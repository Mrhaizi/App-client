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

QT_BEGIN_NAMESPACE
namespace Ui {class ChatWindow;}
QT_END_NAMESPACE

class ChatWindow : public QWidget {
    Q_OBJECT
public:
    ChatWindow(QWidget *parent = nullptr, std::shared_ptr<ClientCommunicator> clientCommunicator = nullptr);
    ~ChatWindow() = default;
    void updateChatWindow();
    void initFriendList();

signals:
    void haveMsg(const QString &text, bool isSentByUser);
private slots:
    void sendMsg();
    void showContextMenu(const QPoint &point);
    void receiveMsg(const QString &message);
    void saveChatHistory();
    void updateFriendList();
    void chooseChatObject(QListWidgetItem *item);
    void addMsg(const QString &text, bool isSentByUser);
private:
    void loatFriendData();
    std::shared_ptr<Ui::ChatWindow> ui_;
    std::shared_ptr<ClientCommunicator> clientcommunicator_;
    PersonalPublicInfo chatobject_;
    QVBoxLayout* m_message_layout;
};

#endif // FRIENDWINDOW_H