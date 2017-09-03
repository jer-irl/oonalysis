#ifndef GUI_MENUCALLBACKS_H
#define GUI_MENUCALLBACKS_H

#include <Fl/Fl_Widget.H>

namespace oonalysis::gui {

void file_open_db(Fl_Widget* w, void* d);
void file_new_db(Fl_Widget* w, void* d);
void action_parse(Fl_Widget* w, void* d);
void action_visualize(Fl_Widget* w, void* d);

} // namespace oonalysis::gui

#endif // GUI_MENUCALLBACKS_H
