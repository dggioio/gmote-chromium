cmake_minimum_required(VERSION 3.10)
project(html_chromium C CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Убираем все лишние префиксы, чтобы библиотека называлась просто html_chromium.so
# По умолчанию CMake добавляет 'lib' в начале (libhtml_chromium.so)
# Мы переименуем его в build.yml, но здесь отключаем префикс для чистоты
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# Исходный файл
set(SOURCES main.cpp)

# Создаем библиотеку
add_library(html_chromium SHARED ${SOURCES})

# Оптимизация и скрытие символов (оставляем только то, что нужно движку)
target_compile_options(html_chromium PRIVATE 
    -fvisibility=hidden 
    -fPIC
)

# Подключаем необходимые библиотеки Android
target_link_libraries(html_chromium PRIVATE dl log)

# Настройка выходного имени (дополнительная страховка)
set_target_properties(html_chromium PROPERTIES 
    OUTPUT_NAME "html_chromium"
    PREFIX ""
)
