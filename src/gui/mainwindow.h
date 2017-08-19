#ifndef GUI_MAINWINDOW_H
#define GUI_MAINWINDOW_H

#include <FL/Fl_Window.H>

namespace oonalysis::gui {

class MainWindow : public Fl_Window {
public:
    MainWindow(int w, int h, const char* t);
    ~MainWindow() { }

}; // class MainWindow


} // namespace oonalysis::gui

#endif // GUI_MAINWINDOW_H
