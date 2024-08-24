#ifndef CLIENTCOMMUNICATOR_H
#define CLIENTCOMMUNICATOR_H

#include <QTcpSocket>
#include <QBuffer>
#include <QDataStream>
#include <QString>
#include <QObject>

class ClientCommunicator : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientCommunicator(QObject *parent = nullptr);
    ~ClientCommunicator();

    void connectToHost(const QString &host, quint16 port);
    void sendMessage(const QString &message);
    
signals:
    void messageReceived(const QString &message);

private slots:
    void onConnected();
    void onReadyRead();
private:
    QTcpSocket socket_;
    QString host_;
    uint16_t port_;
    QByteArray buffer_;
    bool b_recv_pending_;
    quint16 message_id_;
    quint16 message_len_;
};

#endif // CLIENTCOMMUNICATOR_H


