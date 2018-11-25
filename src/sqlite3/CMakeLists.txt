add_library(sqlite3 sqlite3.c shell.c)
target_link_libraries(sqlite3 dl)
