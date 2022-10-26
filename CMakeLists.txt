cmake_minimum_required(VERSION 3.17)
project(Projet C)

set(CMAKE_C_STANDARD 99)

add_executable(Projet main.c sources/test.c includes/test.h sources/map/tiles.c includes/map/tiles.h)

add_subdirectory("raylib")
include_directories("raylib")

target_link_libraries(Projet raylib)

