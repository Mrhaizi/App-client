#include <HomeWindow.h>

HomeWindow::HomeWindow(QWidget *Parent) 
    : ui_(std::make_shared<Ui::HomeWindow>()),
      QWidget(Parent) 
    {

        ui_->setupUi(this);
        initAllWindow();
        connect(ui_->pushButton_friend, &QPushButton::clicked, this, &HomeWindow::showFriendWindow);
        connect(ui_->pushButton_play_game, &QPushButton::clicked, this, &HomeWindow::showPlayGameWindow);
    }

void HomeWindow::showFriendWindow() {
    
    ui_->stackedWidget_run_function->setCurrentWidget(friendwindow_);
    // if (chatwindow_ != nullptr) {
    //     chatwindow_ = nullptr;
    // }
    // chatwindow_ = std::make_shared<ChatWindow>(ui_->widget_friend);
    // chatwindow_->setGeometry(ui_->widget_friend->rect());
    // chatwindow_->show();
}

void HomeWindow::showPlayGameWindow() {

}

void HomeWindow::initAllWindow() {
    friendwindow_ = new FriendWindow();
    ui_->stackedWidget_run_function->addWidget(friendwindow_);
}

