#ifndef GUI_MENUBAR_H
#define GUI_MENUBAR_H

#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>

namespace oonalysis { namespace gui {

class MenuBar : public Fl_Menu_Bar {
public:
    MenuBar(int w);
    ~MenuBar() { }
private:

}; // class MenuBar

} } // namespace oonalysis::gui

#endif // GUI_MENUBAR_H
