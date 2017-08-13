include_directories (.)
add_library (myclang clang.cc cursor_dispatch.cc handlers.cc)

target_link_libraries(myclang /usr/local/opt/llvm/lib/libclang.dylib)
