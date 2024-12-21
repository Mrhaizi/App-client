#ifndef CHECKHTTPMANAGRR_H
#define CHECKHTTPMANAGER_H

#include "BaseHttpManager.h"
#include "Singleton2.hpp"

class CheckHttpManager : public BaseHttpManager, public Singleton2<CheckHttpManager>
{
    Q_OBJECT
    friend class Singleton2<CheckHttpManager>;

private:
    explicit CheckHttpManager(QObject* parent = nullptr);
    ~CheckHttpManager();

public:
    void createCategory(int title_id, const QString& category_name, const QString& description, ReqId req_id);
    void deleteCategory(int category_id, ReqId req_id);

signals:
    void createCategoryFinished(ReqId req_id, QString response, ErrorCodes err);
    void deleteCategoryFinished(ReqId req_id, QString response, ErrorCodes err);
};

#endif // CHECKHTPPMANAGER_H