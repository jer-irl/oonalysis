add_library (gui mainwindow.cc menubar.cc menucallbacks.cc ctx.cc)

target_link_libraries (gui fltk)
