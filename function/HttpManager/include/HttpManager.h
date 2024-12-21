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
    // Community 
    void ApplyTitle(const QString& title_name, ReqId req_id);
    void ApproveTitle(int title_id, bool approved, ReqId req_id);
    void PublishPost(const QString& content, int title_id, ReqId req_id);
    void DeletePost(int post_id, ReqId req_id);
    void ReviewPost(int post_id, bool approved, const QString& reason, int category_id, ReqId req_id);
    void RemoveTitleFromPost(int post_id, ReqId req_id);
    void FollowUser(int following_id, ReqId req_id);
    void GetFollowings(int user_id, ReqId req_id);
    void GetPosts(const QString& filter, ReqId req_id);
    void SearchTitles(const QString& title_name, ReqId req_id);
    void GetPostsUnderTitle(int title_id, ReqId req_id);
    void CreateCategory(int title_id, const QString& category_name, const QString& description, ReqId req_id);
    void DeleteCategory(int category_id, ReqId req_id);
    void AssignPostToCategory(int post_id, int category_id, ReqId req_id);
    void GetCategoriesUnderTitle(int title_id, ReqId req_id);
    void GetPostsUnderCategory(int title_id, int category_id, ReqId req_id);

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
