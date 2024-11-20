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

#include "PersonManager.h"
#include "ui_new_login.h"
#include "CommunicatorClient.h"
#include "HomeWindow.h"
#include "LoginMessage.h"
#include "nlohmann/json.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {class LoginWindow;}
QT_END_NAMESPACE

class LoginWindow : public QWidget {
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = nullptr, std::shared_ptr<ClientCommunicator> clientcommunicator = nullptr);
    ~LoginWindow() = default;
    void applyStylesheet(const QString &qssFile);
    bool checkUserValid();
    bool checkPwdValid();

private slots:
    void onLoginResponseReceived(const QString &message);
    void loginButtonClicked();
    void registerButtonClicked();
    void onCacheInfoReceived(const QString& mesage);
    void slot_login_mod_finish(ReqId id, QString res, ErrorCodes err);
    void changePage();
private:
    void showTip(QString str,bool b_ok);
    void addTipErr(TipErr te,QString tips);
    void delTipErr(TipErr te);
    void initHttpHandlers();
    std::shared_ptr<Ui::LoginWindow> ui_;
    std::shared_ptr<PersonManager> personmanager_;
    HomeWindow *homewindow_;
    std::shared_ptr<ClientCommunicator> clientcommunicator_;
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;
    QMap<TipErr, QString> tip_errs_;
};

#endif //LOGINUI_H
