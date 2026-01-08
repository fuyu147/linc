cmake_minimum_required(VERSION 3.10)
project(flies)

set(CMAKE_C_STANDARD 99)

file(GLOB SRC_FILES
    source/*.c
    source/*/*.c
)

add_executable(flies ${SRC_FILES})

target_include_directories(flies PRIVATE
    source/matrix
    source/vector
)
