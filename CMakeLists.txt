cmake_minimum_required(VERSION 3.10)
project(gmote-chromium)

set(CMAKE_CXX_STANDARD 17)

# Добавляем библиотеку
add_library(html_chromium SHARED main.cpp)

# 1. Находим системную библиотеку логов
find_library(log-lib log)

# 2. Привязываем библиотеку и добавляем системные пути NDK через toolchain
# Переменная ANDROID_NDK должна быть определена в workflow
target_link_libraries(html_chromium PRIVATE ${log-lib})

# 3. Явно указываем include для логов, если они не подхватываются автоматически
target_include_directories(html_chromium PRIVATE 
    ${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include
)
