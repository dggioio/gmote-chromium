#!/bin/bash
export NDK=/data/data/com.termux/files/usr/opt/android-ndk

# Удаляем только старую 32-битную сборку
rm -rf build_armeabi-v7a
mkdir -p build_armeabi-v7a
cd build_armeabi-v7a

cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=armeabi-v7a \
    -DANDROID_PLATFORM=android-21 \
    -DCMAKE_BUILD_TYPE=Release

make -j$(nproc)

# Копируем результат в корень для удобства
cp html_chromium.so ../html_chromium.so

echo "Готово! Твой файл: html_chromium.so"
