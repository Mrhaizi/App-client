#ifndef SERVERCONFIGMANAGER_H
#define SERVERCONFIGMANAGER_H


#include <string>
class ServerConfig {
public:
    ServerConfig(const std::string& ipaddress, int portnumber)
        : ip_(ipaddress), port_(portnumber) {}

    std::string getIP() const { return ip_; }
    int getPort() const { return port_; }

    void setIP(const std::string& ipaddress) { ip_ = ipaddress; }
    void setPort(int portnumber) { port_ = portnumber; }

private:
    std::string ip_;
    int port_;
};

class ServerConfigManager {
public:
    static ServerConfigManager& getInstance() {
        static ServerConfigManager instance("myqzyx.cn", 8989); // 默认IP和端口
        return instance;
    }

    std::string getIP() const { return config_.getIP(); }
    int getPort() const { return config_.getPort(); }

    void setIP(const std::string& ipaddress) { config_.setIP(ipaddress); }
    void setPort(int portnumber) { config_.setPort(portnumber); }

private:
    ServerConfig config_;

    ServerConfigManager(const std::string& ip, int port)
        : config_(ip, port) {}

    ServerConfigManager(const ServerConfigManager&) = delete;
    void operator=(const ServerConfigManager&) = delete;
};
#endif // SERVERCONFIGMANAGER_H
