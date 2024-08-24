#ifndef PERSONALINFOMANAGER_H
#define PERSONALINFOMANAGER_H

#include <iostream>
#include <memory>
#include <unordered_map>

#include "CommunicatorClient.h"

struct PersonalPublicInfo {
    std::string name;
    int id;
    // 以下信息可以选择隐藏
    int age;
    std::string address;
    std::string phoneNumber;
    std::string email;
};

struct PersonalPrivateInfo {
    std::string password;
    std::unordered_map<std::string, PersonalPublicInfo> friend_list;

};


class PersonManager {
public:
    PersonManager(std::shared_ptr<PersonalPrivateInfo> private_info = nullptr, std::shared_ptr<PersonalPublicInfo> public_info = nullptr);
    void addFriend(const std::string &name);
    void deleteFriend(const std::string &name);
private:
    std::shared_ptr<PersonalPrivateInfo> private_info_;
    std::shared_ptr<PersonalPublicInfo> public_info_;
};

#endif // PERSONALINFOMANAGER_