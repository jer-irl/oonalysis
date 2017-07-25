add_library (core cpreprocessor.cc Ctx.cc filetype.cc ghc.cc srcfile.cc strutils.cc)

include_directories (/usr/local/opt/llvm/include)
link_directories (/usr/local/opt/llvm/lib)
