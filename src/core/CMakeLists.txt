include_directories (/usr/local/opt/llvm/include)

add_subdirectory (clang)

add_library (core cpreprocessor.cc Ctx.cc ghc.cc strutils.cc parse.cc filetype.cc)

target_link_libraries (core myclang)

