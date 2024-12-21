#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <iostream>
#include <memory>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>
#include <QFile>

#include "CommunityMainWindow.h"
#include "ui_homewindow.h"
#include "ChatWindow.h"
#include "AddressBookWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {class HomeWindow;}
QT_END_NAMESPACE  

class HomeWindow : public QWidget {
    Q_OBJECT
public:
    HomeWindow(QWidget *parent = nullptr, ClientCommunicator::ptr clientcommunicator = nullptr);
    ~HomeWindow() = default;
    void init();
    
    void initAllWindow();
private slots:
    void showPlayGameWindow();
    void showAddressBookWindow();
    void showChatWindow();
    void showCommunityWindow();
    void showShopWindow();
    void showSettingWindow();
    
public:
    std::shared_ptr<Ui::HomeWindow>  ui_;
    ChatWindow* chatwindow_;
    CommunityMainWindow* communitymainwindow_;
    AddressBookWindow* addressbookwindow_;
    // std::shared_ptr<FriendWindow> friendwidow_;
    ClientCommunicator::ptr clientcommunicator_;
};

#endif // HOMEWINDOW_H
