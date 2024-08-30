#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>

#include "MessageBase.h"
#include "glob.h"

class ChatMessage : public MessageBase {
public:
ChatMessage(const std::string &sender, const std::string &content, const std::string &recipient,
                ContentType messageType = ContentType::Text, 
                std::time_t timestamp= std::time(nullptr), 
                const std::string &messageID = generateMessageId());
    std::string getType() const override;
    nlohmann::json toJson() const override;
    
private:
    static std::string generateMessageId();
    std::string sender_;
    std::string content_;
    std::string recipient_;
    std::time_t timestamp_;
    std::string messageID_;
    ContentType messageType_;
    MessageStatus status_;
};

class LoginRequestMessage : public MessageBase  {
public:
    LoginRequestMessage(const std::string &username, const std::string &password);
    std::string getType() const override;
    nlohmann::json toJson() const override;
private:
    std::string username_;
    std::string password_;
    std::string messageID_;
};

class RegistRequestMessage : public MessageBase {
public:

};

class LoginResponseMessage : public MessageBase {
public:

};

class RegistResponseMessage : public MessageBase {
public:

};

#endif // MESSAGE_H