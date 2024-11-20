// #include "LoginMessage.h"
// #include "global.h"

// LoginRequestMessage::LoginRequestMessage(const std::string &username, const std::string &password) 
//     : username_(username),
//     password_(password),
//     MessageBase(ContentType::Text, MessageStatus::Created) {


// }

// std::string LoginRequestMessage::getType() const {
//     return "LoginRequestMessage";
// }

// nlohmann::json LoginRequestMessage::toJson() const {
//     return nlohmann::json {
//     {"messagetype", getType()},
//     {"username", username_},
//     {"password", password_},
//     {"messageid", messageid_},
//     {"timestamp", timestamp_},
//     {"messagetype", static_cast<int>(contenttype_)},
//     {"status", static_cast<int>(status_)},
//     };
// }

// LoginResponseMessage::LoginResponseMessage(const PersonalPublicInfo &public_info, const PersonalPrivateInfo &private_info, bool success) 
//     : MessageBase(ContentType::Text, MessageStatus::Created),
//     public_info_(public_info),
//     private_info_(private_info), 
//     success_(success) {}

// std::string LoginResponseMessage::getType() const {
//     return "LoginResponseMessage";
// }

// nlohmann::json LoginResponseMessage::toJson() const {
//     return nlohmann::json {
//     {"messgaetype", getType()},
//     {"username", public_info_.username},
//     {"userid", public_info_.id},
//     {"userage", public_info_.age},
//     {"useremail", public_info_.email},
//     {"userpassword", private_info_.password},
//     {"friends", private_info_.friend_list},
//     {"success", success_},
//     };
// }
#include "LoginMessage.h"

LoginRequestMessage::LoginRequestMessage(const std::string &username, const std::string &password) 
    : MessageBase(ContentType::Text, MessageStatus::Created) {
        info_.username = username;
        info_.password = password;
}


std::string LoginRequestMessage::getType() const {
    return "LoginRequestMessage";
}

void LoginRequestMessage::castFromString(const std::string& source)  {
    try {
        nlohmann::json j = nlohmann::json::parse(source);
        info_ = j.get<Info>();
    } catch(std::exception e) {
    }
}

nlohmann::json LoginRequestMessage::toJson() const {
    return nlohmann::json {
    {"messagetype", getType()},
    {"username",  info_.username},
    {"password", info_.password},
    {"messageid", messageid_},
    {"timestamp", timestamp_},
    {"conenttype", static_cast<int>(contenttype_)},
    {"status", static_cast<int>(status_)},
    };
}


LoginResponseMessage::LoginResponseMessage(PersonalPublicInfo public_info, PersonalPrivateInfo private_info, bool success) 
    : MessageBase(ContentType::Text, MessageStatus::Created) {
        info_.public_info = public_info;
        info_.private_info = private_info;
        info_.success = success;
    }

std::string LoginResponseMessage::getType() const {
    return "LoginResponseMessage";
}

nlohmann::json LoginResponseMessage::toJson() const {
    return nlohmann::json {
    {"messagetype", getType()},
    {"public_info", info_.public_info},
    {"private_info", info_.private_info},
    {"success", info_.success},
    };
}

void LoginResponseMessage::castFromString(const std::string& source) {
    try {
        nlohmann::json j = nlohmann::json::parse(source);
        info_ = j.get<Info>();
    } catch(std::exception e) {
    }

}

