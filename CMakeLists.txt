cmake_minimum_required(VERSION 3.12)
project(ZPR)
set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.65 REQUIRED COMPONENTS unit_test_framework)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)

