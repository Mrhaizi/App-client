#include "UserInfoManager.h"

UserInfoManager::UserInfoManager(const MySqlInfo& mysqlinfo) : mysqlinfo_(mysqlinfo) {
    driver_ = std::shared_ptr<sql::mysql::MySQL_Driver>(sql::mysql::get_mysql_driver_instance());
    connection_ = std::shared_ptr<sql::Connection>(driver_->connect(mysqlinfo_.host, mysqlinfo_.user, mysqlinfo_.password));
    connection_->setSchema(mysqlinfo_.database);
    stmt_ = std::shared_ptr<sql::Statement>(connection_->createStatement());
}

bool UserInfoManager::registerUserInfo(const std::string& username, const std::string& password) {
    try {
        std::shared_ptr<sql::PreparedStatement> pstmt(connection_->prepareStatement("INSERT INTO " + mysqlinfo_.table + " (username, password) VALUES (?, ?)"));
        pstmt->setString(1, username);
        pstmt->setString(2, password);
        pstmt->execute();
        return true;
    } catch (sql::SQLException& e) {
        return false;
    }
}

bool UserInfoManager::fetchUserInfo(const std::string& username, const std::string& password) {
    try {
        std::shared_ptr<sql::PreparedStatement> pstmt(connection_->prepareStatement("SELECT COUNT(*) FROM " + mysqlinfo_.table + " WHERE username = ? AND password = ?"));
        pstmt->setString(1, username);
        pstmt->setString(2, password);
        std::shared_ptr<sql::ResultSet> res(pstmt->executeQuery());
        res->next();
        return res->getInt(1) > 0;
    } catch (sql::SQLException& e) {
        return false;
    }
}

bool UserInfoManager::fetchUserName(const std::string& username) {
    try {
        std::shared_ptr<sql::PreparedStatement> pstmt(connection_->prepareStatement("SELECT COUNT(*) FROM " + mysqlinfo_.table + " WHERE username = ?"));
        pstmt->setString(1, username);
        std::shared_ptr<sql::ResultSet> res(pstmt->executeQuery());
        res->next();
        return res->getInt(1) > 0;
    } catch(sql::SQLException& e) {
        return false;
    }
}