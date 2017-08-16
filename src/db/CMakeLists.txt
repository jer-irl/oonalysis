include_directories (.)

add_subdirectory (repo)

add_library (db init.cc file.cc cppinclusion.cc)

target_link_libraries(db sqlite3)
target_link_libraries(db repo)
