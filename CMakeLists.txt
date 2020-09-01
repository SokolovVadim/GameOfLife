cmake_minimum_required(VERSION 3.6)
project(GameOfLife)

# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER "/usr/bin/mpic++")

set(SFML_ROOT_DIR "/home/vadim/Documents/SFML-2.5.1")
set(SFML_DIR "${SFML_ROOT_DIR}/lib/cmake/SFML")

find_package(SFML 2.5 REQUIRED COMPONENTS graphics audio)

add_executable(GameOfLife main.cpp engine.cpp engine.hpp matrix.cpp matrix.hpp)

target_link_libraries(GameOfLife sfml-graphics sfml-audio)

include_directories(/usr/include/mpi/)