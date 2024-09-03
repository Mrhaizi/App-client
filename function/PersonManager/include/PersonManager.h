#ifndef PERSONALINFOMANAGER_H
#define PERSONALINFOMANAGER_H

#include <iostream>
#include <memory>
#include <unordered_map>

#include "CommunicatorClient.h"
#include "global.h"


class PersonManager {
public:
    PersonManager(std::shared_ptr<ClientCommunicator> communicator, const PersonalPublicInfo &public_info, const PersonalPrivateInfo &private_info);
    PersonalPublicInfo getPublicInfo();
    PersonalPrivateInfo getPrivateInfo();
    bool initPersonalInfo();
    void addFriend(const std::string &name);
    void deleteFriend(const std::string &name);
private:
    std::shared_ptr<ClientCommunicator> communicator_ = nullptr;
    PersonalPrivateInfo private_info_;
    PersonalPublicInfo public_info_;
};
#endif // PERSONALINFOMANAGER_
