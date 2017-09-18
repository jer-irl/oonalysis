#ifndef GUI_MAINFRAME_H
#define GUI_MAINFRAME_H

#include <wx/frame.h>

namespace oonalysis::gui {

class MainFrame : public wxFrame {
public:
    MainFrame();
private:
    void on_parse(wxCommandEvent& event);
    void on_exit(wxCommandEvent& event);
    void on_about(wxCommandEvent& event);
}; // class MainFrame

enum {
    ID_Parse = 1,
};

} // namespace oonalysis::gui

#endif // GUI_MAINFRAME_H
