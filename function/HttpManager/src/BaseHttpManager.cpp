#include "BaseHttpManager.h"
#include <QJsonDocument>
#include <QDebug>

BaseHttpManager::BaseHttpManager(QObject* parent)
    : QObject(parent)
{
}

void BaseHttpManager::setBaseUrl(const QString& base_url)
{
    base_url_ = base_url;
}


BaseHttpManager::~BaseHttpManager()
{
}

void BaseHttpManager::sendRequest(QString path, QJsonObject json, QString http_method, ReqId req_id)
{
    QUrl url(base_url_ + path);
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = nullptr;

    if (http_method == "POST") {
        reply = network_manager_.post(request, data);
    } else if (http_method == "PUT") {
        reply = network_manager_.put(request, data);
    } else if (http_method == "DELETE") {
        reply = network_manager_.deleteResource(request);
    } else if (http_method == "GET") {
        reply = network_manager_.get(request);
    }

    if (reply) {
        connect(reply, &QNetworkReply::finished, [this, reply, req_id]() {
            if (reply->error() != QNetworkReply::NoError) {
                qDebug() << "Network error:" << reply->errorString();
                emit requestFinished(req_id, reply->errorString(), ErrorCodes::NETWORK_ERROR);
            } else {
                QString res = reply->readAll();
                emit requestFinished(req_id, res, ErrorCodes::SUCCESS);
            }
            reply->deleteLater();
        });
    } else {
        qDebug() << "Invalid HTTP method:" << http_method;
        emit requestFinished(req_id, "Invalid HTTP method", ErrorCodes::NETWORK_ERROR);
    }

}