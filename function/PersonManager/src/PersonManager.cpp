#include "PersonManager.h"
#include "global.h"
#include <exception>

PersonManager::PersonManager() {
}

bool PersonManager::initPersonalInfo(std::shared_ptr<ClientCommunicator> communicator, const PersonalPublicInfo &public_info, const PersonalPrivateInfo &private_info) {
    try {

    } catch (std::exception) {
    
    }
}

void PersonManager::setCommunicator(std::shared_ptr<ClientCommunicator> communicator) {
    communicator = communicator;
}

void PersonManager::setPrivateInfo(const PersonalPrivateInfo& private_info)  {
    private_info_ = private_info;
}

void PersonManager::setPublicInfo(const PersonalPublicInfo& public_info) {
    public_info_ = public_info;
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

void PersonManager::getAllPersonalPublicInfo(const std::vector<PersonalPublicInfo>& info) {
    all_public_info_ = info;
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