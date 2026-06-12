cmake_minimum_required(VERSION 3.10)
project(html_chromium)

add_library(html_chromium SHARED main.cpp)

target_link_libraries(html_chromium PRIVATE dl)

target_compile_options(html_chromium PRIVATE 
    -fPIC 
    -fvisibility=hidden 
    -ffast-math 
    -O2 
    -fno-strict-aliasing
)
