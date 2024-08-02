#include "FriendWindow.h"

FriendWindow::FriendWindow(QWidget *parent) :
    QWidget(parent),
    ui_(std::make_shared<Ui::FriendWindow>()) {
        ui_->setupUi(this);
        
    }