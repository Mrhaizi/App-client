#include <iostream>
#include <time.h>

#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/exception.h>

#include "LogInWindow.h"
#include "HomeWindow.h"
#include "ConnectPool.h"
#include "ServerConfigManager.h"


int main(int argc, char* argv[]) {   
    QApplication app(argc, argv);
    // MySqlInfo mysqlInfo;
    // #ifdef _WIN32
    //     mysqlInfo = {"tcp://127.0.0.1:3306", "root", "123456", "userdata", "users"};
    // #elif defined(__unix__) || defined(__linux__)
    //     mysqlInfo = {"tcp://127.0.0.1:3306", "root", "myq", "AppInfo", "users"};
    // #else
    //     std::cerr << "Unsupported platform!" << std::endl;
    //     return 1;
    // #endif
    
    ServerConfigManager::getInstance().setIP("111.73.106.31"); 
    ServerConfigManager::getInstance().setPort(89);
    auto connect = ConnectPool::getInstance(
        ServerConfigManager::getInstance().getIP(),
        ServerConfigManager::getInstance().getPort()
    ).getConnection(500);
    // std::cout << mysqlInfo.database << std::endl;
    // PersonalPrivateInfo demo_private = {};
    // PersonalPublicInfo demo_public = {"1", 12, "email", 18};
    // std::shared_ptr<PersonManager> infomanager = std::make_shared<PersonManager>(connect, demo_public, demo_private);
    LoginWindow loginWindow(nullptr, connect);
    loginWindow.show();
    return app.exec();
}
