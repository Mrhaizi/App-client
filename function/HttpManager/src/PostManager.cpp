#include "PostHttpManager.h"

PostManager::PostManager(QObject* parent)
    : BaseHttpManager(parent)
{
}

PostManager::~PostManager()
{
}

void PostManager::publishPost(const QString& content, int title_id, ReqId req_id)
{
    QString path =  QString("/posts");
    QJsonObject json;
    json["content"] = content;
    if (title_id != -1)
    {
        json["title_id"] = title_id;
    }
    sendRequest(path, json, "POST", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit publishPostFinished(req_id, response, err);
        }
    });
}

void PostManager::deletePost(int postId, ReqId req_id)
{
    QString path = QString("/posts/%1").arg(postId);
    QJsonObject json;
    sendRequest(path, json, "DELETE", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit deletePostFinished(req_id, response, err);
        }
    });
}

void PostManager::reviewPost(int postId, bool approved, const QString& reason, int categoryId, ReqId req_id)
{
    QString path = QString("/posts/review");
    QJsonObject json;
    json["post_id"] = postId;
    json["approved"] = approved;
    if (!reason.isEmpty())
    {
        json["reason"] = reason;
    }
    if (categoryId != -1)
    {
        json["category_id"] = categoryId;
    }
    sendRequest(path, json, "PUT", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit reviewPostFinished(req_id, response, err);
        }
    });
}

void PostManager::removeTitleFromPost(int postId, ReqId req_id)
{
    QString path = QString("/posts/%1/title").arg(postId);
    QJsonObject json;
    sendRequest(path, json, "DELETE", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit removeTitleFromPostFinished(req_id, response, err);
        }
    });
}

void PostManager::getPosts(const QString& filter, ReqId req_id)
{
    QString path = QString("/posts");
    if (!filter.isEmpty())
    {
        path += QString("?filter=%1").arg(filter);
    }
    QJsonObject json;
    sendRequest(path, json, "GET", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit getPostsFinished(req_id, response, err);
        }
    });
}

void PostManager::assignPostToCategory(int postId, int category_id, ReqId req_id)
{
    QString path = QString("/posts/%1/category").arg(postId);
    QJsonObject json;
    json["category_id"] = category_id;
    sendRequest(path, json, "PUT", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit assignPostToCategoryFinished(req_id, response, err);
        }
    });
}

void PostManager::getPostsUnderCategory(int title_id, int category_id, ReqId req_id)
{
    QString path = QString("/titles/%1/categories/%2/posts").arg(title_id).arg(category_id);
    QJsonObject json;
    sendRequest(path, json, "GET", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit getPostsUnderCategoryFinished(req_id, response, err);
        }
    });
}
