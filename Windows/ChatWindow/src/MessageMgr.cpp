#include "MessageMgr.h"
#include "WebSocketMgr.h"

MessageManager::MessageManager(QObject *parent)
    : QObject(parent) {

    connect(WebSocketHandler::GetInstance().get(), &WebSocketHandler::chatmessageReceived,
            this, &MessageManager::handlePrivateMessage);

    connect(WebSocketHandler::GetInstance().get(), &WebSocketHandler::groupMessageReceived,
            this, &MessageManager::handleGroupMessage);
}
void MessageManager::addPrivateMessage(uint64_t user_id, const ChatMessage &msg) {
    QMutexLocker locker(&mutex_);
    privateMessages_[user_id].append(msg);
    emit privateMessageDispatched(user_id, msg); // 分发消息信号
}

void MessageManager::addGroupMessage(uint64_t group_id, const ChatMessage &msg) {
    QMutexLocker locker(&mutex_);
    groupMessages_[group_id].append(msg);
    emit groupMessageDispatched(group_id, msg); // 分发消息信号
}

QVector<ChatMessage> MessageManager::getPrivateMessages(uint64_t userId) const {
    QMutexLocker locker(&mutex_);
    return privateMessages_.value(userId);
}

QVector<ChatMessage> MessageManager::getGroupMessages(uint64_t groupId) const {
    QMutexLocker locker(&mutex_);
    return groupMessages_.value(groupId);
}

void MessageManager::handlePrivateMessage(const QJsonObject &msg) {
    ChatMessage chat_msg;
    chat_msg.castFromJsonObject(msg); // 假设有一个方法将 JSON 转换为 ChatMessage
    std::cout << chat_msg.getConent() << std::endl;
    uint64_t user_id = msg["from_user_id"].toString().toULongLong();
    chat_msg.setSendByUser(false);
    addPrivateMessage(user_id, chat_msg);
}

void MessageManager::handleGroupMessage(const QJsonObject &msg) {
    ChatMessage group_msg;
    group_msg.castFromJsonObject(msg);
    uint64_t groupId = msg["group_id"].toString().toULongLong();
    addGroupMessage(groupId, group_msg);
}
