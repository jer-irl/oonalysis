include_directories (.)
add_library (cli parse.cc list.cpp help.cpp cli.cpp)

target_link_libraries (cli /usr/local/lib/libboost_filesystem.a)
target_link_libraries (cli /usr/local/lib/libboost_system.a)
target_link_libraries (cli /usr/local/lib/libboost_program_options.a)
