cmake_minimum_required(VERSION 3.10)
project(html_chromium C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Убираем префикс 'lib', чтобы файл сразу назывался html_chromium.so
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# Исходный файл
set(SOURCES main.cpp)

# Создаем библиотеку
add_library(html_chromium SHARED ${SOURCES})

# Оптимизация: скрываем внутренние символы, оставляем только CreateInterface
target_compile_options(html_chromium PRIVATE 
    -fvisibility=hidden 
    -fPIC
)

# Линковка системных библиотек
target_link_libraries(html_chromium PRIVATE dl log)

# Настройка итогового имени
set_target_properties(html_chromium PROPERTIES 
    OUTPUT_NAME "html_chromium"
    PREFIX ""
)
