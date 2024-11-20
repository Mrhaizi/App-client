#ifndef REGISTERUI_H
#define REGISTERUI_H

#include <iostream>
#include <memory>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>
#include <QMap>
#include <QJsonObject>
#include <QSet>
#include <QTimer>
#include <QTimer>
#include <QRandomGenerator>
#include "PersonManager.h"
#include "ui_register.h"

QT_BEGIN_NAMESPACE 
namespace Ui {class RegisterWindow;}
QT_END_NAMESPACE

class RegisterWindow : public QWidget {
    Q_OBJECT
public:
    RegisterWindow(QWidget *parent, std::shared_ptr<ClientCommunicator> clientcommunicator);
    ~RegisterWindow() = default;
    void startVerificationCountdown();  // 开始验证码倒计时
private slots:
    void slot_registerUserInfo();
    void slot_getVerifyCode();
    void slot_updateButtonText();            // 更新按钮文本
    void slot_backLoginWindow();
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
private:
    void changeTipPage();
    void showTip(QString str, bool b_ok);
    void initHttpHandlers();
    std::string m_code = "";
    bool success = false;
    std::shared_ptr<PersonManager> infomanager_;
    std::shared_ptr<Ui::RegisterWindow> ui_;
    std::shared_ptr<ClientCommunicator> clientcommunicator_;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    QTimer* m_timer; 
    int m_counttime;
};


#endif // REGISTERUI_H
