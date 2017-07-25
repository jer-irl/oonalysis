add_library (db init.c io.c)
include_directories (.)

target_link_libraries(db sqlite3)
