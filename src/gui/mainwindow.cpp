#include "mainwindow.hpp"

#include <QMenuBar>
#include <QFileDialog>

namespace oonalysis::gui {

MainWindow::MainWindow() : QMainWindow() {
    create_menu_bar();
}

void MainWindow::create_menu_bar() {
    QMenuBar *menu_bar = menuBar();

    auto file_menu = new QMenu("File");
    auto new_db_action = new QAction("New Database...");
    file_menu->addAction(new_db_action);
    connect(new_db_action, &QAction::triggered, this, &MainWindow::on_new_database);

    menu_bar->addMenu(file_menu);
}

void MainWindow::on_new_database() {
    QString file_name = QFileDialog::getSaveFileName(this, "Make a new database");
}

} // namespace oonalysis::gui