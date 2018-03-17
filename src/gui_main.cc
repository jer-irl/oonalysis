#include "gui/mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])  {
    QApplication OOnalysisApp(argc, argv);

    oonalysis::gui::MainWindow main_window;
    main_window.show();

    return OOnalysisApp.exec();
}
