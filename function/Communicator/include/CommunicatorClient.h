#ifndef CLIENTCOMMUNICATOR_H
#define CLIENTCOMMUNICATOR_H

#include <QTcpSocket>
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
};

#endif // CLIENTCOMMUNICATOR_H


