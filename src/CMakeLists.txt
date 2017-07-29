add_executable (oonalysis main.cc)
include_directories(.)

add_subdirectory (db)
add_subdirectory (metrics)
#add_subdirectory (core)
#add_subdirectory (cli)

#target_link_libraries (oonalysis core)
#target_link_libraries (oonalysis cli)
target_link_libraries (oonalysis db)
target_link_libraries (oonalysis metrics)

