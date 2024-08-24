#include "FriendListItem.h"

FriendListItemWindow::FriendListItemWindow(const QString image_path, const QString &name, QWidget *parent) :
    ListItemBase(parent),
    ui_(std::make_shared<Ui::FriendListItemWindow>()) {
        setItemType(ListItemType::CHAT_USER_ITEM);
        ui_->setupUi(this);
        ui_->label_name->setText(name);
        QPixmap pixmap(image_path);
        ui_->label_image->setPixmap(pixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }