add_library (myclang clang.cc)

find_package (clang REQUIRED)
target_link_libraries(myclang /usr/local/opt/llvm/lib/libclang.dylib)
