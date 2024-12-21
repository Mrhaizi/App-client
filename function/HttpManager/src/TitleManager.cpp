#include "TitleHttpManager.h"

TitleManager::TitleManager(QObject* parent)
    : BaseHttpManager(parent)
{
}

TitleManager::~TitleManager()
{
}

void TitleManager::applyTitle(const QString& title_name, ReqId req_id)
{
    QString path = QString("/titles");
    QJsonObject json;
    json["title_name"] = title_name;
    sendRequest(path, json, "POST", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit applyTitleFinished(req_id, response, err);
        }
    });
}

void TitleManager::approveTitle(int title_id, bool approved, ReqId req_id)
{
    QString path = QString("/titles/%1/approval").arg(title_id);
    QJsonObject json;
    json["approved"] = approved;
    sendRequest(path, json, "PUT", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit approveTitleFinished(req_id, response, err);
        }
    });
}

void TitleManager::searchTitles(const QString& title_name, ReqId req_id)
{
    QString path = QString("/titles/search?title_name=%1").arg(title_name);
    QJsonObject json;
    sendRequest(path, json, "GET", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit searchTitlesFinished(req_id, response, err);
        }
    });
}

void TitleManager::getPostsUnderTitle(int title_id, ReqId req_id)
{
    QString path = QString("/titles/%1/posts").arg(title_id);
    QJsonObject json;
    sendRequest(path, json, "GET", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit getPostsUnderTitleFinished(req_id, response, err);
        }
    });
}

void TitleManager::getCategoriesUnderTitle(int title_id, ReqId req_id)
{
    QString path = QString("/titles/%1/categories").arg(title_id);
    QJsonObject json;
    sendRequest(path, json, "GET", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit getCategoriesUnderTitleFinished(req_id, response, err);
        }
    });
}
