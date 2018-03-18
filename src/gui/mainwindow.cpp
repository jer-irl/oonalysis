#include "mainwindow.hpp"

#include <QMenuBar>
#include <QFileDialog>
#include <QDockWidget>
#include <QScrollArea>
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include "core/parse.h"
#include "db/db.h"
#include "graph/inclgraph.h"

namespace fs = boost::filesystem;

namespace oonalysis::gui {

MainWindow::MainWindow() : QMainWindow() {
    create_menu_bar();

    file_tree = new FileTree(fs::current_path().string());
    auto left_dock = new QDockWidget("File Selection");
    left_dock->setWidget(file_tree);
    addDockWidget(Qt::LeftDockWidgetArea, left_dock);

    image_scroll_area = new QScrollArea(this);
    image_label = new QLabel(image_scroll_area);
    image_scroll_area->setWidget(image_label);
    setCentralWidget(image_scroll_area);
    image_scroll_area->setWidgetResizable(true);
}

void MainWindow::create_menu_bar() {
    QMenuBar *menu_bar = menuBar();

    auto file_menu = new QMenu("File");

    auto new_db_action = new QAction("New Database...");
    file_menu->addAction(new_db_action);
    connect(new_db_action, &QAction::triggered, this, &MainWindow::on_new_database);

    auto open_db_action = new QAction("Open Database...");
    file_menu->addAction(open_db_action);
    connect(open_db_action, &QAction::triggered, this, &MainWindow::on_open_database);

    auto select_project_root_action = new QAction("Open Project Root...");
    file_menu->addAction(select_project_root_action);
    connect(select_project_root_action, &QAction::triggered, this, &MainWindow::on_select_project_root);

    auto parse_action = new QAction("Parse files");
    file_menu->addAction(parse_action);
    connect(parse_action, &QAction::triggered, this, &MainWindow::on_parse);

    auto show_inclusions_action = new QAction("Show inclusions");
    file_menu->addAction(show_inclusions_action);
    connect(show_inclusions_action, &QAction::triggered, this, &MainWindow::on_show_inclusions);

    menu_bar->addMenu(file_menu);
}

void MainWindow::on_new_database() {
    db_name = QFileDialog::getSaveFileName(this, "Make a new database").toStdString();
}

void MainWindow::on_select_project_root() {
    project_root = QFileDialog::getExistingDirectory(this, "Select Project Root").toStdString();
    file_tree->set_root(project_root);
    file_tree->redraw();
}

void MainWindow::on_parse() {
    auto files = file_tree->selected_files();
    db::Database db = db::get_storage(db_name);
    core::parse_files(db, files);
}

void MainWindow::on_open_database() {
    db_name = QFileDialog::getOpenFileName(this, "Open an existing database").toStdString();
}

void MainWindow::on_show_inclusions() {
    db::Database db = db::get_storage(db_name);
    Agraph_t *graph = graph::get_inclgraph(db);

    FILE *image_file = fopen("graph.png", "w");
    GVC_t* gvc = gvContext();
    gvLayout(gvc, graph, "dot");
    gvRender(gvc, graph, "png", image_file);
    fclose(image_file);

    agclose(graph);

    QImage image("graph.png");
    image_label->setPixmap(QPixmap::fromImage(image));
}

} // namespace oonalysis::gui