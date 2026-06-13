cmake_minimum_required(VERSION 3.10)
project(gmote-chromium)

set(CMAKE_CXX_STANDARD 17)

# Добавляем библиотеку
add_library(html_chromium SHARED main.cpp)

# Линкуем библиотеку логов
target_link_libraries(html_chromium PUBLIC log)

# Добавляем пути к системным заголовкам
target_include_directories(html_chromium PUBLIC ${ANDROID_NDK}/sysroot/usr/include)
