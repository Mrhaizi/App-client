#ifndef USERINFOMANAGER_H
#define USERINFOMANAGER_H

#include <iostream>
#include <vector>
#include <string>


#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/prepared_statement.h>

#include "PersonalInfoManager.h"
#include "CommunicatorClient.h"



struct MySqlInfo {
    std::string host;
    std::string user;
    std::string password;
    std::string database;
    std::string table;
};

class UserInfoManager {
public:
    UserInfoManager(const MySqlInfo& mysqlinfo);

    bool registerUserInfo(const std::string& username, const std::string& password);

    bool fetchUserInfo(const std::string& username, const std::string& password);
    
    bool fetchUserName(const std::string& username);

    bool getSingleUserAllInfo(const std::string& username);

private:
    MySqlInfo mysqlinfo_;
    std::shared_ptr<sql::mysql::MySQL_Driver> driver_ = nullptr;
    std::shared_ptr<sql::Connection> connection_ = nullptr;
    std::shared_ptr<sql::Statement> stmt_ = nullptr;
};

#endif // USERINFOMANAGER_H