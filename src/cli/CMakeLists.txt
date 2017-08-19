include_directories (.)
add_library (cli parse.cc)

target_link_libraries (cli /usr/local/lib/libboost_filesystem.a)
target_link_libraries (cli /usr/local/lib/libboost_system.a)
target_link_libraries (cli /usr/local/lib/libboost_program_options.a)
target_link_libraries (cli db)
target_link_libraries (cli core)
target_link_libraries (cli metrics)
