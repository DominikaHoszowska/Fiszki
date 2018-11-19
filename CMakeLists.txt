cmake_minimum_required(VERSION 3.12)
project(ZPR)

set(CMAKE_CXX_STANDARD 14)

add_executable(ZPR main.cpp Card.h Collection.h Card.cpp Collection.cpp)