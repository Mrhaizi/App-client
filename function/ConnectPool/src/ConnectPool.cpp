#include "ConnectPool.h"

ConnectPool::ConnectPool(const int &poolsize, const std::string &ip, const int &port) 
    :server_ip_(ip),
    server_port_(port),
    pool_size_(poolsize) {
    for (int i = 0; i < pool_size_; ++i) {
        auto socket = std::make_shared<ClientCommunicator>(nullptr, server_port_, server_ip_);
        connections_.push(socket);
    }
}
ConnectPool& ConnectPool::getInstance(const std::string &ip, const int &port, const int &poolsize) {
    static ConnectPool instance(poolsize,ip, port);
    return instance;
}

std::shared_ptr<ClientCommunicator> ConnectPool::getConnection(const int &timeout)  {
    std::unique_lock<std::mutex> lock(mutex_);
    if (cv_.wait_for(lock, std::chrono::milliseconds(timeout), [this] { return!connections_.empty();})) {
        auto connection = connections_.front();
        connections_.pop();
        return connection;
    } else {
        return nullptr;
    }
}
void ConnectPool::releaseConnection(std::shared_ptr<ClientCommunicator> connection) {
    std::unique_lock<std::mutex> lock(mutex_);
    connections_.push(connection);
    cv_.notify_one();
}
     

