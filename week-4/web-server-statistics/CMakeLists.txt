cmake_minimum_required(VERSION 3.17)
project(web_server_statistics)

set(CMAKE_CXX_STANDARD 20)

add_executable(web_server_statistics main.cpp http_request.h stats.h test_runner.h profile.h stats.cpp)