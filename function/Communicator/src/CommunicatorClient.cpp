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
    QByteArray data = readAll();
    QString message = QString::fromUtf8(data);
    emit messageReceived(message);
}

