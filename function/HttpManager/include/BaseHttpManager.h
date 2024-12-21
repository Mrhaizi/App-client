#ifndef BASEHTTPMANAGER_H
#define BASEHTTPMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QUrl>

#include "global.h"

class BaseHttpManager : public QObject
{
    Q_OBJECT
public:
    explicit BaseHttpManager(QObject* parent = nullptr);
    virtual ~BaseHttpManager();
    static void setBaseUrl(const QString& base_url);
    static QString getBaseUrl(const QString& baseUrl) {return base_url_;}
protected:
    void sendRequest(QString url, QJsonObject json, QString httpMethod, ReqId req_id);
signals:
    void requestFinished(ReqId req_id, QString response, ErrorCodes err);

private:
    QNetworkAccessManager network_manager_;
    inline static QString base_url_;
};

#endif // BASEHTTPMANAGER_H