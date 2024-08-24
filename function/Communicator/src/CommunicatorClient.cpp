#include "CommunicatorClient.h"

ClientCommunicator::ClientCommunicator(QObject *parent)
    : QTcpSocket(parent)
{
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
    if (state() == QAbstractSocket::ConnectedState) {
        write(message.toUtf8());
        flush();  // 确保数据立即发送
    } else {
        qWarning("Not connected to host.");
    }
}

void ClientCommunicator::onConnected()
{
    qDebug("Connected to server.");
    sendMessage("hello");
}

void ClientCommunicator::onReadyRead()
{
    // 当有数据可读时，读取所有数据
    buffer_.append(socket_.readAll());
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

            // 输出读取的数据
            qDebug() << "Message ID:" << message_id_ << ", Length:" << message_len_;

        }

        //buffer剩余长读是否满足消息体长度，不满足则退出继续等待接受
        if(buffer_.size() < message_len_){
            b_recv_pending_ = true;
            return;
        }

        b_recv_pending_ = false;
        // 读取消息体
        QByteArray messageBody = buffer_.mid(0, message_len_);
        qDebug() << "receive body msg is " << messageBody ;

        buffer_ = buffer_.mid(message_len_);
    }
}

