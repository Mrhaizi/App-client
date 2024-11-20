#include <exception>

#include "ChatMessage.h"
#include "ChatMessage.h"

ChatMessage::ChatMessage(const std::string &content, const std::string &sender, const std::string &receiver, uint64_t uid_re, uint64_t uid_sen) 
        : MessageBase(ContentType::Text,
         MessageStatus::Created)
        {
            info_.content = content;
            info_.sender = sender;
            info_.receiver = receiver;
            info_.uid_receiver = uid_re;
            info_.uid_sender = uid_sen;
        }
std::string ChatMessage::getType() const {
    return "ChatMessage"; 
}

void ChatMessage::castFromString(const std::string& source) {
    try {
        nlohmann::json j = nlohmann::json::parse(source);
        info_ = j.get<Info>();
    } catch(std::exception e) {
    }
}
void ChatMessage::printMessage() {
}
nlohmann::json ChatMessage::toJson() const {
    return nlohmann::json { 
    {"sender", info_.sender},
    {"content", info_.content},
    {"receiver", info_.receiver},
    {"uid_sender", info_.uid_sender},
    {"uid_receiver", info_.uid_receiver},
    {"timestamp", timestamp_},
    {"messageid", messageid_},
    {"messagetype", static_cast<int>(contenttype_)},
    {"status", static_cast<int>(status_)}
};
}
AddFriendRequestMessage::AddFriendRequestMessage(const std::string& friend_username, uint64_t friend_id, const std::string& own_username, uint64_t own_id) : MessageBase(ContentType::Text, MessageStatus::Created) {
    info_.friend_username = friend_username;
    info_.own_username = own_username;
    info_.friend_id = friend_id;
    info_.own_id = own_id;
}

std::string AddFriendRequestMessage::getType() const {
    return "AddFriendRequestMessage";
}

nlohmann::json AddFriendRequestMessage::toJson() const {
    return nlohmann::json { 
    {"friend_username", info_.friend_username},
    {"own_username", info_.own_username},
    {"friend_id", info_.friend_id},
    {"own_id", info_.own_id},
    {"timestamp", timestamp_},
    {"messageidid", messageid_},
    {"messagetype", static_cast<int>(contenttype_)},
    {"status", static_cast<int>(status_)}
};
}

void AddFriendRequestMessage::castFromString(const std::string& source) {
    try {
        nlohmann::json j = nlohmann::json::parse(source);
        info_ = j.get<Info>();
    } catch(std::exception e) {
        // ZUES_LOG_STREAM_ERROR(ZUES_GET_LOG("system")) << "AddFriendRequestMessage cast error";
    }
}

AddFriendResponeMessage::AddFriendResponeMessage(bool success, PersonalPublicInfo public_info) : MessageBase(ContentType::Text, MessageStatus::Created) {
    info_.success = success;
    info_.public_info = public_info;
}

std::string AddFriendResponeMessage::getType() const {
    return "AddFriendResponeMessage";
}
nlohmann::json AddFriendResponeMessage::toJson() const {
    return nlohmann::json { 
    {"public_info", info_.public_info},
    {"bool", info_.success},
    {"timestamp", timestamp_},
    {"messageid", messageid_},
    {"messagetype", getType()},
    {"status", static_cast<int>(status_)}
};
}

void AddFriendResponeMessage::castFromString(const std::string& source) {
    try {
        nlohmann::json j = nlohmann::json::parse(source);
        info_ = j.get<Info>();
    } catch(std::exception e) {
        // ZUES_LOG_STREAM_ERROR(ZUES_GET_LOG("system")) << "AddFriendRequestMessage cast error";
    }
}

DeleteFriendMessage::DeleteFriendMessage(const std::string& username, uint64_t friend_id, uint64_t own_id) : MessageBase(ContentType::Text, MessageStatus::Created) {
    info_.username = username;
    info_.friend_id = friend_id;
    info_.own_id = own_id;
}

std::string DeleteFriendMessage::getType() const {
    return "DeleteFriendMessage";
}
nlohmann::json DeleteFriendMessage::toJson() const {
    return nlohmann::json { 
    {"username", info_.username},
    {"friend_id", info_.friend_id},
    {"own_id", info_.own_id},
    {"timestamp", timestamp_},
    {"messageid", messageid_},
    {"messagetype", getType()},
    {"status", static_cast<int>(status_)}
};
}

void DeleteFriendMessage::castFromString(const std::string& source) {
    try {
        nlohmann::json j = nlohmann::json::parse(source);
        info_ = j.get<Info>();
    } catch(std::exception e) {
        // ZUES_LOG_STREAM_ERROR(ZUES_GET_LOG("system")) << "DeleteFriendMessage cast error";
    }
}

FriendConfirmMessage::FriendConfirmMessage(bool success, uint64_t friend_id, uint64_t own_id) : MessageBase(ContentType::Text, MessageStatus::Created) {
    info_.success = success;
    info_.friend_id = friend_id;
    info_.own_id = own_id;
}

std::string FriendConfirmMessage::getType() const {
    return "ConfirmMessage"; 
}

void FriendConfirmMessage::castFromString(const std::string& source) {
    try {
        nlohmann::json j = nlohmann::json::parse(source);
        info_ = j.get<Info>();
    } catch(std::exception e) {
        // ZUES_LOG_STREAM_ERROR(ZUES_GET_LOG("system")) << " ConfirmMessage cast error";
    }
}

nlohmann::json FriendConfirmMessage::toJson() const {
    return nlohmann::json { 
    {"success", info_.success},
    {"friend_id", info_.friend_id},
    {"own_id", info_.own_id},
    {"timestamp", timestamp_},
    {"messageid", messageid_},
    {"messagetype", getType()},
    {"status", static_cast<int>(status_)}
};
}




