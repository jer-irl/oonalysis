#include "GraphDisplayRegion.hpp"

namespace oonalysis::gui {

GraphDisplayRegion::GraphDisplayRegion(QWidget *parent) : QWebEngineView(parent) {
    load(QUrl("file:///Users/Jeremy/Programming/oonalysis/src/gui/index.html"));
}

void GraphDisplayRegion::startInclusionsRendering() {
    page()->runJavaScript("showInclusions()");
}

} // namespace oonalysis::gui