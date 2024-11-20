#ifndef FRIENDLISTITEMWINDOW_H
#define FRIENDLISTITEMWINDOW_H

#include <iostream>
#include <string>
#include <memory>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>
#include <QFile>
#include <QString>

#include "ui_friendchatlistitem.h"
#include "ListItemBase.h"

QT_BEGIN_NAMESPACE
namespace Ui {class FriendChatListItemWindow;}
QT_END_NAMESPACE

class FriendChatListItemWindow : public ListItemBase {
    Q_OBJECT
public:
    FriendChatListItemWindow(const QString image_path, PersonalPublicInfo info, QWidget *parent = nullptr);
    QSize sizeHint() const override {
        return QSize(200, 100);

    };
    QString getName() {return QString::fromStdString(m_info.username);}
    QString getemail(){return QString::fromStdString(m_info.email);}
    uint64_t getId() {return m_info.id;}
    int getAge() {return m_info.age;}
private:
    PersonalPublicInfo m_info;
    std::shared_ptr<Ui::FriendChatListItemWindow> ui_;
};

#endif // FRIENDLISTITEMWINIDOW_H

