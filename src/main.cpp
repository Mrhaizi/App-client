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

int main(int argc, char* argv[]) {   
        QApplication app(argc, argv);
        MySqlInfo mysqlInfo;
        #ifdef _WIN32
            mysqlInfo = {"tcp://127.0.0.1:3306", "root", "123456", "userdata", "users"};
        #elif defined(__unix__) || defined(__linux__)
            mysqlInfo = {"tcp://127.0.0.1:3306", "root", "myq", "userdata", "users"};
        #else
            std::cerr << "Unsupported platform!" << std::endl;
            return 1;
        #endif
        ClientCommunicator client;
        client.connectToHost("127.0.0.1", 8989);
        std::cout << mysqlInfo.database << std::endl;
        std::shared_ptr<UserInfoManager> infomanager = std::make_shared<UserInfoManager>(mysqlInfo);
        LoginWindow loginWindow(nullptr, infomanager);
        // HomeWindow homeWindow(nullptr);
        // homeWindow.show();
        loginWindow.show();
        return app.exec();
}