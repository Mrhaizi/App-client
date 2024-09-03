#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>

#include "MessageBase.h"
#include "glob.h"
#include "nlohmann/json.hpp"

class ChatMessage : public MessageBase {
public:
ChatMessage(const std::string &content, const std::string &sender, const std::string &receiver);
    std::string getType() const override;
    nlohmann::json toJson() const override;
private:
    std::string content_;
    std::string sender_;
    std::string receiver_;
};


#endif // MESSAGE_H
