cmake_minimum_required(VERSION 3.10)
project(gmote-chromium CXX)

set(CMAKE_CXX_STANDARD 17)

# Создаем библиотеку
add_library(html_chromium SHARED main.cpp)

# Находим системную библиотеку логирования Android
find_library(LOG_LIB log)

# Связываем её с нашим проектом
if(LOG_LIB)
    target_link_libraries(html_chromium PRIVATE ${LOG_LIB})
else()
    target_link_libraries(html_chromium PRIVATE log)
endif()
