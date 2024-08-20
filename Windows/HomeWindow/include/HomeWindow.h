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

#include "ui_homewindow.h"
#include "FriendWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {class HomeWindow;}
QT_END_NAMESPACE  

class HomeWindow : public QWidget {
    Q_OBJECT
public:
    HomeWindow(QWidget *parent = nullptr, std::shared_ptr<UserInfoManager> userinfomanager = nullptr);
    ~HomeWindow() = default;
    
    void initAllWindow();
private slots:
    void showPlayGameWindow();
    void showFriendWindow();
    void showGroupWindow();
    void showCommunityWindow();
    void showShopWindow();
    void showSettingWindow();
    
public:
    std::shared_ptr<Ui::HomeWindow>  ui_;
    FriendWindow *friendwindow_;
    std::shared_ptr<UserInfoManager> userinfomanager_;
    // std::shared_ptr<FriendWindow> friendwidow_;
};

#endif // HOMEWINDOW_H