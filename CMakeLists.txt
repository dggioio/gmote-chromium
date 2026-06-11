cat << 'EOF' > CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(GMoteChromium)

add_library(html_chromium SHARED main.cpp)

target_compile_options(html_chromium PRIVATE -Wall -fvisibility=hidden)
set_target_properties(html_chromium PROPERTIES PREFIX "")
EOF
