#include <FL/Fl_Window.H>
#include "mainwindow.h"

namespace oonalysis { namespace gui {

MainWindow::MainWindow(int w, int h, const char* t) : Fl_Window(w, h, t),
                                                      menu_bar(w)
{
    // Config
    this->resizable(this);

    // Members
    this->add(menu_bar);
}

} } // namespace oonalysis::gui
