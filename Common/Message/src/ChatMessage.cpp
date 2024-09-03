#include "ChatMessage.h"


ChatMessage::ChatMessage(const std::string &content, const std::string &sender, const std::string &receiver) 
        : MessageBase(ContentType::Text, MessageStatus::Created) {}

std::string ChatMessage::getType() const {
    return "ChatMessage"; 
}

nlohmann::json ChatMessage::toJson() const {
    return nlohmann::json {
    {"sender", sender_},
    {"content", content_},
    {"recipient", receiver_},
    {"timestamp", timestamp_},
    {"messageID", messageid_},
    {"messageType", static_cast<int>(contenttype_)},
    {"status", static_cast<int>(status_)}
};
}


