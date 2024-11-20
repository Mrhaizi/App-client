#ifndef FRIENDAPPLYITEM_H
#define FRIENDAPPLYITEM_H

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

#include "CommunicatorClient.h"
#include "ListItemBase.h"
#include "ui_friendapplyitem.h"

QT_BEGIN_NAMESPACE
namespace Ui {class FriendApplyItem;}
QT_END_NAMESPACE

class FriendApplyItem : public ListItemBase {
    Q_OBJECT
public:
    FriendApplyItem(const QString image_path, PersonalPublicInfo info, QWidget *parent = nullptr, ClientCommunicator::ptr clientcommunicator = nullptr);
    QSize sizeHint() const override {
        return QSize(200, 100);
    };
    QString getName() {return QString::fromStdString(m_info.username);}
    QString getemail(){return QString::fromStdString(m_info.email);}
    uint64_t getId() {return m_info.id;}
    int getAge() {return m_info.age;}
private slots:
    void accept();
    void refuse();
private:
    PersonalPublicInfo m_info;
    std::shared_ptr<Ui::FriendApplyItem> ui_;
    ClientCommunicator::ptr clientcommunicator_;
};
#endif // FRIENDAPPLYITEM_H