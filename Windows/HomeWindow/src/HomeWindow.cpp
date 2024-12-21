#include "AddressBookWindow.h"
#include <HomeWindow.h>

HomeWindow::HomeWindow(QWidget *parent, ClientCommunicator::ptr clientcommunicator) 
    : ui_(std::make_shared<Ui::HomeWindow>()),
      clientcommunicator_(clientcommunicator),
      QWidget(parent)
    {
        ui_->setupUi(this);
        connect(ui_->pushButton_addressbook, &QPushButton::clicked, this, &HomeWindow::showAddressBookWindow);
        connect(ui_->pushButton_chat, &QPushButton::clicked, this, &HomeWindow::showChatWindow);
        connect(ui_->pushButton_play_game, &QPushButton::clicked, this, &HomeWindow::showPlayGameWindow);
        connect(ui_->pushButton_community, &QPushButton::clicked, this, &HomeWindow::showCommunityWindow);
    }

void HomeWindow::showAddressBookWindow() {
    ui_->stackedWidget_run_function->setCurrentWidget(addressbookwindow_);
    // if (chatwindow_ != nullptr) {
    //     chatwindow_ = nullptr;
    // }
    // chatwindow_ = std::make_shared<ChatWindow>(ui_->widget_friend);
    // chatwindow_->setGeometry(ui_->widget_friend->rect());
    // chatwindow_->show();
}

void HomeWindow::init() {
    initAllWindow();
}
void HomeWindow::showPlayGameWindow() {
}

void HomeWindow::initAllWindow() {
    chatwindow_ = new ChatWindow(nullptr, clientcommunicator_);
    chatwindow_->init();
    addressbookwindow_ = new AddressBookWindow(nullptr);
    communitymainwindow_ = new CommunityMainWindow(nullptr);
    ui_->stackedWidget_run_function->addWidget(chatwindow_);
    ui_->stackedWidget_run_function->addWidget(addressbookwindow_);
    ui_->stackedWidget_run_function->addWidget(communitymainwindow_);
}

void HomeWindow::showChatWindow() {
    ui_->stackedWidget_run_function->setCurrentWidget(chatwindow_);
}

void HomeWindow::showShopWindow() {

}

void HomeWindow::showSettingWindow() {

}

void HomeWindow::showCommunityWindow() {
    ui_->stackedWidget_run_function->setCurrentWidget(communitymainwindow_);
}

