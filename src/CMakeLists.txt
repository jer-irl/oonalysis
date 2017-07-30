add_executable (oonalysis main.cc)
include_directories(.)

add_subdirectory (db)
add_subdirectory (metrics)
add_subdirectory (cli)
add_subdirectory (core)

target_link_libraries (oonalysis core)
target_link_libraries (oonalysis cli)
target_link_libraries (oonalysis db)
target_link_libraries (oonalysis metrics)
target_link_libraries (oonalysis SQLiteCpp)

