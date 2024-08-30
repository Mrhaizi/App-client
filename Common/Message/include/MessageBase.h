#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

enum class ContentType { Text};
enum class MessageStatus {Sent, Delivered, Read};

class MessageBase {
    virtual std::string getType() const = 0;
    virtual nlohmann::json toJson() const = 0;
};

#endif // MESSAGEBASE_H
