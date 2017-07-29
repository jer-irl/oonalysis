add_library (db init.c io.cc add.cc delete.cc get.cc update.cc)
include_directories (.)

target_link_libraries(db sqlite3)
