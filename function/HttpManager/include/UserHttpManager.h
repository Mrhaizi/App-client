#ifndef USERHTTPMANAGER_H
#define USERHTTPMANAGER_H


#include "BaseHttpManager.h"
#include "Singleton2.hpp"

class UserManager : public BaseHttpManager, public Singleton2<UserManager>
{
    Q_OBJECT
    friend class Singleton2<UserManager>;

private:
    explicit UserManager(QObject* parent = nullptr);
    ~UserManager();

public:
    void followUser(int following_id, ReqId req_id);
    void getFollowings(int user_id, ReqId req_id);

signals:
    void followUserFinished(ReqId req_id, QString response, ErrorCodes err);
    void getFollowingsFinished(ReqId req_id, QString response, ErrorCodes err);
};

#endif // USERHTTPMANAGER_H