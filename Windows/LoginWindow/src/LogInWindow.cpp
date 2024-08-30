#include "LogInWindow.h"
#include "HomeWindow.h"

LoginWindow::LoginWindow(QWidget *parent, std::shared_ptr<UserInfoManager> userinfomanager, std::shared_ptr<ClientCommunicator> clientcommunicator)
    : QWidget(parent),
    ui_(std::make_shared<Ui::LoginWindow>()),
    userinfomanager_(userinfomanager),
    clientcommunicator_(clientcommunicator)
{
    ui_->setupUi(this);
    connect(ui_->pushButton_login, &QPushButton::clicked, this, &LoginWindow::loginButtonClicked);
    connect(ui_->pushButton_register, &QPushButton::clicked, this, &LoginWindow::registerButtonClicked);
    applyStylesheet(":/res/qss/style-1.qss");
}

void LoginWindow::loginButtonClicked() {
    QString username = ui_->lineEdit_account->text();
    QString password = ui_->lineEdit_password->text();    
    if (userinfomanager_->fetchUserInfo(username.toStdString(), password.toStdString())) {
        QMessageBox::information(this, "Login", "Login successful!");
    } else {
        QMessageBox::warning(this, "Login", "Invalid username or password.");
    }
    homewindow_ = new HomeWindow(nullptr, userinfomanager_);
    homewindow_->show();
    this->close();
}   

void LoginWindow::registerButtonClicked() {
    // std::shared_ptr<RegisterWindow> register_window = std::make_shared<RegisterWindow>(nullptr, userinfomanager_);
    RegisterWindow *register_window = new RegisterWindow(nullptr, userinfomanager_);
    register_window->show();
}

void LoginWindow::applyStylesheet(const QString &qssFile) {
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();
    } else {
        std::cout << "path error" << std::endl;
    }
}