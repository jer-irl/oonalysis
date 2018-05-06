#include "GraphDisplayRegion.hpp"

#include <QWebChannel>

namespace oonalysis::gui {

GraphDisplayRegion::GraphDisplayRegion(QWidget *parent) : QWebEngineView(parent) {
    webState = new WebInterface(this);
    webSocketServer = new QWebSocketServer("Placeholder name", QWebSocketServer::NonSecureMode, this);
    webChannel = new QWebChannel(this);
    webSocketClientWrapper = new WebSocketClientWrapper(webSocketServer, this);

    webSocketServer->listen(QHostAddress::LocalHost, quint16(54321));

    connect(webSocketClientWrapper, &WebSocketClientWrapper::clientConnected, webChannel, &QWebChannel::connectTo);

    webChannel->registerObject(QStringLiteral("interface"), webState);

    load(QUrl("file:///Users/Jeremy/Programming/oonalysis/src/gui/web/index.html"));
}

void GraphDisplayRegion::startInclusionsRendering() {
    page()->runJavaScript("showInclusions()");
}

} // namespace oonalysis::gui