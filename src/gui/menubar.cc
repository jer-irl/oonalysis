#include <string>
#include <FL/Fl_Menu_.H>
#include <FL/Fl_Sys_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include "menubar.h"
#include "menucallbacks.h"

namespace oonalysis::gui {

MenuBar::MenuBar(int width) : Fl_Sys_Menu_Bar(0, 0, width, 20, "oonalysis") {
    this->add("File/Open DB", 0, file_open_db);
    this->add("Action/Analyze", 0, action_parse);
}

} // namespace oonalysis::gui
