#include "Message.h"


ChatMessage::ChatMessage(const std::string &sender, const std::string &content, const std::string &recipient,
            ContentType messageType, 
            std::time_t timestamp, 
            const std::string &messageID)
    : sender_(sender), content_(content), recipient_(recipient), 
        messageType_(messageType), timestamp_(timestamp), messageID_(messageID),
        status_(MessageStatus::Sent) {}

std::string ChatMessage::getType() const {
    return "ChatMessage"; 
}

nlohmann::json ChatMessage::toJson() const {
    return nlohmann::json {
    {"sender", sender_},
    {"content", content_},
    {"recipient", recipient_},
    {"timestamp", timestamp_},
    {"messageID", messageID_},
    {"messageType", static_cast<int>(messageType_)},
    {"status", static_cast<int>(status_)}
};
}

std::string ChatMessage::generateMessageId() {
    return std::to_string(std::time(nullptr)) + std::to_string(rand());
}