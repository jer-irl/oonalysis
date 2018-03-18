#include "gui/mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])  {
    QApplication oonalysisApp(argc, argv);

    oonalysis::gui::MainWindow main_window;
    main_window.show();

    return oonalysisApp.exec();
}
