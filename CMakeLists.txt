cmake_minimum_required(VERSION 3.10)
project(gmote-chromium)

set(CMAKE_CXX_STANDARD 17)

# Ищем библиотеку логов Android
find_library(log-lib log)

# Добавляем библиотеку проекта
add_library(html_chromium SHARED main.cpp)

# Линкуем библиотеку логов
target_link_libraries(html_chromium PUBLIC ${log-lib})

# Явно подключаем системные заголовки NDK
target_include_directories(html_chromium PUBLIC ${ANDROID_NDK}/sysroot/usr/include)
