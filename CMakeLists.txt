cmake_minimum_required (VERSION 3.0.0)
project (oonalysis)
set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories (lib/SQLiteCpp/include)
dd_subdirectory (lib)

include_directories (lib/SQLiteCpp/include/SQLiteCpp)
add_subdirectory (src)


set (CMAKE_C_FLAGS -Wall)
set (CMAKE_CXX_FLAGS -Wall)
