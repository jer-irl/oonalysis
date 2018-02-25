#include "mainframe.h"

#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/log.h>
#include <wx/filedlg.h>
#include <wx/dialog.h>
#include <wx/webview.h>
#include <wx/button.h>
#include "graph/inclgraph.h"
#include "core/parse.h"

namespace oonalysis::gui {

MainFrame::MainFrame(Context& the_ctx)
        : ctx(the_ctx),
          wxFrame(nullptr, wxID_ANY, "oonalysis", wxDefaultPosition, wxDefaultSize) {

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_NewDb, "&New DB...",
                     "Make a new database file");
    menuFile->Append(ID_OpenDb, "&Open DB...",
                     "Open a database file");
    menuFile->Append(ID_Parse, "&Parse...",
                     "Parse a program");
    menuFile->Append(ID_Display, "&Display",
                     "Display stats");
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
    Bind(wxEVT_MENU, &MainFrame::on_new_db, this, ID_NewDb);
    Bind(wxEVT_MENU, &MainFrame::on_open_db, this, ID_OpenDb);
    Bind(wxEVT_MENU, &MainFrame::on_display, this, ID_Display);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(main_sizer);

    graph_view = new GraphView(this);
    main_sizer->Add(graph_view, wxSizerFlags(1).Expand());
    graph_view->Show();
}

void MainFrame::on_new_db(wxCommandEvent& event) {
    wxFileDialog file_dialog;
    file_dialog.SetTitle("New Database");
    file_dialog.SetWindowStyle(wxFD_SAVE);
    file_dialog.ShowModal();

    ctx.database_path = file_dialog.GetPath();
}

void MainFrame::on_open_db(wxCommandEvent& event) {
    wxFileDialog file_dialog;
    file_dialog.SetTitle("Open Database");
    file_dialog.ShowModal();

    ctx.database_path = file_dialog.GetPath();
}

void MainFrame::on_exit(wxCommandEvent& event) {
    switch (event.GetEventType()) {
    default:
        Close(true);
    }
}

void MainFrame::on_parse(wxCommandEvent& event) {
    event.GetId();

    if (ctx.database_path.empty()) {
        wxDialog no_db;
        no_db.SetTitle("No Database available");
        return;
    }

    wxFileDialog dialog(this, "Select file to parse");
    auto res = dialog.ShowModal();
    if (res == wxCANCEL) {
        return;
    }

    std::string path = dialog.GetPath();

    db::Database db = db::get_storage(ctx.database_path);
    core::parse_file(db, path);
}

void MainFrame::on_about(wxCommandEvent& event) {
    event.GetId();
}

void MainFrame::on_display(wxCommandEvent& event) {
    db::Database db = db::get_storage(ctx.database_path);
    Agraph_t* g = graph::get_inclgraph(db);
    graph_view->set_graph(g);
}

} // namespace oonalysis::gui
