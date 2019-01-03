add_subdirectory(sqlite3)

file(GLOB_RECURSE SOURCES "fiszki/*.cpp")
add_library(fiszki ${SOURCES})
target_link_libraries(fiszki sqlite3)

add_executable(ZPR main.cpp)
target_link_libraries(ZPR fiszki)
