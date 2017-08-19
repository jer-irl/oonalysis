#ifndef GUI_MAINWINDOW_H
#define GUI_MAINWINDOW_H

#include <FL/Fl_Window.H>
#include "menubar.h"

namespace oonalysis::gui {

class MainWindow : public Fl_Window {
public:
    MainWindow(int w, int h, const char* t);
    ~MainWindow() { }
private:
    MenuBar menu_bar;

}; // class MainWindow


} // namespace oonalysis::gui

#endif // GUI_MAINWINDOW_H
