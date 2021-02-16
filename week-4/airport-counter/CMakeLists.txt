cmake_minimum_required(VERSION 3.17)
project(airport_counter)

set(CMAKE_CXX_STANDARD 20)

add_executable(airport_counter main.cpp test_runner.h profile.h)