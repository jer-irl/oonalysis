cmake_minimum_required (VERSION 3.0.0)
project (oonalysis)
set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_C_FLAGS "-Wall -std=c11")
set (CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories (lib/SQLiteCpp/include)
add_subdirectory (lib)

include_directories (lib/SQLiteCpp/include/SQLiteCpp)
add_subdirectory (src)


