cmake_minimum_required(VERSION 3.10)
project(html_chromium)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(html_chromium SHARED main.cpp)

target_link_libraries(html_chromium PRIVATE dl)

target_compile_options(html_chromium PRIVATE 
    -fPIC 
    -fvisibility=hidden 
    -ffast-math 
    -O3 
    -fno-strict-aliasing
    -Wall
)
