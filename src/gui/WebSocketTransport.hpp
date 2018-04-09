#ifndef GUI_WEBSOCKETTRANSPORT_HPP
#define GUI_WEBSOCKETTRANSPORT_HPP

#include <QWebChannelAbstractTransport>
#include <QWebSocket>

namespace oonalysis::gui {

class WebSocketTransport : public QWebChannelAbstractTransport {
public:
    explicit WebSocketTransport(QWebSocket *socket);
    virtual ~WebSocketTransport();

    void sendMessage(const QJsonObject &message) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void textMessageReceived(const QString &message);

private:
    QWebSocket *m_socket;
};

} // namespace oonalysis::gui

#endif // GUI_WEBSOCKETTRANSPORT_HPP