file(GLOB_RECURSE TEST_SOURCES "*.cpp")

add_executable(all_unit_tests ${TEST_SOURCES})

target_link_libraries(all_unit_tests ${Boost_LIBRARIES} fiszki ${SQLite_LIB})
