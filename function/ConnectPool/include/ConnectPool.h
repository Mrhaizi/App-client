#ifndef CONNECTPOOL_H
#define CONNECTPOOL_H

#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <memory>
#include <thread>

#include "CommunicatorClient.h"

class ConnectPool
{
public:
    ConnectPool(const int &poolsize, const std::string &ip, const int &port);
    ~ConnectPool() = default;
    std::shared_ptr<ClientCommunicator> getConnection(const int &timeout);
    void releaseConnection(std::shared_ptr<ClientCommunicator> connection);
private:
    std::string server_ip_;
    int server_port_;
    int pool_size_;
    std::queue<std::shared_ptr<ClientCommunicator>> connections_;
    std::mutex mutex_;
    std::condition_variable cv_;
};



#endif // CONNECTPOOL_H