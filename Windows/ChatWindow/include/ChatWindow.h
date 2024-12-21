#ifndef FRIENDWINDOW_H
#define FRIENDWINDOW_H

#include <iostream>
#include <qlist.h>
#include <string>
#include <memory>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>
#include <QFile>
#include <QtWidgets/QMenu>
#include <QThread>

#include "ui_chatwindow.h"
#include "CommunicatorClient.h"
#include "FriendChatListItem.h"
#include "global.h"
#include "ChatMessage.h"
#include "PersonManager.h"
#include "ConnectPool.h"
#include "ServerConfigManager.h"
#include "WebSocketMgr.h"
#include "MessageMgr.h"

QT_BEGIN_NAMESPACE
namespace Ui {class ChatWindow;}
QT_END_NAMESPACE

class ChatWindow : public QWidget {
    Q_OBJECT
public:
    ChatWindow(QWidget *parent = nullptr, std::shared_ptr<ClientCommunicator> clientCommunicator = nullptr);
    ~ChatWindow() = default;
    void updateChatWindow();
    void init();
signals:
    void haveMsg(const QString &text, bool isSentByUser);
private slots:
    void sendMsg();
    void machineMsg(const QJsonObject& msg);
    void showContextMenu(const QPoint& point);
    void saveChatHistory();
    void updateFriendList();
    void addtextMsg(const QString &text, bool isSentByUser);
    void handlePrivateMessage(uint64_t userId, const ChatMessage &msg);
    void handleGroupMessage(uint64_t groupId, const ChatMessage &msg);
    void switchChatObject(QListWidgetItem *item);
private:
    void loadChatHistory(uint64_t chatId); 
    void markMessageAsUnread(uint64_t senderId);
    void updateUnreadCount(uint64_t chatId);
    void initFriendList();
    void loatFriendData();
    uint64_t currentChatId_; // 当前聊天对象的 ID
    QMap<uint64_t, int> unreadCounts_; // 未读消息计数
    std::shared_ptr<Ui::ChatWindow> ui_;
    std::shared_ptr<ClientCommunicator> clientcommunicator_;
    PersonalPublicInfo chatobject_;
    QVBoxLayout* m_message_layout;
    MessageManager* message_mgr_;
};

#endif // FRIENDWINDOW_H
