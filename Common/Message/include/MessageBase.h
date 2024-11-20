#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include <ctime>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include "global.h"


enum MessageType {
    Chat = 0x01,
    LogRequest = 0x02,
    LogResponse = 0x03,
    RegRequest = 0x04,
    RegResponse = 0x05,
    SendVerifyCode = 0x06,
    RetVerifyCode = 0x07,
    AddFriendRequest = 0x08,
    AddFriendResponeMessage = 0x09,
    DeleteFriend = 0xa,
    FriendConfirm = 0xb, 
    InformFriendApply = 0xc,
    CheckPersonalInfo = 0xd,
    CacheInfo = 0x0e,
};

struct TcpPacket {
    uint32_t length;   // 包长度（4 bytes）
    uint16_t type;     // 包类型（2 bytes）
    uint8_t version;   // 版本号（1 byte）
    uint8_t reserved;  // 保留字段（1 byte）
    char body[];       // 包体，动态长度
};
class MessageBase {
public:
    MessageBase(ContentType contenttype, MessageStatus status)
        : messageid_(generateMessageId()), contenttype_(contenttype), status_(status), timestamp_(std::time(nullptr)) {}
    virtual ~MessageBase() = default;
    virtual std::string getType() const = 0;
    virtual nlohmann::json toJson() const = 0;
    static std::string generateMessageId();
    virtual void castFromString(const std::string& source) = 0;
protected:
    std::string messageid_;
    ContentType contenttype_;
    MessageStatus status_;
    std::time_t timestamp_;
};
#endif // MESSAGEBASE_H
