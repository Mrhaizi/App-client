#include "FriendApplyItem.h"
#include "ChatMessage.h"
#include "PersonManager.h"
#include <QtWebSockets/qwebsocket.h>
#include <QtWidgets/qpushbutton.h>
#include <qjsonobject.h>
#include <string>
#include "WebSocketMgr.h"

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
    QJsonObject msg;

    std::cout << m_info.id << std::endl;
    msg["type"] = "accept_friend";
    msg["request_id"] = (int)m_info.id;
    WebSocketHandler::GetInstance()->sendMessage(msg);
    this->close();
}

void FriendApplyItem::refuse() {
    QJsonObject msg;
    msg["type"] = "reject_friend";
    std::cout << m_info.id << std::endl;
    msg["request_id"] = (int)m_info.id;
    WebSocketHandler::GetInstance()->sendMessage(msg);
    this->close();
}
