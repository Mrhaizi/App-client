#include "MyObject.h"
#include "PersonManager.h"

MyObject::MyObject(QObject* parent) : QObject(parent)  {

}

QString MyObject::getData() const {
    PersonManager::singleton::getInstance()->getJwdCode();
}

void MyObject::receiveFromJs(const QString &message) {

}
