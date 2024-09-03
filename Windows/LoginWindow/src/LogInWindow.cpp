#include "LogInWindow.h"

LoginWindow::LoginWindow(QWidget *parent,  std::shared_ptr<ClientCommunicator> clientcommunicator)
    : QWidget(parent),
    ui_(std::make_shared<Ui::LoginWindow>()),
    clientcommunicator_(clientcommunicator)
{
    ui_->setupUi(this);
    connect(ui_->pushButton_login, &QPushButton::clicked, this, &LoginWindow::loginButtonClicked);
    connect(ui_->pushButton_register, &QPushButton::clicked, this, &LoginWindow::registerButtonClicked);
    connect(clientcommunicator_.get(), &ClientCommunicator::messageReceived, this, &LoginWindow::onLoginResponseReceived);

    applyStylesheet(":/res/qss/style-1.qss");
}

void LoginWindow::onLoginResponseReceived(const QString &message ) {
    // 将 QByteArray 转换为 std::string 以便使用 nlohmann::json 解析
    std::string json_string = message.toStdString();

    try {
        // 解析 JSON 数据
        nlohmann::json json_response = nlohmann::json::parse(json_string);

        // 检查 responseType 是否为 "LoginResponse"
        if (json_response.contains("messageType") && json_response["responseType"] == "LoginResponseMessage") {
            bool success = json_response["success"].get<bool>();
            if (success) {
                // 登录成功，打开主窗口
                homewindow_ = new HomeWindow(nullptr, personmanager_);
                homewindow_->show();
                this->close();
            } else {
                // 登录失败，显示错误信息
                std::string errorMessage = json_response["errorMessage"].get<std::string>();
                QMessageBox::warning(this, "Login Failed", QString::fromStdString(errorMessage));
            }
        } else {
            qDebug() << "Unexpected responseType or invalid JSON structure.";
        }
    } catch (nlohmann::json::parse_error &e) {
        qDebug() << "JSON parse error: " << e.what();
    } catch (nlohmann::json::type_error &e) {
        qDebug() << "JSON type error: " << e.what();
    } catch (std::exception &e) {
        qDebug() << "Unexpected error: " << e.what();
    }

}
void LoginWindow::loginButtonClicked() {
    QString username = ui_->lineEdit_account->text();
    QString password = ui_->lineEdit_password->text();    
    LoginRequestMessage login_request = LoginRequestMessage(username.toStdString(), password.toStdString());
    clientcommunicator_->sendMessage(QString::fromStdString(login_request.toJson().dump()));
    
    homewindow_ = new HomeWindow(nullptr, personmanager_);
    homewindow_->show();
    this->close();
}   

void LoginWindow::registerButtonClicked() {
    // std::shared_ptr<RegisterWindow> register_window = std::make_shared<RegisterWindow>(nullptr, personmanager_);
    RegisterWindow *register_window = new RegisterWindow(nullptr, personmanager_);
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

