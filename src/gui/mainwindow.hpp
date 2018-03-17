#ifndef GUI_MAINWINDOW_HPP
#define GUI_MAINWINDOW_HPP

#include <QMainWindow>
#include <QTreeWidget>
#include <string>

namespace oonalysis::gui {

class MainWindow : public QMainWindow {

public:
    MainWindow();

private:
    void create_menu_bar();

    void on_new_database();
    void on_select_project_root();

    std::string db_name = "";
    std::string project_root = "";

    QTreeWidget *file_tree;

}; // class MainWindow

} // namespace oonalysis::gui

#endif // GUI_MAINWINDOW_HPP