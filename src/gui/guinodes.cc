#include "FL/Fl_Box.H"
#include "guinodes.h"

namespace oonalysis::gui {

GuiNode::GuiNode() :
    gui_box(0, 0, 30, 20)
{
}

void GuiNode::show() {
    gui_box.show();
}

} // namespace oonalysis::gui
