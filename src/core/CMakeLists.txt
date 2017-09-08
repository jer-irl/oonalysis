include_directories (/usr/local/opt/llvm/include)

add_library (core strutils.cc parse.cc filetype.cc)

add_subdirectory (clang)
add_subdirectory (common)

target_link_libraries(core /usr/local/opt/llvm/lib/libclang.dylib)

