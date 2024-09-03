#ifndef LOGINMESSAGE_H
#define LOGINMESSAGE_H

#include <MessageBase.h>

class LoginRequestMessage : public MessageBase  {
public:
    LoginRequestMessage(const std::string &username, const std::string &password);
    std::string getType() const override;
    nlohmann::json toJson() const override;
private:
    std::string username_;
    std::string password_;
};

class LoginResponseMessage : public MessageBase {
public:
    LoginResponseMessage(const PersonalPublicInfo &public_info, const PersonalPrivateInfo &private_info, bool success);
    std::string getType() const override;
    nlohmann::json toJson() const override;
    PersonalPublicInfo getPublicInfo();
    PersonalPrivateInfo getPrivateInfo();
private:
    bool success_;
    PersonalPublicInfo public_info_;
    PersonalPrivateInfo private_info_; 
};
#endif // LOGINMESSAGE_H
