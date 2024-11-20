#include "FriendChatListItem.h"

FriendChatListItemWindow::FriendChatListItemWindow(const QString image_path, PersonalPublicInfo info, QWidget *parent) :
    ListItemBase(parent),
    ui_(std::make_shared<Ui::FriendChatListItemWindow>()),
    m_info(info){
        setItemType(ListItemType::ChatUserItem);
        ui_->setupUi(this);
        ui_->label_name->setText(QString::fromStdString(info.username));
        QPixmap pixmap(image_path);
        ui_->label_image->setPixmap(pixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

