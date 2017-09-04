add_library (gui mainwindow.cc menubar.cc menucallbacks.cc ctx.cc canvas.cc guinodes.cc)

target_link_libraries (gui fltk)
target_link_libraries (gui db)
