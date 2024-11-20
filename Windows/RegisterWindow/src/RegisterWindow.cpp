#include "RegisterWindow.h"
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include "HttpManager.h"
#include "LogInWindow.h"
#include "RegisterMessage.h"
#include "RegisterMessage.h"
#include "HttpManager.h"

RegisterWindow::RegisterWindow(QWidget *parent, std::shared_ptr<ClientCommunicator> clientcommunicator)
                                 : clientcommunicator_(clientcommunicator) , 
                                    ui_(std::make_shared<Ui::RegisterWindow>()) 
                                    {
                                    ui_->setupUi(this);
                                    ui_->lineEdit_password_r->setEchoMode(QLineEdit::Password);
                                    ui_->lineEdit_define_password->setEchoMode(QLineEdit::Password);
                                    m_timer = new QTimer(this);
                                    connect(ui_->pushButton_register, &QPushButton::clicked, this, &RegisterWindow::slot_registerUserInfo);
                                    connect(ui_->pushButton_back, &QPushButton::clicked, this, &RegisterWindow::slot_backLoginWindow);
                                    connect(m_timer, &QTimer::timeout, this, &RegisterWindow::slot_updateButtonText);
                                    connect(ui_->pushButton_get_verifycode, &QPushButton::clicked, this, &RegisterWindow::slot_getVerifyCode);
                                    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterWindow::slot_reg_mod_finish);
                                    initHttpHandlers();
                                    }
void RegisterWindow::slot_registerUserInfo() {
    if(ui_->lineEdit_username_r->text() == ""){
        showTip(tr("用户名不能为空"), false);
        return;
    }

    if(ui_->lineEdit_email->text() == ""){
        showTip(tr("邮箱不能为空"), false);
        return;
    }

    if(ui_->lineEdit_password_r->text() == ""){
        showTip(tr("密码不能为空"), false);
        return;
    }

    if(ui_->lineEdit_define_password->text() == ""){
        showTip(tr("确认密码不能为空"), false);
        return;
    }

    if(ui_->lineEdit_define_password->text() != ui_->lineEdit_password_r->text()){
        showTip(tr("密码和确认密码不匹配"), false);
        return;
    }

    if(ui_->lineEdit_verify_code->text() == ""){
        showTip(tr("验证码不能为空"), false);
        return;
    }
    QString username = ui_->lineEdit_username_r->text();
    QString password = ui_->lineEdit_password_r->text();
    QString email = ui_->lineEdit_email->text();
    QString password_defined = ui_->lineEdit_define_password->text();
    QJsonObject json_obj;
    json_obj["user"] = ui_->lineEdit_username_r->text();
    json_obj["email"] = ui_->lineEdit_email->text();
    json_obj["password"] = ui_->lineEdit_password_r->text();
    json_obj["confirm"] = ui_->lineEdit_define_password->text();
    json_obj["varifycode"] = ui_->lineEdit_verify_code->text();
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_register"),
                 json_obj, ReqId::ID_REG_USER,Modules::REGISTERMOD);

}
void RegisterWindow::slot_backLoginWindow() {
    // 创建并显示登录窗口
    LoginWindow *loginWindow = new LoginWindow(nullptr, clientcommunicator_);
    loginWindow->show();
    // 关闭当前注册窗口
    this->close();
}      

void RegisterWindow::slot_getVerifyCode() {
    //验证邮箱的地址正则表达式
    auto email = ui_->lineEdit_email->text();
    // 邮箱地址的正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(match){
        // 发送http请求获取验证码
        QJsonObject json_obj;
        json_obj["email"] = email;
        HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/get_varifycode"),
                    json_obj, ReqId::ID_GET_VARIFY_CODE,Modules::REGISTERMOD);
        startVerificationCountdown();
    }else{
        //提示邮箱不正确
        showTip(tr("邮箱地址不正确"),false);
    }
}

void RegisterWindow::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
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
    _handlers[id](jsonDoc.object());
    return;
}

void RegisterWindow::initHttpHandlers()
{
    //注册获取验证码回包逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已发送到邮箱，注意查收"), true);
        qDebug()<< "email is " << email ;
    });

    //注册注册用户回包逻辑
    _handlers.insert(ReqId::ID_REG_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("用户注册成功"), true);
        qDebug()<< "email is " << email ;
        qDebug()<< "user uuid is " <<  jsonObj["uid"].toString();
    });
}

void RegisterWindow::showTip(QString str, bool b_ok)
{
    if(b_ok){
         ui_->err_tip->setProperty("state","normal");
    }else{
        ui_->err_tip->setProperty("state","err");
    }
    ui_->err_tip->setText(str);
    repolish(ui_->err_tip);
}
void RegisterWindow::startVerificationCountdown() {
    QString email = ui_->lineEdit_email->text();
    VerifyCodeMessage email_msg = VerifyCodeMessage(email.toStdString());
    clientcommunicator_->sendMessage(SendVerifyCode, QString::fromStdString(email_msg.toJson().dump()).toUtf8());
    m_counttime = 60; // 重置倒计时时间
    ui_->pushButton_get_verifycode->setText("验证码已发送 (" + QString::number(m_counttime) + "s)");
    ui_->pushButton_get_verifycode->setEnabled(false); // 禁用按钮
    m_timer->start(1000); // 启动定时器，每秒更新一次
}

void RegisterWindow::slot_updateButtonText() {
    if (m_counttime > 0) {
        --m_counttime;
        ui_->pushButton_get_verifycode->setText("验证码已发送 (" + QString::number(m_counttime) + "s)");
    } else {
        m_timer->stop();  // 停止定时器
        ui_->pushButton_get_verifycode->setText("获取验证码");
        ui_->pushButton_get_verifycode->setEnabled(true); // 重新启用按钮
    }
}