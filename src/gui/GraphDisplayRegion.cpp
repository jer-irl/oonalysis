#include "GraphDisplayRegion.hpp"

namespace oonalysis::gui {

GraphDisplayRegion::GraphDisplayRegion(QWidget *parent) : QWebEngineView(parent) {
    load(QUrl(QString("https://google.com")));
}

} // namespace oonalysis::gui