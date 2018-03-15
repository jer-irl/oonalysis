#include "graphview.h"

#include <wx/graphics.h>
#include <wx/dcclient.h>
#include <graphviz/gvc.h>


namespace oonalysis::gui {

GraphView::GraphView(wxWindow* parent) : wxScrolledWindow(parent) {
    graph = nullptr;
    Bind(wxEVT_PAINT, &GraphView::on_paint, this);
    wxImage::AddHandler(new wxPNGHandler);
    graphviz_ctx = gvContext();

    SetScrollRate(10, 10);
}

void GraphView::set_graph(Agraph_t* g) {
    this->graph = g;
    FILE* image_file = fopen("graph.png", "w");

    gvLayout(graphviz_ctx, graph, "dot");
    gvRender(graphviz_ctx, graph, "png", image_file);
    fclose(image_file);
    gvFreeLayout(graphviz_ctx, graph);

    this->Refresh();
}

void GraphView::on_paint(wxPaintEvent& event) {
    if (!graph) {
        return;
    }

    wxImage img("graph.png");
    wxBitmap bitmap(img);

    SetVirtualSize(bitmap.GetWidth(), bitmap.GetHeight());

    wxPaintDC dc(this);
    DoPrepareDC(dc);
    wxGraphicsContext* ctx = wxGraphicsContext::Create(dc);

    ctx->DrawBitmap(bitmap, 0, 0, bitmap.GetWidth(), bitmap.GetHeight());
}

} // namespace oonalysis::gui