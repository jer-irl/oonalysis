#ifndef GUI_GRAPHDISPLAYREGION_HPP
#define GUI_GRAPHDISPLAYREGION_HPP

#include <QWebEngineView>

namespace oonalysis::gui {

class GraphDisplayRegion : public QWebEngineView {
public:
    GraphDisplayRegion(QWidget* parent = nullptr);
};

} // namespace oonalysis::gui

#endif // GUI_GRAPHDISPLAYREGION_HPP