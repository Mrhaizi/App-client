#include "WebSocketMgr.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

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
    QJsonObject obj = doc.object();
    emit messageReceived(obj);
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
