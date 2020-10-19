cmake_minimum_required(VERSION 3.17)
project(bad_macros)

set(CMAKE_CXX_STANDARD 14)

add_executable(bad_macros main.cpp test_runner.h)