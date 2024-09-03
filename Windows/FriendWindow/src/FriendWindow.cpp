#include "FriendWindow.h"
#include "ChatMessage.h"
#include <iostream>
#include <qdebug.h>

FriendWindow::FriendWindow(QWidget *parent, std::shared_ptr<PersonManager> personmanager, std::shared_ptr<ClientCommunicator> clientcommunicator) :
    QWidget(parent),
    ui_(std::make_shared<Ui::FriendWindow>()),
    personalinfomanager_(personmanager),
    clientcommunicator_(clientcommunicator) {
        ui_->setupUi(this);
        initFriendList();
        connect(ui_->pushButton_send, &QPushButton::clicked, this, &FriendWindow::sendMsg);
        connect(ui_->listWidget_friend_list, &QListWidget::itemClicked, this, &FriendWindow::chooseChatObject);
    }

void FriendWindow::sendMsg() {
    QString user_input = ui_->textEdit_chat->toPlainText();
    if (!user_input.isEmpty()) {
        ChatMessage msg = ChatMessage(user_input.toStdString(), personalinfomanager_->getPublicInfo().username, chatobject_.username);
        clientcommunicator_->sendMessage(QString::fromStdString(msg.toJson().dump()));
        ui_->textEdit_chat->clear();
    }
}

void FriendWindow::initFriendList() {
    ui_->listWidget_friend_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui_->listWidget_friend_list, &QListWidget::customContextMenuRequested, this, &FriendWindow::showContextMenu);
    FriendListItemWindow *demo =  new FriendListItemWindow("/home/myq/Desktop/my_code/App-client/test/1.jpg", "baby");
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(demo->sizeHint());
    ui_->listWidget_friend_list->addItem(item);
    ui_->listWidget_friend_list->setItemWidget(item, demo);
}

void FriendWindow::showContextMenu(const QPoint &point) {
        // 获取被点击的项
        QListWidgetItem *item = ui_->listWidget_friend_list->itemAt(point);
        if (item) {
            QMenu contextMenu;
            QAction *viewInfoAction = contextMenu.addAction("查看个人信息");
            QAction *deleteFriendAction = contextMenu.addAction("删除好友");
            // 显示菜单，并获取用户选择的选项
            QAction *selectedAction = contextMenu.exec(mapToGlobal(point));
            
            if (selectedAction == viewInfoAction) {
                QMessageBox::information(this, "信息", "显示个人信息：" + item->text());
            } else if (selectedAction == deleteFriendAction) {
                delete item;  // 删除好友（列表项）
            }
        }    
} 

void FriendWindow::chooseChatObject(QListWidgetItem *item) {
    FriendListItemWindow *frienditem = qobject_cast<FriendListItemWindow *>(ui_->listWidget_friend_list->itemWidget(item));
    if (frienditem) {
        QFont font;
        font.setPointSize(25); // 设置字体大小
        ui_->label_friend_name->setFont(font);
        ui_->label_friend_name->setText(frienditem->getName());
        ui_->label_friend_name->setAlignment(Qt::AlignCenter);
        chatobject_ = PersonalPublicInfo{"baby", 1, "2127800097@qq.com", 18};
    }
}

void FriendWindow::saveChatHistory() {

}
void FriendWindow::updateFriendList() {
    
}





