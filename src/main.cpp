#include <iostream>
#include <string>
#include <memory> 
#include <time.h>

#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/exception.h>
#include <QDir>
#include <QSettings>
#include <QMainWindow>
#include <QWebEngineView>

#include "LogInWindow.h"
#include "HomeWindow.h"
#include "ConnectPool.h"
#include "ServerConfigManager.h"
#include "CommunicatorClient.h"

int main(int argc, char* argv[]) {   
    QApplication app(argc, argv);
    // ServerConfigManager::getInstance().setIP("111.173.106.31"); 
    ServerConfigManager::getInstance().setIP("127.0.0.1"); 
    // ServerConfigManager::getInstance().setIP("127.0.0.1"); 
    ServerConfigManager::getInstance().setPort(12345);
    std::shared_ptr<ClientCommunicator> connect = ConnectPool::getInstance(
        ServerConfigManager::getInstance().getIP(),
        ServerConfigManager::getInstance().getPort()

    ).getConnection(500);
    QString app_path = QCoreApplication::applicationDirPath();
    if (app_path.endsWith("/build")) {
        app_path.chop(6);  // 移除末尾的 "/build"
    }
    std::cout << app_path.toStdString() << std::endl;
    QString fileName = "Config/config.ini";
    QString config_path = QDir::toNativeSeparators(app_path +
                             QDir::separator() + fileName);
    QSettings settings(config_path, QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    gate_url_prefix = "http://"+gate_host+":"+gate_port;
    // std::cout << mysqlInfo.database << std::endl;
    // PersonalPrivateInfo demo_private = {};
    // PersonalPublicInfo demo_public = {"1", 12, "email", 18};
    // std::shared_ptr<PersonManager> infomanager = std::make_shared<PersonManager>(connect, demo_public, demo_private);
    LoginWindow loginWindow(nullptr, connect);
    loginWindow.show();

    return app.exec();
}
