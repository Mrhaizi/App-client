#ifndef CATEGORYHTTPMANAGER_H
#define CATEGORYHTTPMANAGER_H

#include "BaseHttpManager.h"
#include "Singleton2.hpp"


class CategoryManager : public BaseHttpManager, public Singleton2<CategoryManager>
{
    Q_OBJECT
    friend class Singleton2<CategoryManager>;

private:
    explicit CategoryManager(QObject* parent = nullptr);
    ~CategoryManager();

public:
    void createCategory(int title_id, const QString& category_name, const QString& description, ReqId req_id);
    void deleteCategory(int category_id, ReqId req_id);

signals:
    void createCategoryFinished(ReqId req_id, QString response, ErrorCodes err);
    void deleteCategoryFinished(ReqId req_id, QString response, ErrorCodes err);
};
#endif // CATEGORYHTTPMANAGRE_H
