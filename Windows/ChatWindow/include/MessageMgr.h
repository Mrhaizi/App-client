#ifndef MESSAGEMGR_H
#define MESSAGEMGR_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QMutex>
#include <QJsonObject>
#include <QString>
#include "ChatMessage.h"

class MessageManager : public QObject {
    Q_OBJECT
public:
    explicit MessageManager(QObject *parent = nullptr);
    ~MessageManager() = default;

    // 添加消息
    void addPrivateMessage(uint64_t userId, const ChatMessage &msg);
    void addGroupMessage(uint64_t groupId, const ChatMessage &msg);

    // 获取消息历史
    QVector<ChatMessage> getPrivateMessages(uint64_t userId) const;
    QVector<ChatMessage> getGroupMessages(uint64_t groupId) const;

signals:
    // 分发私聊和群聊消息信号
    void privateMessageDispatched(uint64_t userId, const ChatMessage &msg);
    void groupMessageDispatched(uint64_t groupId, const ChatMessage &msg);

public slots:
    // 处理消息的统一入口
    void handlePrivateMessage(const QJsonObject &msg);
    void handleGroupMessage(const QJsonObject &msg);

private:
    QMap<uint64_t, QVector<ChatMessage>> privateMessages_; // 私聊消息缓存
    QMap<uint64_t, QVector<ChatMessage>> groupMessages_;   // 群聊消息缓存
    mutable QMutex mutex_; // 线程安全锁
};

#endif // MESSAGEMGRH
