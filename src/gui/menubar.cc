#include <FL/Fl_Menu_Bar.H>
#include "menubar.h"

namespace oonalysis { namespace gui {

MenuBar::MenuBar(int width) : Fl_Menu_Bar(0, 0, width, 20, "oonalysis")
{
    // Buttons
    this->add("File");
    this->add("Action");
    //this->show();
}

} } // namespace oonalysis::gui
