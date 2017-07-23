add_executable (oonalysis main.cc)
include_directories(.)

link_libraries (oonalysis STATIC core)
include_directories(core)

link_libraries (oonalysis STATIC cli)
include_directories (cli)

