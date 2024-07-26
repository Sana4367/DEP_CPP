cmake_minimum_required(VERSION 3.10)
project(MultiThreadedWebServer)

set(CMAKE_CXX_STANDARD 11)

add_executable(MultiThreadedWebServer src/main.cpp src/server.cpp)
