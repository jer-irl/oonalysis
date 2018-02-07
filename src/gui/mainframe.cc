#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/log.h>
#include "mainframe.h"

namespace oonalysis::gui {

MainFrame::MainFrame()
          : wxFrame(nullptr, wxID_ANY, "oonalysis", wxDefaultPosition, wxDefaultSize) {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Parse, "&Parse...",
                     "Parse a program");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");

    SetMenuBar(menuBar);
    CreateStatusBar();

    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &MainFrame::on_parse, this, ID_Parse);
    Bind(wxEVT_MENU, &MainFrame::on_about, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::on_exit, this, wxID_EXIT);
}

void MainFrame::on_exit(wxCommandEvent& event) {
    switch (event.GetEventType()) {
    default:
        Close(true);
    }
}

void MainFrame::on_parse(wxCommandEvent& event) {
    event.GetId();
    wxLogMessage("Hello world from wxWidgets!");
}

void MainFrame::on_about(wxCommandEvent& event) {
    event.GetId();
    wxLogMessage("Hello world from wxWidgets!");
}

} // namespace oonalysis::gui
