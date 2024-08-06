#include "FriendWindow.h"

FriendWindow::FriendWindow(QWidget *parent) :
    QWidget(parent),
    ui_(std::make_shared<Ui::FriendWindow>()) {
        ui_->setupUi(this);
        connect(ui_->pushButton_send, &QPushButton::clicked, this, &FriendWindow::sendMsg);
    }

void FriendWindow::sendMsg() {
    

}

void FriendWindow::loadChatHistory() {

}
