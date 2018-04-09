#ifndef GUI_WEBSOCKETCLIENTWRAPPER_HPP
#define GUI_WEBSOCKETCLIENTWRAPPER_HPP

#include <QWebSocketServer>
#include "WebSocketTransport.hpp"

namespace oonalysis::gui{

class WebSocketClientWrapper : public QObject
{
    Q_OBJECT

public:
    WebSocketClientWrapper(QWebSocketServer *server, QObject *parent = 0);

Q_SIGNALS:
    void clientConnected(WebSocketTransport* client);
private Q_SLOTS:
    void handleNewConnection();

private:
    QWebSocketServer *m_server;
};


} // namespace oonalysis::gui

#endif // GUI_WEBSOCKETCLIENTWRAPPER_HPP