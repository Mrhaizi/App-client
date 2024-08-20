#include "PersonalInfoManager.h"

PersonManager::PersonManager(std::shared_ptr<PersonalPrivateInfo> private_info, std::shared_ptr<PersonalPublicInfo> public_info) :
    private_info_(private_info),
    public_info_(public_info) {
}

void PersonManager::deleteFriend(const std::string& name) {

}

void PersonManager::addFriend(const std::string& name) {

}