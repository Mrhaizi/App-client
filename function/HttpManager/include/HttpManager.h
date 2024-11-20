#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "Singleton2.hpp"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QDir>
#include <QSettings>
#include "global.h"


class HttpMgr:public QObject, public Singleton2<HttpMgr>,
        public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
    friend class Singleton2<HttpMgr>;
public:
    ~HttpMgr();
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
private:
    HttpMgr();
    QNetworkAccessManager _manager;
public slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    //注册模块http相关请求完成发送此信号
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_reset_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_login_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMGR_H
