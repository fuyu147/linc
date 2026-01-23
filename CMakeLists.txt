cmake_minimum_required(VERSION 3.10)
project(linc)

set(CMAKE_C_STANDARD 99)

file(GLOB SRC_FILES
    source/*.c
    source/*/*.c
)

add_executable(linc ${SRC_FILES})

target_include_directories(linc PRIVATE
    source/matrix
    source/vector
    source/repl
)

target_link_libraries(linc PRIVATE raylib)
