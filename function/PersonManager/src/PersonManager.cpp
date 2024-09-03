#include "PersonManager.h"
#include "global.h"
#include <exception>

PersonManager::PersonManager(std::shared_ptr<ClientCommunicator> communicator, const PersonalPublicInfo &public_info, const PersonalPrivateInfo &private_info) 
    : communicator_(communicator), 
    public_info_(public_info),
    private_info_(private_info) {
}

bool PersonManager::initPersonalInfo() {
    try {

    } catch (std::exception) {
    
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
