#ifndef CLIENTCOMMUNICATOR_H
#define CLIENTCOMMUNICATOR_H

#include <QTcpSocket>
#include <QBuffer>
#include <QDataStream>
#include <QString>
#include <QObject>

#include <nlohmann/json.hpp>

#include "ChatMessage.h"



class ClientCommunicator : public QTcpSocket
{
    Q_OBJECT
public:
    typedef std::shared_ptr<ClientCommunicator> ptr;
    explicit ClientCommunicator(QObject *parent = nullptr, const int &port = 0, const std::string &ip = "");
    ~ClientCommunicator();

    void connectToHost();
    
    void sendMessage(MessageType type, const QByteArray &message);
signals:
    void messageReceivedChat(const QString &message);
    void messageReceivedLogRes(const QString &message);
    void messageReceivedRegRes(const QString &message);
    void messageReceivedCache(const QString &message);
private slots:
    void onConnected();
    void onReadyRead();
private:
    QString host_;
    int port_;
    QByteArray buffer_;
    bool b_recv_pending_;
    // quint16 message_id_;
    quint16 message_len_;
    uint32_t packet_length_;   // 包长度（4 bytes）
    uint16_t func_id_;     // 包类型（2 bytes）
    uint8_t version_;   // 版本号（1 byte）
    uint8_t reserved_;  // 保留字段（1 byte）
};

#endif // CLIENTCOMMUNICATOR_H


