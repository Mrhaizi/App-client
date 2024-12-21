#ifndef AUTHHTTPMANAGER_H
#define AUTHHTTPMANAGER_H

#include "BaseHttpManager.h"
#include "Singleton2.hpp"

class AuthManager : public BaseHttpManager, public Singleton2<AuthManager>
{
    Q_OBJECT
    friend class Singleton2<AuthManager>;
private:
    explicit AuthManager(QObject* parent = nullptr);
public:
    void registerUser(const QString& username, const QString& password, ReqId req_id);
    void loginUser(const QString& username, const QString& password, ReqId req_id);
    void resetPassword(const QString& username, const QString& newPassword, ReqId req_id);
    ~AuthManager() = default;
signals:
    void registerFinished(ReqId req_id, QString response, ErrorCodes err);
    void loginFinished(ReqId req_id, QString response, ErrorCodes err);
    void resetPasswordFinished(ReqId req_id, QString response, ErrorCodes err);
};
#endif // AUTHHTTPMANAGER_H