cmake_minimum_required(VERSION 3.16)
project(generate_LS)

set(CMAKE_CXX_STANDARD 14)
include_directories( "/usr/include/eigen3" )
add_executable(generate_LS main.cpp)