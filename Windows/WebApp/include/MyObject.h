#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QDebug>

class MyObject : public QObject
{
    Q_OBJECT
public:
    explicit MyObject(QObject *parent = nullptr);

signals:
    void sendToJs(const QString &message);

public slots:
    void receiveFromJs(const QString &message);
    QString getData() const;
};

#endif // MYOBJECT_H
