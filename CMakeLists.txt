cmake_minimum_required(VERSION 3.10)
project(chip8)

set(SOURCES
    src/main.c
    src/instructions.c
    src/chip8.c
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(chip8 ${SOURCES})
target_link_libraries(chip8 ${SDL2_LIBRARIES})

