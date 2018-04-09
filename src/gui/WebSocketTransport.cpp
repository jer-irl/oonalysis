#include "WebSocketTransport.hpp"

#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

namespace oonalysis::gui {

/*!
    Construct the transport object and wrap the given socket.
    The socket is also set as the parent of the transport object.
*/
WebSocketTransport::WebSocketTransport(QWebSocket *socket)
        : QWebChannelAbstractTransport(socket), m_socket(socket) {
    connect(socket, &QWebSocket::textMessageReceived,
            this, &WebSocketTransport::textMessageReceived);
}

/*!
    Destroys the WebSocketTransport.
*/
WebSocketTransport::~WebSocketTransport() {

}

/*!
    Serialize the JSON message and send it as a text message via the WebSocket to the client.
*/
void WebSocketTransport::sendMessage(const QJsonObject &message) {
    QJsonDocument doc(message);
    m_socket->sendTextMessage(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}

/*!
    Deserialize the stringified JSON messageData and emit messageReceived.
*/
void WebSocketTransport::textMessageReceived(const QString &messageData) {
    QJsonParseError error;
    QJsonDocument message = QJsonDocument::fromJson(messageData.toUtf8(), &error);
    if (error.error) {
        qWarning() << "Failed to parse text message as JSON object:" << messageData
                   << "Error is:" << error.errorString();
        return;
    } else if (!message.isObject()) {
        qWarning() << "Received JSON message that is not an object: " << messageData;
        return;
    }
    emit messageReceived(message.object(), this);
}

} // namespace oonalysis::gui