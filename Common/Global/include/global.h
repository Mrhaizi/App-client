#ifndef GLOBAL_H
#define GLOBAL_H

#include <functional>
#include <QObject>


extern std::function<void(QWidget*)> repolish;

enum MessageId{
    ID_GET_VARIFY_CODE_REQUEST = 1001, //获取验证码请求
    ID_GET_VARIFY_CODE_RESPONE = 1002, //获取验证码请求
    ID_REGIST_USER_REQUEST = 1003, //注册用户请求
    ID_REGIST_USER_RESPONE = 1004, //注册用户响应
    ID_LOGIN_USER_REQUEST = 1005, //用户登录请求
    ID_LOGIN_USER_RESPONE = 1006, //用户登录回应
};

enum ListItemType{
    CHAT_USER_ITEM, //聊天用户
    SEARCH_USER_ITEM, //搜索到的用户
    ADD_USER_TIP_ITEM, //提示添加用户
    INVALID_ITEM,  //不可点击条目
    GROUP_TIP_ITEM, //分组提示条目
    LINE_ITEM,  //分割线
    APPLY_FRIEND_ITEM, //好友申请
};


#endif // GLOBAL_H