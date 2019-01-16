cmake_minimum_required(VERSION 3.12)
project(ZPR)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Boost 1.65 REQUIRED COMPONENTS unit_test_framework date_time)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)


install(TARGETS fiszki sqlite3 DESTINATION /usr/local/lib/)
#install(FILES)
