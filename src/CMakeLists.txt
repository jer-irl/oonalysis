add_definitions(-DWITH_CLI)
include_directories(.)
add_executable (oonalysis main.cc)

option(GUI "Run with gui" OFF)
option(CLI "Run with cli" ON)

add_subdirectory (db)
add_subdirectory (metrics)
add_subdirectory (core)
add_subdirectory (cli)

target_link_libraries (oonalysis core)
target_link_libraries (oonalysis db)
target_link_libraries (oonalysis metrics)
target_link_libraries (oonalysis SQLiteCpp)
target_link_libraries (oonalysis cli)

if(GUI)
    add_definitions(-DWITH_GUI)
    #add_subdirectory(gui)
    #target_link_libraries(oonalysis gui)
elseif(CLI)
else()
    message (FATAL_ERROR "Need an interface")
endif()

