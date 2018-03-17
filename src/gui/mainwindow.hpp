#ifndef GUI_MAINWINDOW_HPP
#define GUI_MAINWINDOW_HPP

#include <QMainWindow>
#include <QTreeWidget>
#include <QLabel>
#include <string>
#include "FileTree.h"

namespace oonalysis::gui {

class MainWindow : public QMainWindow {

public:
    MainWindow();

private:
    void create_menu_bar();

    void on_new_database();
    void on_select_project_root();
    void on_parse();

    std::string db_name = "";
    std::string project_root = "";

    FileTree *file_tree;
    QLabel *image_label;

}; // class MainWindow

} // namespace oonalysis::gui

#endif // GUI_MAINWINDOW_HPP