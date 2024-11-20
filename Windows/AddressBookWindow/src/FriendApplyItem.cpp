#include "FriendApplyItem.h"
#include "ChatMessage.h"
#include "PersonManager.h"
#include <QtWidgets/qpushbutton.h>

FriendApplyItem::FriendApplyItem(const QString image_path, PersonalPublicInfo info, QWidget *parent, ClientCommunicator::ptr clientcommunicator) :
    ListItemBase(parent),
    ui_(std::make_shared<Ui::FriendApplyItem>()),
    clientcommunicator_(clientcommunicator),
    m_info(info){
        setItemType(ListItemType::ChatUserItem);
        ui_->setupUi(this);
        ui_->label_name->setText(QString::fromStdString(info.username));
        QPixmap pixmap(image_path);
        ui_->label_image->setPixmap(pixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        connect(ui_->pushButton_accept, &QPushButton::clicked, this, &FriendApplyItem::accept);
        connect(ui_->pushButton_refuse, &QPushButton::clicked, this, &FriendApplyItem::refuse);
}

void FriendApplyItem::accept() {
    FriendConfirmMessage confirm_msg(true, m_info.id, PersonManager::singleton::getInstance()->getPublicInfo().id );
    clientcommunicator_->sendMessage(FriendConfirm, QString::fromStdString(confirm_msg.toJson().dump()).toUtf8());
}

void FriendApplyItem::refuse() {
    FriendConfirmMessage confirm_msg(false, m_info.id, PersonManager::singleton::getInstance()->getPublicInfo().id );
    clientcommunicator_->sendMessage(FriendConfirm, QString::fromStdString(confirm_msg.toJson().dump()).toUtf8());
}
