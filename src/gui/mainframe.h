#ifndef GUI_MAINFRAME_H
#define GUI_MAINFRAME_H

#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/webview.h>
#include "context.h"

namespace oonalysis::gui {

class MainFrame : public wxFrame {
public:
    MainFrame(Context& ctx);
private:
    Context& ctx;

    void on_parse(wxCommandEvent& event);
    void on_exit(wxCommandEvent& event);
    void on_about(wxCommandEvent& event);
    void on_new_db(wxCommandEvent& event);
    void on_open_db(wxCommandEvent& event);
    void on_display(wxCommandEvent& event);

    wxBoxSizer* main_sizer;
    wxWebView* web_view;
}; // class MainFrame

enum {
    ID_Parse = 1,
    ID_OpenDb = 2,
    ID_NewDb = 3,
    ID_Display = 4,
};

} // namespace oonalysis::gui

#endif // GUI_MAINFRAME_H
