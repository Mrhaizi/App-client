#include "CommunityMainWindow.h"

CommunityMainWindow::CommunityMainWindow(QWidget* parent) : 
    QWidget(parent),
    ui_(std::make_shared<Ui::Community>()) {
    ui_->setupUi(this);
}