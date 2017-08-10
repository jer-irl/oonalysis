add_library (cli parse.cc)
include_directories (.)

target_link_libraries (cli util)
