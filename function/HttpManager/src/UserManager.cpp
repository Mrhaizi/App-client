#include "UserHttpManager.h"

UserManager::UserManager(QObject* parent)
    : BaseHttpManager(parent)
{
}

UserManager::~UserManager()
{
}

void UserManager::followUser(int following_id, ReqId req_id)
{
    QString path = QString("/users/%1/follow").arg(following_id);
    QJsonObject json;
    sendRequest(path, json, "POST", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit followUserFinished(req_id, response, err);
        }
    });
}

void UserManager::getFollowings(int user_id, ReqId req_id)
{
    QString path = QString("/users/%1/followings").arg(user_id);
    QJsonObject json;
    sendRequest(path, json, "GET", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit getFollowingsFinished(req_id, response, err);
        }
    });
}
