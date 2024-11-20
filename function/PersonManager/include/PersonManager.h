#ifndef PERSONALINFOMANAGER_H
#define PERSONALINFOMANAGER_H

#include <iostream>
#include <memory>
#include <unordered_map>

#include "CommunicatorClient.h"
#include "Singleton.hpp"
#include "global.h"


class PersonManager {
public:
    typedef Singleton<PersonManager> singleton;
    PersonManager();
    void setCommunicator(std::shared_ptr<ClientCommunicator> communicator);
    void setPublicInfo(const PersonalPublicInfo& public_info);
    void setPrivateInfo(const PersonalPrivateInfo& private_info);
    PersonalPublicInfo getPublicInfo();
    PersonalPrivateInfo getPrivateInfo();
    bool initPersonalInfo(std::shared_ptr<ClientCommunicator> communicator, const PersonalPublicInfo& public_info, const PersonalPrivateInfo& private_info);
    void addFriend(const std::string &name);
    void deleteFriend(const std::string &name);
    void getAllPersonalPublicInfo(const std::vector<PersonalPublicInfo>& info);
    std::vector<PersonalPublicInfo> searchPerson(const std::string& username);

private:
    std::shared_ptr<ClientCommunicator> communicator_ = nullptr;
    PersonalPrivateInfo private_info_;
    PersonalPublicInfo public_info_;
    std::vector<PersonalPublicInfo> all_public_info_;
};
#endif // PERSONALINFOMANAGER_
