#include "WebSocketMgr.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>

// 获取单例实例

WebSocketHandler::WebSocketHandler(QObject* parent) : QObject(parent) {
    connect(&webSocket_, &QWebSocket::connected, this, &WebSocketHandler::onConnected);
    connect(&webSocket_, &QWebSocket::disconnected, this, &WebSocketHandler::onDisconnected);
    connect(&webSocket_, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onMessageReceived);
    connect(&webSocket_, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &WebSocketHandler::onError);
}

WebSocketHandler::~WebSocketHandler() {
    webSocket_.close();
}

// 连接到服务器
void WebSocketHandler::connectToServer(const QString& serverIp, const QString& serverPort, const QString& token) {
    if (webSocket_.state() == QAbstractSocket::UnconnectedState) {

        // 将 token 作为查询参数附加到 WebSocket URL 中
        QUrl url(QString("ws://%1:%2?token=%3").arg(serverIp).arg(serverPort).arg(token));
        qDebug() << "正在连接到 WebSocket 服务器:" << url.toString();
        webSocket_.open(url);
    } else {
        qDebug() << "WebSocket 已连接或正在连接";
    }
}

// 发送消息
void WebSocketHandler::sendMessage(const QJsonObject& message) {
    if (webSocket_.state() == QAbstractSocket::ConnectedState) {
        QJsonDocument doc(message);
        webSocket_.sendTextMessage(doc.toJson(QJsonDocument::Compact));
    } else {
        qDebug() << "WebSocket 未连接，无法发送消息";
    }
}

// 收到消息
void WebSocketHandler::onMessageReceived(const QString& message) {
   QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject())
    {
        qWarning() << "Invalid message format!";
        return;
    }
    QJsonObject obj = doc.object();
    QString type = obj.value("type").toString();
    if (type == "init") {
    // 解析 init 消息的各个字段
    QJsonArray all_users = obj.value("all_users").toArray();
    QJsonArray friends = obj.value("friends").toArray();
    QJsonArray friend_requests = obj.value("friend_requests").toArray();
    QJsonArray offline_messages = obj.value("offline_messages").toArray();
    QJsonArray offline_group_messages = obj.value("offline_group_messages").toArray();
    QJsonArray group_notifications = obj.value("group_notifications").toArray();
    QJsonArray pending_requests = obj.value("pending_requests").toArray();
    QJsonObject user_info = obj.value("user_info").toObject();
    PersonManager::singleton::getInstance()->initPersonalInfo(user_info, friends);
    PersonManager::singleton::getInstance()->initCacheInfo(all_users);
    PersonManager::singleton::getInstance()->initOfflineRequest(friend_requests, pending_requests);
    PersonManager::singleton::getInstance()->initOfflineMessage(offline_messages, offline_group_messages, group_notifications);
    PersonManager::singleton::getInstance()->initInfo();
    emit initEnd();
    } else if (type == "rec_chat_msg") {
        // 解析私聊消息
        QJsonObject chat_msg = obj.value("message").toObject();
        emit chatmessageReceived(chat_msg);

    } else if (type == "rec_friend_request") {
        // 解析好友申请
        QJsonObject friend_request = obj.value("request").toObject();
        emit friendRequestReceived(friend_request);

    } else if (type == "rec_group_message") {
        // 解析群聊消息
        QJsonObject group_message = obj.value("message").toObject();
        emit groupMessageReceived(group_message);
    } else if (type == "join_request_response") {
        // 处理群组加入申请的结果
        QJsonObject join_response = obj.value("response").toObject();
        emit joinRequestResponse(join_response);
    } else if (type == "removed_from_group") {
        // 解析被移出群组的通知
        int group_id = obj.value("group_id").toInt();
        emit removedFromGroup(group_id);
    }else if(type == "removed_from_group"){
        
    } else {
        // 未知消息类型，打印日志
        qDebug() << "Unknown message type:" << type << ", content:" << obj;
    }
}
// 连接成功
void WebSocketHandler::onConnected() {
    qDebug() << "WebSocket 已连接";
    emit connected();
}

// 断开连接
void WebSocketHandler::onDisconnected() {
    qDebug() << "WebSocket 已断开连接";
    emit disconnected();
}

// 错误处理
void WebSocketHandler::onError(QAbstractSocket::SocketError error) {
    qDebug() << "WebSocket 错误:" << webSocket_.errorString();
    emit errorOccurred(webSocket_.errorString());
}
