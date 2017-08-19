cmake_minimum_required (VERSION 3.0.0)
project (oonalysis)
set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1z")

include_directories (lib/SQLiteCpp/include)
add_subdirectory (lib)

include_directories (lib/SQLiteCpp/include/SQLiteCpp)
include_directories (lib/FLTK)
add_subdirectory (src)


