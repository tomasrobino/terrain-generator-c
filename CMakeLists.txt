cmake_minimum_required(VERSION 3.28)
project(terrain_generation_c C)

set(CMAKE_C_STANDARD 11)

add_library(stb_image_write STATIC vendor/stb/stb_image_write.c)
target_include_directories(stb_image_write PUBLIC vendor/stb)

add_executable(terrain_generation_c main.c
        generation.c
        generation.h)

target_link_libraries(terrain_generation_c PRIVATE stb_image_write)

if (NOT MSVC)
    target_link_libraries(terrain_generation_c PRIVATE m)
endif ()
