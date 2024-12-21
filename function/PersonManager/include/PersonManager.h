#ifndef PERSONALINFOMANAGER_H
#define PERSONALINFOMANAGER_H

#include <iostream>
#include <memory>
#include <unordered_map>

#include "CommunicatorClient.h"
#include "Singleton.hpp"
#include "global.h"

struct InitInfo {
    QJsonArray all_users;
    QJsonArray friends;
    QJsonArray friend_requests;
    QJsonArray offline_messages;
    QJsonArray offline_group_messages;
    QJsonArray group_notifications;
    QJsonArray pending_requests;
    QJsonObject user_info;
    InitInfo() {
        all_users = QJsonArray();
        friends = QJsonArray();
        friend_requests = QJsonArray();
        offline_messages = QJsonArray();
        offline_group_messages  = QJsonArray();
        group_notifications = QJsonArray();
        pending_requests = QJsonArray();
        user_info = QJsonObject();
        all_users = QJsonArray();

    }
};

class PersonManager {
public:
    typedef Singleton<PersonManager> singleton;
    PersonManager();
    void setCommunicator(std::shared_ptr<ClientCommunicator> communicator);
    PersonalPublicInfo getPublicInfo();
    PersonalPrivateInfo getPrivateInfo();
    void initCacheInfo(const QJsonArray& all_users);
    void initPersonalInfo(const QJsonObject& user_info, const QJsonArray& friend_list);
    void initOfflineMessage(const QJsonArray& offline_chat_msg, const QJsonArray& offline_group_msg, const QJsonArray& offline_notify);
    void initOfflineRequest(const QJsonArray& offline_frient_req, const QJsonArray& offline_group_req);
    void addFriend(const std::string &name);
    void deleteFriend(const std::string &name);
    void setAllPersonalPublicInfo();
    void setAllUsers();
    void setJwdCode(const QString& code);
    QString getJwdCode() {return jwt_code_;}
    std::vector<PersonalPublicInfo> searchPerson(const std::string& username);
    // void getInitInfo(std::vector<QJson>);

    void initInfo();
private:
    void setPublicInfo();
    void setPrivateInfo();
    std::shared_ptr<ClientCommunicator> communicator_ = nullptr;
    PersonalPrivateInfo private_info_;
    PersonalPublicInfo public_info_;
    InitInfo init_info_;
    std::vector<PersonalPublicInfo> all_public_info_;
    QString jwt_code_;
};
#endif // PERSONALINFOMANAGER_
