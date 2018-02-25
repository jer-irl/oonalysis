#ifndef GUI_GRAPHVIEW_H
#define GUI_GRAPHVIEW_H

#include <wx/panel.h>
#include <graphviz/cgraph.h>

namespace oonalysis::gui {

class GraphView : public wxPanel {
public:
    explicit GraphView(wxWindow* parent);
    void set_graph(Agraph_t* graph);
    void on_paint(wxPaintEvent& event);

private:
    Agraph_t *graph;

}; // class GraphView

} // namespace oonalysis::gui

#endif // GUI_GRAPHVIEW_H