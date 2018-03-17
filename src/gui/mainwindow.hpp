#ifndef GUI_MAINWINDOW_HPP
#define GUI_MAINWINDOW_HPP

#include <QMainWindow>
#include <string>

namespace oonalysis::gui {

class MainWindow : public QMainWindow {

public:
    MainWindow();

private:
    void create_menu_bar();
    void on_new_database();

}; // class MainWindow

} // namespace oonalysis::gui

#endif // GUI_MAINWINDOW_HPP