add_library (core parse.cc filetype.cc)

add_subdirectory (clang)
add_subdirectory (common)

target_link_libraries(core /usr/local/opt/llvm/lib/libclang.dylib)

