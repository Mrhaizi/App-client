#include <iostream>

#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/exception.h>

#include <LogInUi.h>

int main(int argc, char* argv[]) {   
        QApplication app(argc, argv);
        MySqlInfo mysqlInfo;
        if (WIN32) {
            mysqlInfo = {"tcp://127.0.0.1:3306", "root", "123456", "userdata", "user"};

        } else {
            mysqlInfo = {"tcp://127.0.0.1:3306", "root", "myq", "userdata", "userinfo"};    
        }
        std::cout << mysqlInfo.database << std::endl;
        std::shared_ptr<UserInfoManager> infomanager = std::make_shared<UserInfoManager>(mysqlInfo);
        LoginWindow loginWindow(nullptr, infomanager);
        loginWindow.show();
        return app.exec();
}