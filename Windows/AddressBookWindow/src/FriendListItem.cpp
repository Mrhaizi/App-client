
#include "FriendListItem.h"
#include "ChatMessage.h"
#include "PersonManager.h"
#include <QtWidgets/qpushbutton.h>
FriendListItem::FriendListItem(const QString image_path, PersonalPublicInfo info, QWidget *parent, ClientCommunicator::ptr clientcommunicator) :
    ListItemBase(parent),
    ui_(std::make_shared<Ui::FriendListItem>()),
    clientcommunicator_(clientcommunicator),
    m_info(info){
        setItemType(ListItemType::ChatUserItem);
        ui_->setupUi(this);
        ui_->label_name->setText(QString::fromStdString(info.username));
        QPixmap pixmap(image_path);
        ui_->label_image->setPixmap(pixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        connect(ui_->pushButton, &QPushButton::clicked, this, &FriendListItem::addFriend);
}

void FriendListItem::addFriend() {
    auto friend_list = PersonManager::singleton::getInstance()->getPrivateInfo().friend_list;
    auto friend_apply = PersonManager::singleton::getInstance()->getPrivateInfo().friend_apply;
    for (auto it : friend_list) {
        if(it.id == m_info.id) {
            return;
        }
    }
    for (auto o_it : friend_apply) {
        if(o_it.id == m_info.id) {
            return;
        }
    }
    AddFriendRequestMessage msg(m_info.username, m_info.id, PersonManager::singleton::getInstance()->getPublicInfo().username,PersonManager::singleton::getInstance()->getPublicInfo().id);
    clientcommunicator_->sendMessage(AddFriendRequest, QString::fromStdString(msg.toJson().dump()).toUtf8());
}