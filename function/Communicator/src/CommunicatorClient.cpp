#include "CommunicatorClient.h"

ClientCommunicator::ClientCommunicator(QObject *parent, const int &port, const std::string &ip) 
    : QTcpSocket(parent),
    port_(port),
    host_(ip) {
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


void ClientCommunicator::connectToHost(const QString &host, quint16 port)
{   //此方法非阻塞，会立即返回，连接的结果会通过 connected 信号通知。
    QTcpSocket::connectToHost(host, port);
}

void ClientCommunicator::sendMessage(const QString &message)
{
    if (this->state() == QAbstractSocket::ConnectedState) {
        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);

        stream << quint16(0); // 占位符，用于后续填充消息长度
        stream << message;    // 消息内容

        stream.device()->seek(0);
        stream << quint16(byteArray.size() - sizeof(quint16)); // 填充实际的消息长度

        this->write(byteArray);
        this->flush();
    } else {
        qDebug() << "Not connected!";
    }
}

void ClientCommunicator::onConnected()
{
    qDebug("Connected to server.");
    sendMessage("hello,connect successfully");
}

void ClientCommunicator::onReadyRead()
{
    // 当有数据可读时，读取所有数据
    buffer_.append(this->readAll());
    QDataStream stream(&buffer_, QIODevice::ReadOnly);
    forever {
            //先解析头部
        if(!b_recv_pending_){
            // 检查缓冲区中的数据是否足够解析出一个消息头（消息ID + 消息长度）
            if (buffer_.size() < static_cast<int>(sizeof(quint16) * 2)) {
                return; // 数据不够，等待更多数据
            }

            // 预读取消息ID和消息长度，但不从缓冲区中移除
            stream >> message_id_ >> message_len_;

            //将buffer 中的前四个字节移除
            buffer_ = buffer_.mid(sizeof(quint16) * 2);
        }

        //buffer剩余长读是否满足消息体长度，不满足则退出继续等待接受
        if(buffer_.size() < message_len_){
            b_recv_pending_ = true;
            return;
        }

        b_recv_pending_ = false;
        // 读取消息体
        QByteArray messageBody = buffer_.mid(0, message_len_);
        // 清空缓存
        buffer_ = buffer_.mid(message_len_);
        emit messageReceived(messageBody);
    }
}

