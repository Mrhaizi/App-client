#include "CategoryHttpManager.h"

CategoryManager::CategoryManager(QObject* parent)
    : BaseHttpManager(parent)
{
}

CategoryManager::~CategoryManager()
{
}

void CategoryManager::createCategory(int title_id, const QString& category_name, const QString& description, ReqId req_id)
{
    QString  path = QString("/titles/%1/categories").arg(title_id);
    QJsonObject json;
    json["category_name"] = category_name;
    json["description"] = description;
    sendRequest(path, json, "POST", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit createCategoryFinished(req_id, response, err);
        }
    });
}

void CategoryManager::deleteCategory(int category_id, ReqId req_id)
{
    QString path = QString("/categories/%1").arg(category_id);
    QJsonObject json;
    sendRequest(path, json, "DELETE", req_id);

    connect(this, &BaseHttpManager::requestFinished, this, [this, req_id](ReqId rId, QString response, ErrorCodes err) {
        if (rId == req_id) {
            emit deleteCategoryFinished(req_id, response, err);
        }
    });
}
