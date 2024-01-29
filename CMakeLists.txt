cmake_minimum_required(VERSION 3.7)
project(ConwaysGameOfLife)

find_package(SDL2 REQUIRED)
include_directories(ConwaysGameOfLife ${SDL2_INCLUDE_DIRS})

add_executable(ConwaysGameOfLife Main.cpp
        Matrix.h
        Vector.h
        Rules.h
)
target_link_libraries(ConwaysGameOfLife ${SDL2_LIBRARIES})