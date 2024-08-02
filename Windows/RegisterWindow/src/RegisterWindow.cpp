#include "RegisterWindow.h"
RegisterWindow::RegisterWindow(QWidget *parent, std::shared_ptr<UserInfoManager> userinfomanager)
                                 : infomanager_(userinfomanager) , 
                                    ui_(std::make_shared<Ui::RegisterWindow>()) 
                                    {
                                    ui_->setupUi(this);
                                    connect(ui_->pushButton_register, &QPushButton::clicked, this, &RegisterWindow::registerUserInfo);
                                    // connect(ui_->pushButton_back, &QPushButton::clicked, this, &RegisterWindow::backLoginWindow);
                                    }

void RegisterWindow::registerUserInfo() {
    QString username = ui_->lineEdit_username->text();
    QString password = ui_->lineEdit_password->text();
    QString password_defined = ui_->lineEdit_define_password->text();
    // 验证输入的密码是否一致
    if (password != password_defined) {
        QMessageBox::warning(this, "Register", "请两次密码输入一致");
        return;
    }
    // 检查用户名是否已存在
    if (infomanager_->fetchUserName(username.toStdString())) {
        QMessageBox::warning(this, "Register", "your username had been used");
        return;
    }
    // 注册用户信息
    infomanager_->registerUserInfo(username.toStdString(), password.toStdString());
    QMessageBox::information(this, "Register", "registe successfully");
}

// void RegisterWindow::backLoginWindow() {
//     // 创建并显示登录窗口
//     LoginWindow *loginWindow = new LoginWindow(nullptr, infomanager_);
//     loginWindow->show();

//     // 关闭当前注册窗口
//     this->close();
// }      