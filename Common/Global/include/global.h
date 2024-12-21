#ifndef GLOBAL_H
#define GLOBAL_H

#include <functional>
#include <QObject>
#include <QtWidgets/QStyle>
#include <QJsonObject>
#include <QJsonArray>
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
enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1, //Json解析失败
    NETWORK_ERROR,
};

enum ReqId{
    ID_GET_VARIFY_CODE = 1001, //获取验证码
    ID_REG_USER = 1002, //注册用户
    ID_RESET_PWD = 1003, //重置密码
    ID_LOGIN_USER = 1004, //用户登录
    ID_CHAT_LOGIN = 1005, //登陆聊天服务器
    ID_CHAT_LOGIN_RSP= 1006, //登陆聊天服务器回包
    ID_SEARCH_USER_REQ = 1007, //用户搜索请求
    ID_SEARCH_USER_RSP = 1008, //搜索用户回包
    ID_ADD_FRIEND_REQ = 1009,  //添加好友申请
    ID_ADD_FRIEND_RSP = 1010, //申请添加好友回复
    ID_NOTIFY_ADD_FRIEND_REQ = 1011,  //通知用户添加好友申请
    ID_AUTH_FRIEND_REQ = 1013,  //认证好友请求
    ID_AUTH_FRIEND_RSP = 1014,  //认证好友回复
    ID_NOTIFY_AUTH_FRIEND_REQ = 1015, //通知用户认证好友申请
    ID_TEXT_CHAT_MSG_REQ  = 1017,  //文本聊天信息请求
    ID_TEXT_CHAT_MSG_RSP  = 1018,  //文本聊天信息回复
    ID_NOTIFY_TEXT_CHAT_MSG_REQ = 1019, //通知用户文本聊天信息
};
enum Modules{
    REGISTERMOD = 0,
    RESETMOD = 1,
    LOGINMOD = 2,
    APPLY_TITLE_MOD,
    APPROVE_TITLE_MOD,
    PUBLISH_POST_MOD,
    DELETE_POST_MOD,
    REVIEW_POST_MOD,
    REMOVE_TITLE_FROM_POST_MOD,
    FOLLOW_USER_MOD,
    GET_FOLLOWINGS_MOD,
    GET_POSTS_MOD,
    SEARCH_TITLES_MOD,
    GET_POSTS_UNDER_TITLE_MOD,
    CREATE_CATEGORY_MOD,
    DELETE_CATEGORY_MOD,
    ASSIGN_POST_TO_CATEGORY_MOD,
    GET_CATEGORIES_UNDER_TITLE_MOD,
    GET_POSTS_UNDER_CATEGORY_MOD,
};
enum TipErr{
    TIP_SUCCESS = 0,
    TIP_EMAIL_ERR = 1,
    TIP_PWD_ERR = 2,
    TIP_CONFIRM_ERR = 3,
    TIP_PWD_CONFIRM = 4,
    TIP_VARIFY_ERR = 5,
    TIP_USER_ERR = 6
};

enum ClickLbState{
    Normal = 0,
    Selected = 1
};


enum class ContentType { Text};

struct PersonalPublicInfo {
    std::string username;
    uint64_t id;
    std::string email;
    int age;
    PersonalPublicInfo(const std::string& name, uint64_t id_value , int age_value, const std::string& email_value = " ") : 
        username(name),
        id(id_value),
        age(age_value),
        email(email_value){}
    PersonalPublicInfo() :
        username(" "),
        id(0),
        age(0),
        email(""){
    }
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
    std::vector<PersonalPublicInfo> friend_list;
    std::vector<PersonalPublicInfo> friend_apply;
    friend void to_json(nlohmann::json& j, const PersonalPrivateInfo& p) {
        j = nlohmann::json{{"password", p.password},
                            {"friend_list", p.friend_list},
                            {"friend_apply", p.friend_apply},
                            };
    }
    friend void from_json(const nlohmann::json& j, PersonalPrivateInfo& p) {
        j.at("password").get_to(p.password);
        j.at("friend_apply").get_to(p.friend_apply);
        j.at("friend_list").get_to(p.friend_list);
    }

};
extern QString gate_url_prefix;
#endif // GLOBAL_H
