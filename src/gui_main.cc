#include <FL/Fl.H>
#include "gui/mainwindow.h"

int main(void) {
    oonalysis::gui::MainWindow mw(400, 400, "oonalysis");
    mw.show();
    return Fl::run();
}
