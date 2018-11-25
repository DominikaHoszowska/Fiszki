add_library(sqlite3 sqlite3.c shell.c sqlite_orm.h)
target_link_libraries(sqlite3 dl)
