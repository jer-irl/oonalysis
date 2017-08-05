include_directories (/usr/local/opt/llvm/include)

add_library (core cpreprocessor.cc Ctx.cc ghc.cc strutils.cc parse.cc clang.cc filetype.cc)

find_package (clang REQUIRED)
target_link_libraries(core /usr/local/opt/llvm/lib/libclang.dylib)

