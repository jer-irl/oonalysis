#ifndef GUI_MAINWINDOW_HPP
#define GUI_MAINWINDOW_HPP

#include <QMainWindow>
#include <QTreeWidget>
#include <QLabel>
#include <QScrollArea>
#include <string>
#include <graphviz/cgraph.h>
#include "FileTree.h"

namespace oonalysis::gui {

class MainWindow : public QMainWindow {

public:
    MainWindow();

private:
    void create_menu_bar();

    void on_new_database();
    void on_open_database();
    void on_select_project_root();
    void on_parse();
    void on_show_inclusions();
    void on_show_callgraph();
    void on_show_filenode();
    void on_show_inclusions_rendered();

    std::string db_name = "";
    std::string project_root = "";

    FileTree *file_tree;
    QLabel *image_label;
    QScrollArea *image_scroll_area;

    void show_graph_image(Agraph_t* graph);

}; // class MainWindow

} // namespace oonalysis::gui

#endif // GUI_MAINWINDOW_HPP