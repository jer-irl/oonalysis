#ifndef GUI_GRAPHDISPLAYREGION_HPP
#define GUI_GRAPHDISPLAYREGION_HPP

#include <QWebEngineView>
#include <QWebSocketServer>
#include <memory>
#include "WebState.hpp"
#include "WebSocketClientWrapper.hpp"

namespace oonalysis::gui {

class GraphDisplayRegion : public QWebEngineView {
public:
    GraphDisplayRegion(QWidget* parent = nullptr);
    void startInclusionsRendering();

private:
    WebState* webState;
    QWebSocketServer* webSocketServer;
    QWebChannel* webChannel;
    WebSocketClientWrapper* webSocketClientWrapper;
};

} // namespace oonalysis::gui

#endif // GUI_GRAPHDISPLAYREGION_HPP