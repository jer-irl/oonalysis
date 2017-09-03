add_library (gui mainwindow.cc menubar.cc menucallbacks.cc ctx.cc canvas.cc)

target_link_libraries (gui fltk)
