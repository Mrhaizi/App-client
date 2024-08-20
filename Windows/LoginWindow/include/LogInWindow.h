#ifndef LOGINUI_H
#define LOGINUI_H

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

#include "UserInfoManager.h"
#include "RegisterWindow.h"
#include "ui_new_login.h"
#include "HomeWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {class LoginWindow;}
QT_END_NAMESPACE

class LoginWindow : public QWidget {
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = nullptr, std::shared_ptr<UserInfoManager> infomysql = nullptr);
    ~LoginWindow() = default;
    void applyStylesheet(const QString &qssFile);
private slots:

    void loginButtonClicked();
    void registerButtonClicked();


private:
    std::shared_ptr<Ui::LoginWindow> ui_;
    std::shared_ptr<UserInfoManager> userinfomanager_;
    HomeWindow *homewindow_;
};

#endif //LOGINUI_H