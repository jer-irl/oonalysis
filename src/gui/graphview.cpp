#include "graphview.h"

#include <wx/graphics.h>
#include <graphviz/gvc.h>


namespace oonalysis::gui {

GraphView::GraphView(wxWindow* parent) : wxPanel(parent) {
    graph = nullptr;
    Bind(wxEVT_PAINT, &GraphView::on_paint, this);
    wxImage::AddHandler(new wxPNGHandler);
}

void GraphView::set_graph(Agraph_t* g) {
    this->graph = g;
}

void GraphView::on_paint(wxPaintEvent& event) {
    if (!graph) {
        return;
    }

    wxGraphicsContext* ctx = wxGraphicsContext::Create(this);

    FILE* image_file = fopen("graph.png", "w");

    GVC_t* gvc = gvContext();
    gvLayout(gvc, graph, "dot");
    gvRender(gvc, graph, "png", image_file);
    fclose(image_file);

    wxImage img("graph.png");
    bool is_okay = img.IsOk();
    wxBitmap bitmap(img);
    ctx->DrawBitmap(bitmap, 0, 0, 500, 500);
}

} // namespace oonalysis::gui