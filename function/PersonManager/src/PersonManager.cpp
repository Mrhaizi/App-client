#include "PersonManager.h"
#include "global.h"
#include <exception>

PersonManager::PersonManager() {
}

void PersonManager::setCommunicator(std::shared_ptr<ClientCommunicator> communicator) {
    communicator = communicator;
}

void PersonManager::setJwdCode(const QString& jwt_code) {
    jwt_code_ = jwt_code;
}


void PersonManager::initInfo() {
    setPublicInfo();
    setPrivateInfo();
    setAllPersonalPublicInfo();
}

void PersonManager::initPersonalInfo(const QJsonObject& user_info, const QJsonArray& friend_list) {
    init_info_.user_info = user_info;
    init_info_.friends = friend_list;
}
void PersonManager::initOfflineMessage(const QJsonArray& offline_chat_msg, const QJsonArray& offline_group_msg, const QJsonArray& offline_notify) {
    init_info_.offline_messages = offline_chat_msg;
    init_info_.offline_group_messages = offline_group_msg;
    init_info_.group_notifications = offline_notify;
}
void PersonManager::initOfflineRequest(const QJsonArray& offline_frient_req, const QJsonArray& offline_group_req) {
    init_info_.friend_requests = offline_frient_req;
    init_info_.pending_requests = offline_group_req;
}

void PersonManager::setPublicInfo() {
    public_info_.age = init_info_.user_info.value("age").toInt();
    public_info_.email = init_info_.user_info.value("email").toString().toStdString();
    public_info_.id = init_info_.user_info.value("id").toInt();
    public_info_.username = init_info_.user_info.value("username").toString().toStdString();
}
void PersonManager::setPrivateInfo() {
    private_info_.friend_list.clear();
    private_info_.friend_apply.clear();
    for (const QJsonValue &value : init_info_.friends) {
        QJsonObject friend_obj = value.toObject();
        PersonalPublicInfo friend_info;
        std::cout << "id : " << friend_obj.value("id").toInt() << std::endl;
        std::cout << "username : " << friend_obj.value("username").toString().toStdString() << std::endl;
        friend_info.id = friend_obj.value("id").toInt();
        friend_info.username = friend_obj.value("username").toString().toStdString();
        private_info_.friend_list.push_back(friend_info);
    }
    for (const QJsonValue &value : init_info_.friend_requests) {
        QJsonObject request_obj = value.toObject();
        PersonalPublicInfo request_info;
        request_info.id = request_obj.value("user_id").toInt();
        request_info.username = request_obj.value("username").toString().toStdString();

        // 添加到好友申请列表
        private_info_.friend_apply.push_back(request_info);
    }
}


void PersonManager::deleteFriend(const std::string& name) {

}

void PersonManager::addFriend(const std::string& name) {

}

PersonalPrivateInfo PersonManager::getPrivateInfo() {
    return private_info_; 
}

PersonalPublicInfo PersonManager::getPublicInfo() {
    return public_info_;

}

void PersonManager::initCacheInfo(const QJsonArray& all_users) {
    init_info_.all_users = all_users;
}

void PersonManager::setAllPersonalPublicInfo() {
    for (const QJsonValue &value : init_info_.all_users) {
        QJsonObject user_obj = value.toObject();
        PersonalPublicInfo user_info;
        user_info.id = user_obj.value("user_id").toInt();
        user_info.username = user_obj.value("username").toString().toStdString();
        all_public_info_.push_back(user_info);
    }
}

std::vector<PersonalPublicInfo> PersonManager::searchPerson(const std::string& username) {
    std::vector<PersonalPublicInfo> re_info;
    for (auto it : all_public_info_) {
        if(it.username == username) {
            re_info.push_back(it);
        }
    }
    return re_info;
}