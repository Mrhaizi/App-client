#include "LogInWindow.h"
#include "RegisterWindow.h"
#include "HttpManager.h"
#include "WebSocketMgr.h"
#include "AuthHttpManager.h" 

LoginWindow::LoginWindow(QWidget *parent,  std::shared_ptr<ClientCommunicator> clientcommunicator)
    : QWidget(parent),
    ui_(std::make_shared<Ui::LoginWindow>()),
    clientcommunicator_(clientcommunicator)
{
    clientcommunicator_->connectToHost();
    ui_->setupUi(this);
    ui_->lineEdit_password->setEchoMode(QLineEdit::Password);
    connect(ui_->pushButton_login, &QPushButton::clicked, this, &LoginWindow::loginButtonClicked);
    connect(ui_->pushButton_register, &QPushButton::clicked, this, &LoginWindow::registerButtonClicked);
    // connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_login_mod_finish, this, &LoginWindow::slot_login_mod_finish);
    connect(AuthManager::GetInstance().get(), &AuthManager::loginFinished, this, &LoginWindow::slot_login_mod_finish);
    connect(WebSocketHandler::GetInstance().get(), &WebSocketHandler::initEnd, this, &LoginWindow::changePage);
    initHttpHandlers();
    applyStylesheet(":/res/qss/style-1.qss");
}
void LoginWindow::changePage() {
    homewindow_ = new HomeWindow();
    homewindow_->init();
    homewindow_->show();
    this->close();
}
void LoginWindow::initHttpHandlers() {
    //注册获取登录回包逻辑
    handlers_.insert(ReqId::ID_LOGIN_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            return;
        }
        QString token = jsonObj["token"].toString();
        QString server_ip = jsonObj["ip"].toString();
        QString server_port = jsonObj["port"].toString();
        PersonManager::singleton::getInstance()->setJwdCode(token);
        WebSocketHandler::GetInstance()->connectToServer(server_ip, server_port, token);
    });
}


void LoginWindow::onLoginResponseReceived(const QString &message ) {
    // // 将 QByteArray 转换为 std::string 以便使用 nlohmann::json 解析
    // std::string json_string = message.toStdString();
    // try {
    //     // 解析 JSON 数据
    //     nlohmann::json json_response = nlohmann::json::parse(json_string);
    //     // 检查 responseType 是否为 "LoginResponse"
    //     if (json_response.contains("messagetype") && json_response["messagetype"] == "LoginResponseMessage") {
    //         bool success = json_response["success"].get<bool>();
    //         if (success) {
    //             // 登录成功，打开主窗口
    //             LoginResponseMessage::Info info = json_response.get<LoginResponseMessage::Info>();
    //             // std::string  username = json_response["username"].get<std::string>();
    //             // std::string password = json_response["password"].get<std::string>();
    //             // std::string email = json_response["email"].get<std::string>();
    //             // std::vector<PersonalPublicInfo> friend_list = json_response["friend_list"].get<std::vector<PersonalPublicInfo>>>();
    //             // int age = json_response["age"].get<int>();
    //             // uint64_t  id = json_response["id"].get<uint64_t>();
    //             PersonalPrivateInfo demo_private;
    //             demo_private.password = info.private_info.password;
    //             demo_private.friend_list = info.private_info.friend_list;
    //             demo_private.friend_apply = info.private_info.friend_apply;
    //             PersonalPublicInfo demo_public = {info.public_info.username, info.public_info.id, info.public_info.age, info.public_info.email};
    //             PersonManager::singleton::getInstance()->setPrivateInfo(demo_private);
    //             PersonManager::singleton::getInstance()->setPublicInfo(demo_public);
    //             homewindow_ = new HomeWindow(nullptr, clientcommunicator_);
    //             homewindow_->show();
    //             this->close();
    //         } else {
    //             // 登录失败，显示错误信息
    //             std::string errorMessage = json_response["errorMessage"].get<std::string>();
    //             QMessageBox::warning(this, "Login Failed", QString::fromStdString(errorMessage));
    //         }
    //     } else {
    //         qDebug() << "Unexpected responseType or invalid JSON structure.";
    //     }
    // } catch (nlohmann::json::parse_error &e) {
    //     qDebug() << "JSON parse error: " << e.what();
    // } catch (nlohmann::json::type_error &e) {
    //     qDebug() << "JSON type error: " << e.what();
    // } catch (std::exception &e) {
    //     qDebug() << "Unexpected error: " << e.what();
    // }
}

void LoginWindow::onCacheInfoReceived(const QString& message) {
    // // 将 QByteArray 转换为 std::string 以便使用 nlohmann::json 解析
    // std::string json_string = message.toStdString();
    // try {
    //     // 解析 JSON 数据
    //     nlohmann::json json_response = nlohmann::json::parse(json_string);
    //     // 检查 responseType 是否为 "LoginResponse"
    //     if (json_response.contains("messagetype") && json_response["messagetype"] == "CacheInfo") {
    //         std::vector<PersonalPublicInfo> temp = json_response["public_info_cache"].get<std::vector<PersonalPublicInfo>>();
    //         PersonManager::singleton::getInstance()->getAllPersonalPublicInfo(temp);
    //     } else { 
    //         qDebug() << "Unexpected responseType or invalid JSON structure.";
    //     }
    // } catch (nlohmann::json::parse_error &e) {
    //     qDebug() << "JSON parse error: " << e.what();
    // } catch (nlohmann::json::type_error &e) {
    //     qDebug() << "JSON type error: " << e.what();
    // } catch (std::exception &e) {
    //     qDebug() << "Unexpected error: " << e.what();
    // }
}

bool LoginWindow::checkPwdValid() {

}

bool LoginWindow::checkUserValid() {

}
void LoginWindow::showTip(QString str,bool b_ok) {

}

void LoginWindow::addTipErr(TipErr te,QString tips) {
    tip_errs_[te] = tips;
    showTip(tips, false);
}
void LoginWindow::delTipErr(TipErr te) {
}


void LoginWindow::loginButtonClicked() {
    qDebug()<<"login btn clicked";
    // if(checkUserValid() == false){
    //     auto user_name = ui_->lineEdit_account->text();
    //     if(user_name.isEmpty()){
    //         qDebug() << "user_name empty " ;
    //         addTipErr(TipErr::TIP_EMAIL_ERR, tr("用户名不能为空"));
    //     }
    //     delTipErr(TipErr::TIP_EMAIL_ERR);
    // }
    // if(checkPwdValid() == false){
    // }

    auto user = ui_->lineEdit_account->text();
    auto pwd = ui_->lineEdit_password->text();
    //发送http请求登录
    QJsonObject json_obj;
    json_obj["username"] = user;
    json_obj["password"] = pwd;

    AuthManager::GetInstance()->setBaseUrl("http://localhost:8080");
    AuthManager::GetInstance()->loginUser(user, pwd, ReqId::ID_LOGIN_USER );
    // HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_login"),
    //                                     json_obj, ,Modules::LOGINMOD);
}   

void LoginWindow::registerButtonClicked() {
    // std::shared_ptr<RegisterWindow> register_window = std::make_shared<RegisterWindow>(nullptr, personmanager_);
    RegisterWindow *register_window = new RegisterWindow(nullptr, clientcommunicator_);
    register_window->show();
    this->close();
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
void LoginWindow::slot_login_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"),false);
        return;
    }

    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    //json解析错误
    if(jsonDoc.isNull()){
        showTip(tr("json解析错误"),false);
        return;
    }
    //json解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析错误"),false);
        return;
    }

    //调用对应的逻辑,根据id回调。
    handlers_[id](jsonDoc.object());
    return;
}

