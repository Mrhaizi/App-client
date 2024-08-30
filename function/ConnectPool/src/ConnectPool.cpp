#include "ConnectPool.h"

ConnectPool::ConnectPool(const int &poolsize, const std::string &ip, const int &port) 
    :server_ip_(ip),
    server_port_(port),
    pool_size_(poolsize) {
    for (int i = 0; i < pool_size_; ++i) {
        auto socket = std::make_shared<ClientCommunicator>();
        connections_.push(socket);
    }
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
     

