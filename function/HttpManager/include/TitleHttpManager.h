#ifndef TITLEHTTPMANAGER_H
#define TITLEHTTPMANAGER_H

#include "BaseHttpManager.h"
#include "Singleton2.hpp"

class TitleManager : public BaseHttpManager, public Singleton2<TitleManager>
{
    Q_OBJECT
    friend class Singleton2<TitleManager>;

private:
    explicit TitleManager(QObject* parent = nullptr);
    ~TitleManager();

public:
    void applyTitle(const QString& title_name, ReqId req_id);
    void approveTitle(int title_id, bool approved, ReqId req_id);
    void searchTitles(const QString& title_name, ReqId req_id);
    void getPostsUnderTitle(int title_id, ReqId req_id);
    void getCategoriesUnderTitle(int title_id, ReqId req_id);

signals:
    void applyTitleFinished(ReqId req_id, QString response, ErrorCodes err);
    void approveTitleFinished(ReqId req_id, QString response, ErrorCodes err);
    void searchTitlesFinished(ReqId req_id, QString response, ErrorCodes err);
    void getPostsUnderTitleFinished(ReqId req_id, QString response, ErrorCodes err);
    void getCategoriesUnderTitleFinished(ReqId req_id, QString response, ErrorCodes err);
};

#endif // TITLEHTTPMANAGER_H