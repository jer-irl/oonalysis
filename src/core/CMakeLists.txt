add_library (core cpreprocessor.cc Ctx.cc filetype.cc ghc.cc srcfile.cc strutils.cc parse.cc)

include_directories (/usr/local/opt/llvm/include)
link_directories (/usr/local/opt/llvm/lib)
