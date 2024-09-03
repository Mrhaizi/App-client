#ifndef GLOBAL_H
#define GLOBAL_H

#include <functional>
#include <QObject>

#include <nlohmann/json.hpp>

extern std::function<void(QWidget*)> repolish;

enum class ListItemType {
    ChatUserItem,      // 聊天用户
    SearchUserItem,    // 搜索到的用户
    AddUserTipItem,    // 提示添加用户
    InvalidItem,       // 不可点击条目
    GroupTipItem,      // 分组提示条目
    LineItem,          // 分割线
    ApplyFriendItem    // 好友申请
};

enum class MessageStatus {
    Created, // 消息已经创建
    PendingSend, // 准备发送
    Sent, // 已经发送
    Received, // 已经收到
    PendingProcess, // 准备处理
    Processing, // 正在处理
    Processed, // 处理完成
    SendFailed, // 发送失败
    ReceiveFailed, // 接收失败
    ProcessingError, // 处理失败
    Acknowledged, // 确认
    AckTimeout // 确认超时
};

enum class ContentType { Text};

struct PersonalPublicInfo {
    std::string username;
    int id;
    std::string email;
    int age;
    friend void to_json(nlohmann::json& j, const PersonalPublicInfo& p) {
        j = nlohmann::json{{"username", p.username}, {"age", p.age}, {"email", p.email}, {"id", p.id}};
    }
    friend void from_json(const nlohmann::json& j, PersonalPublicInfo& p) {
        j.at("username").get_to(p.username);
        j.at("age").get_to(p.age);
        j.at("email").get_to(p.email);
        j.at("id").get_to(p.id);
    }
};
struct PersonalPrivateInfo {
    std::string password;
    std::unordered_map<std::string, PersonalPublicInfo> friend_list;
};


#endif // GLOBAL_H
