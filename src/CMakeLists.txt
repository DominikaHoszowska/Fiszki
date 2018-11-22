file(GLOB_RECURSE SOURCES "fiszki/*.cpp")
add_library(fiszki ${SOURCES})

add_executable(ZPR main.cpp)
target_link_libraries(ZPR fiszki)
