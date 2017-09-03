#ifndef GUI_CTX_H
#define GUI_CTX_H

#include <string>
#include "mainwindow.h"
#include "canvas.h"

namespace oonalysis::gui {

class Ctx {
public:
    static Ctx* inst();

    Ctx();
    void show();

    MainWindow mw;
    Canvas* canvas;
    std::string db_filename;
}; // class Ctx

} // namespace oonalysis::gui

#endif // GUI_CTX_H
