#include <FL/Fl.H>
#include "gui/mainwindow.h"

int main(void)
{
    oonalysis::gui::MainWindow* mw{};
    mw->show();
    return Fl::run();
}
