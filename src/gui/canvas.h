#ifndef GUI_CANVAS_H
#define GUI_CANVAS_H

#include <FL/Fl_Group.H>

namespace oonalysis::gui {

class Canvas : public Fl_Group {
public:
    Canvas(int x, int y, int w, int h) : Fl_Group(x, y, w, h) { }
    void display();
}; // class Canvas

} // namespace oonalysis::gui

#endif // GUI_CANVAS_H
