#include "mainwindow.hpp"

#include <QMenuBar>
#include <QFileDialog>
#include <boost/filesystem.hpp>
#include "FileTree.h"

namespace fs = boost::filesystem;

namespace oonalysis::gui {

MainWindow::MainWindow() : QMainWindow() {
    file_tree = new FileTree(fs::current_path().string());
    setCentralWidget(file_tree);

    create_menu_bar();
}

void MainWindow::create_menu_bar() {
    QMenuBar *menu_bar = menuBar();

    auto file_menu = new QMenu("File");

    auto new_db_action = new QAction("New Database...");
    file_menu->addAction(new_db_action);
    connect(new_db_action, &QAction::triggered, this, &MainWindow::on_new_database);

    auto select_project_root_action = new QAction("Open Project Root...");
    file_menu->addAction(select_project_root_action);
    connect(select_project_root_action, &QAction::triggered, this, &MainWindow::on_select_project_root);

    menu_bar->addMenu(file_menu);
}

void MainWindow::on_new_database() {
    db_name = QFileDialog::getSaveFileName(this, "Make a new database").toStdString();
}

void MainWindow::on_select_project_root() {
    project_root = QFileDialog::getExistingDirectory(this, "Select Project Root").toStdString();
}

} // namespace oonalysis::gui