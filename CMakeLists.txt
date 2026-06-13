name: Build Chromium (Hard Override r25c)

on: [push, pull_request]

jobs:
  build_32:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4

      - name: Setup NDK r25c
        run: |
          # Скачиваем и распаковываем
          wget -q https://dl.google.com/android/repository/android-ndk-r25c-linux.zip
          unzip -q android-ndk-r25c-linux.zip -d $HOME/ndk25
          
          # Устанавливаем путь
          echo "MY_NDK_PATH=$HOME/ndk25/android-ndk-r25c" >> $GITHUB_ENV

      - name: Compile 32-bit
        run: |
          # ВАЖНО: Переопределяем системную переменную, чтобы cmake брал наш NDK
          export ANDROID_NDK_HOME=$MY_NDK_PATH
          export CMAKE_PREFIX_PATH=$MY_NDK_PATH
          
          mkdir build_32 && cd build_32
          
          # Запускаем cmake, явно указывая путь к toolchain
          cmake .. \
            -DCMAKE_TOOLCHAIN_FILE=$MY_NDK_PATH/build/cmake/android.toolchain.cmake \
            -DANDROID_NDK=$MY_NDK_PATH \
            -DANDROID_ABI=armeabi-v7a \
            -DANDROID_PLATFORM=android-24 \
            -DCMAKE_BUILD_TYPE=Release
            
          make -j$(nproc)
          
      - uses: actions/upload-artifact@v4
        with:
          name: lib_armeabi-v7a
          path: build_32/html_chromium.so
