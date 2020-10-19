cmake_minimum_required(VERSION 3.17)
project(comparator_generator)

set(CMAKE_CXX_STANDARD 17)

add_executable(comparator_generator main.cpp test_runner.h airline_ticket.h)