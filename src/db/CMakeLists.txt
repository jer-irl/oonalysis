add_library (db init.cc file.cc cppinclusion.cc)

include_directories (.)
add_subdirectory (repo)

target_link_libraries(db sqlite3)
target_link_libraries(db SQLiteCpp)
target_link_libraries(db util)
