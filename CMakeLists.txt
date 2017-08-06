cmake_minimum_required (VERSION 3.0.0)
project (oonalysis)
set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build Libraries
include_directories (lib/SQLiteCpp/include)
set (CMAKE_CXX_FLAGS "-w")
add_subdirectory (lib)

# Include Libraries
include_directories (lib/SQLiteCpp/include/SQLiteCpp)
include_directories (lib/spdlog/include/spdlog)

# Build Source
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

add_subdirectory (src)


