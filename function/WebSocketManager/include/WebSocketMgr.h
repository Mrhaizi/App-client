#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QWebSocket>
#include "Singleton2.hpp"

class WebSocketHandler : public QObject , public Singleton2<WebSocketHandler> {
    Q_OBJECT
    friend class  Singleton2<WebSocketHandler>;
public:
    void connectToServer(const QString& server_ip, const QString& server_port, const QString& token);
    ~WebSocketHandler();
    void sendMessage(const QJsonObject& message);
signals:
    void messageReceived(const QJsonObject& message);
    void connected();
    void disconnected();
    void errorOccurred(const QString& error);
private slots:
    void onMessageReceived(const QString& message);
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);
private:
    explicit WebSocketHandler(QObject* parent = nullptr);
    inline static QWebSocket webSocket_;
};

#endif // WEBSOCKETHANDLER_H
