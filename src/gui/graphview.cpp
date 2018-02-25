#include "graphview.h"

#include <wx/graphics.h>
#include <wx/dcclient.h>
#include <graphviz/gvc.h>


namespace oonalysis::gui {

GraphView::GraphView(wxWindow* parent) : wxPanel(parent) {
    graph = nullptr;
    Bind(wxEVT_PAINT, &GraphView::on_paint, this);
    wxImage::AddHandler(new wxPNGHandler);
    graphviz_ctx = gvContext();
}

void GraphView::set_graph(Agraph_t* g) {
    this->graph = g;
    FILE* image_file = fopen("graph.png", "w");

    gvLayout(graphviz_ctx, graph, "dot");
    gvRender(graphviz_ctx, graph, "png", image_file);
    fclose(image_file);

    this->Refresh();
}

void GraphView::on_paint(wxPaintEvent& event) {
    if (!graph) {
        return;
    }

    wxPaintDC dc(this);
    wxGraphicsContext* ctx = wxGraphicsContext::Create(dc);

    wxImage img("graph.png");
    wxBitmap bitmap(img);
    int w, h;
    GetSize(&w, &h);
    ctx->DrawBitmap(bitmap, 0, 0, w, h);
}

} // namespace oonalysis::gui