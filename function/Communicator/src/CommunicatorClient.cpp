#include "CommunicatorClient.h"
#include "MessageBase.h"
#include <QtEndian>


ClientCommunicator::ClientCommunicator(QObject *parent, const int &port, const std::string &ip) 
    : QTcpSocket(parent),
    port_(port),
    host_(QString::fromStdString(ip)) {
    connect(this, &QTcpSocket::connected, this, &ClientCommunicator::onConnected);
    connect(this, &QTcpSocket::readyRead, this, &ClientCommunicator::onReadyRead);
}

ClientCommunicator::~ClientCommunicator()
{
    // 关闭连接并释放资源
    if (isOpen()) {
        close();
    }
}


void ClientCommunicator::connectToHost()
{   //号此方法非阻塞，会立即返回，连接的结果会通过 connected 信通知。
    // std::cout << "start connect" << "host :" << host_.toStdString() << "port:" << port_ <<   std::endl;
    QTcpSocket::connectToHost(host_, port_);
}

void ClientCommunicator::sendMessage(MessageType type, const QByteArray &message)
{
    if (this->state() == QAbstractSocket::ConnectedState) {
        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_12);

        // 预留 4 个字节的长度占位符
        stream << (uint32_t)(message.size());  // 4 字节的包长度，占位符
        uint16_t func_id = type;
        uint8_t version = 55;      // 版本号
        uint8_t reserved = 66;     // 保留字段

        // 写入包头 (包类型、版本号、保留字段)
        stream << func_id;
        stream << version;
        stream << reserved;

        // 写入实际消息内容（包体）
        byteArray.append(message);  // 追加 message 的字节数据到 byteArray(不要用<< 会自动追加长度信息)
        // 发送数据
        this->write(byteArray);
        this->flush();  // 确保数据立即发送

        std::cout << "length : " << message.size() << "start send::" << message.toStdString() << std::endl;
    } else {
        qDebug() << "Not connected!";
    }
}

void ClientCommunicator::onConnected()
{
   if (this->state() == QAbstractSocket::ConnectedState) {
        std::cout << "Connected to server." << std::endl;
        // sendMessage("hello,connect successfully");
    } else {
        qDebug("Connected Erroe");
        std::cout << "connect failed" << std::endl;
    }
}
void ClientCommunicator::onReadyRead()
{
    std::cout << "data arrive" << std::endl;
    // 当有数据可读时，读取所有数据
    buffer_.append(this->readAll());
    char* temp = buffer_.data(); 
    char demo[4096];
    memcpy(&demo[0], temp, 1000);
    QDataStream stream(&buffer_, QIODevice::ReadOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    forever {
        // 解析头部
        if (!b_recv_pending_) {
            // 检查缓冲区中的数据是否足够解析出一个消息头
            if (buffer_.size() < 8) { // 8 字节的包头长度
                return; // 数据不够，等待更多数据
            }
            // 读取消息长度、消息ID、版本号和保留字段
            stream >> packet_length_ >> func_id_ >> version_ >> reserved_;
            packet_length_ = qFromBigEndian(packet_length_);
            func_id_ = qFromBigEndian(func_id_);
            if (packet_length_ < 8) {
                std::cerr << "Invalid packet length" << std::endl;
                buffer_.clear();
                return;
            }
            //将buffer中的前8个字节移除
            buffer_ = buffer_.mid(8);
            message_len_ = packet_length_; // 实际消息体长度
        }

        // 检查buffer剩余长度是否满足消息体长度，不满足则退出继续等待接收
        if (buffer_.size() < message_len_) {
            b_recv_pending_ = true;
            return;
        }

        b_recv_pending_ = false;
        // 读取消息体
        QByteArray messageBody = buffer_.mid(0, message_len_);
        std::cout << "fuc_id : " << func_id_ << " message : "  << messageBody.toStdString() << std::endl;
        // 清空已读的消息体部分
        buffer_ = buffer_.mid(message_len_);
        if (func_id_ == 0x01) {
            std::cout << "this is chat message" << std::endl;
            emit messageReceivedChat(messageBody);
        } else if(func_id_ == 0x03) {
            emit messageReceivedLogRes(messageBody);
        } else if (func_id_ == 0x05) {
            emit messageReceivedRegRes(messageBody);
        } else if (func_id_ == 0x0e) {
            emit messageReceivedCache(messageBody);
        }
    }
}

// void ClientCommunicator::onReadyRead()
// {
//     std::cout << "data arrive" << std::endl;
//     // 当有数据可读时，读取所有数据
//     buffer_.append(this->readAll());
//     QDataStream stream(&buffer_, QIODevice::ReadOnly);
//     forever {
//             //先解析头部
//         if(!b_recv_pending_){
//             // 检查缓冲区中的数据是否足够解析出一个消息头（消息ID + 消息长度）
//             if (buffer_.size() < static_cast<int>(sizeof(quint16) * 2)) {
//                 return; // 数据不够，等待更多数据
//             }

//             // 预读取消息ID和消息长度，但不从缓冲区中移除
//             stream >> message_id_ >> message_len_;

//             //将buffer 中的前四个字节移除
//             buffer_ = buffer_.mid(sizeof(quint16) * 2);
//         }

//         //buffer剩余长读是否满足消息体长度，不满足则退出继续等待接受
//         if(buffer_.size() < message_len_){
//             b_recv_pending_ = true;
//             return;
//         }

//         b_recv_pending_ = false;
//         // 读取消息体
//         QByteArray messageBody = buffer_.mid(0, message_len_);
//         // 清空缓存
//         buffer_ = buffer_.mid(message_len_);
//         emit messageReceived(messageBody);
//     }
// }

