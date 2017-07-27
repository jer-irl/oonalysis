add_library (db init.c io.c add.c)
include_directories (.)

target_link_libraries(db sqlite3)
