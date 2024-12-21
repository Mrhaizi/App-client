#include "AuthHttpManager.h"

AuthManager::AuthManager(QObject* parent)
    : BaseHttpManager(parent)
{
}

void AuthManager::registerUser(const QString& username, const QString& password, ReqId req_id)
{
    QString path =  QString("/register");
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;
    sendRequest(path, json, "POST", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit registerFinished(req_id, response, err);
        }
    });
}

void AuthManager::loginUser(const QString& username, const QString& password, ReqId req_id)
{
    QString path = QString("/user_login");
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;
    sendRequest(path, json, "POST", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit loginFinished(req_id, response, err);
        }
    });
}

void AuthManager::resetPassword(const QString& username, const QString& new_password, ReqId req_id)
{
    QString path = QString("/reset_password");
    QJsonObject json;
    json["username"] = username;
    json["new_password"] = new_password;
    sendRequest(path, json, "PUT", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit resetPasswordFinished(req_id, response, err);
        }
    });
}
