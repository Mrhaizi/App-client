#ifndef POSTHTTPMANAGER_H
#define POSTHTTPMANAGER_H

#include "BaseHttpManager.h"
#include "Singleton2.hpp"

class PostManager : public BaseHttpManager, public Singleton2<PostManager>
{
    Q_OBJECT
    friend class Singleton2<PostManager>;

private:
    explicit PostManager(QObject* parent = nullptr);
    ~PostManager();

public:
    void publishPost(const QString& content, int title_id, ReqId req_id);
    void deletePost(int post_id, ReqId req_id);
    void reviewPost(int post_id, bool approved, const QString& reason, int categoryId, ReqId req_id);
    void removeTitleFromPost(int post_id, ReqId req_id);
    void getPosts(const QString& filter, ReqId req_id);
    void assignPostToCategory(int post_id, int categoryId, ReqId req_id);
    void getPostsUnderCategory(int title_id, int categoryId, ReqId req_id);

signals:
    void publishPostFinished(ReqId req_id, QString response, ErrorCodes err);
    void deletePostFinished(ReqId req_id, QString response, ErrorCodes err);
    void reviewPostFinished(ReqId req_id, QString response, ErrorCodes err);
    void removeTitleFromPostFinished(ReqId req_id, QString response, ErrorCodes err);
    void getPostsFinished(ReqId req_id, QString response, ErrorCodes err);
    void assignPostToCategoryFinished(ReqId req_id, QString response, ErrorCodes err);
    void getPostsUnderCategoryFinished(ReqId req_id, QString response, ErrorCodes err);
};

#endif // POSTHTTPMANAGER_H