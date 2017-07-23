cmake_minimum_required (VERSION 3.0.0)
project (oonalysis)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_subdirectory (lib)
add_subdirectory (src)

set (CMAKE_C_FLAGS -Wall -O2)
