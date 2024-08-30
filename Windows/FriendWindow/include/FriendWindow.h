#ifndef FRIENDWINDOW_H
#define FRIENDWINDOW_H

#include <iostream>
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

#include "ui_friendwindow.h"
#include "UserInfoManager.h"
#include "FriendListItem.h"
#include "ConnectPool.h"

QT_BEGIN_NAMESPACE
namespace Ui {class FriendWindow;}
QT_END_NAMESPACE

class FriendWindow : public QWidget {
    Q_OBJECT
public:
    FriendWindow(QWidget *parent = nullptr, std::shared_ptr<UserInfoManager> userInfoManager = nullptr, std::shared_ptr<ClientCommunicator> clientCommunicator = nullptr);
    ~FriendWindow() = default;
    void updateChatWindow();
    void initFriendList();
private slots:
    void sendMsg();
    void showContextMenu(const QPoint &point);
    void saveChatHistory();
    void updateFriendList();
private:
    void loatFriendData();
    std::shared_ptr<Ui::FriendWindow> ui_;
    std::shared_ptr<UserInfoManager>  userinfomanager_;    
    std::shared_ptr<ClientCommunicator> clientcommunicator_;
};

#endif // FRIENDWINDOW_H