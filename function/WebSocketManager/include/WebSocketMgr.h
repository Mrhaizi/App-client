#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QWebSocket>
#include "Singleton2.hpp"
#include "PersonManager.h"

class WebSocketHandler : public QObject , public Singleton2<WebSocketHandler> {
    Q_OBJECT
    friend class  Singleton2<WebSocketHandler>;
public:
    void connectToServer(const QString& server_ip, const QString& server_port, const QString& token);
    ~WebSocketHandler();
    void sendMessage(const QJsonObject& message);
signals:
    void messageReceived(const QJsonObject& message);
    void chatmessageReceived(const QJsonObject& message);
    void cachemessageReceived(const QJsonObject& message);
    void connected();
    void disconnected();
    void errorOccurred(const QString& error);
    void allUsersReceived(const QJsonArray& users);
    void friendsReceived(const QJsonArray& friends);
    void friendRequestsReceived(const QJsonArray& requests);
    void offlineMessagesReceived(const QJsonArray& messages);
    void friendRequestReceived(const QJsonObject& messages);
    void groupMessageReceived(const QJsonObject& messages);
    void joinRequestResponse(const QJsonObject& messages);
    void removedFromGroup(uint64_t id);
    void postReceived(const QJsonObject& message);
    void initEnd();
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
