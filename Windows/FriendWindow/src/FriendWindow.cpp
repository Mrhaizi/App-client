#include "FriendWindow.h"

FriendWindow::FriendWindow(QWidget *parent, std::shared_ptr<UserInfoManager> userinfomanager) :
    QWidget(parent),
    ui_(std::make_shared<Ui::FriendWindow>()) ,
    userinfomanager_(userinfomanager) {
        ui_->setupUi(this);
        initFriendList();
        connect(ui_->pushButton_send, &QPushButton::clicked, this, &FriendWindow::sendMsg);
    }

void FriendWindow::sendMsg() {
    

}

void FriendWindow::initFriendList() {
    ui_->listWidget_friend_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui_->listWidget_friend_list, &QListWidget::customContextMenuRequested, this, &FriendWindow::showContextMenu);
    ui_->listWidget_friend_list->addItem("1");
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

void FriendWindow::saveChatHistory() {

}





