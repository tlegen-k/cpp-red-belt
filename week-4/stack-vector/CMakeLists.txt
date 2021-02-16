cmake_minimum_required(VERSION 3.17)
project(stack_vector)

set(CMAKE_CXX_STANDARD 20)

add_executable(stack_vector main.cpp stack_vector.h test_runner.h profile.h)