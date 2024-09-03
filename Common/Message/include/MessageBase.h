#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include <ctime>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include "global.h"



class MessageBase {
public:
    MessageBase(ContentType contenttype, MessageStatus status)
        : messageid_(generateMessageId()), contenttype_(contenttype), status_(status), timestamp_(std::time(nullptr)) {}
    virtual ~MessageBase() = default;

    virtual std::string getType() const = 0;
    virtual nlohmann::json toJson() const = 0;

    static std::string generateMessageId();

protected:
    std::string messageid_;
    ContentType contenttype_;
    MessageStatus status_;
    std::time_t timestamp_;

};

#endif // MESSAGEBASE_H
