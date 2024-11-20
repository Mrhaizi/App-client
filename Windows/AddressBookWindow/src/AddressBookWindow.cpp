#include "AddressBookWindow.h"
#include <QtWidgets/qpushbutton.h>
#include "FriendApplyItem.h"
AddressBookWindow::AddressBookWindow(QWidget* parent) :
    QWidget(parent),
    ui_(std::make_shared<Ui::AddressBookWindow>()) {
    clientcommunicator_ = ConnectPool::getInstance(
    ServerConfigManager::getInstance().getIP(),
    ServerConfigManager::getInstance().getPort()).getConnection(500);
// 尝试连接到主机
    clientcommunicator_->connectToHost();
    ui_->setupUi(this);
    connect(ui_->pushButton_add_friend, &QPushButton::clicked, this, &AddressBookWindow::showFindWindow);
    connect(ui_->pushButton_friend_inform, &QPushButton::clicked, this, &AddressBookWindow::showFriendInform);
}
void AddressBookWindow::initAddressBookList() {
    // 切换到 page_function 页面，确保好友列表出现在正确的位置
    ui_->stackedWidget->setCurrentWidget(ui_->page_function);

    // 清空现有的好友列表项
    QLayoutItem *item;
    while ((item = ui_->verticalLayout_friend_list->takeAt(0)) != nullptr) {
        delete item->widget();  // 删除子部件
        delete item;  // 删除布局项
    }
    // 设置好友列表滚动区域的右键菜单策略
    ui_->scrollArea_friend_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui_->scrollArea_friend_list, &QScrollArea::customContextMenuRequested, this, &AddressBookWindow::showContextMenu);

    // 遍历好友列表并动态添加到布局中
    for (const auto& it : PersonManager::singleton::getInstance()->getPrivateInfo().friend_list) {
        // 创建 FriendListItem 实例，初始化头像和好友信息
        FriendListItem *demo = new FriendListItem("/home/myq/Desktop/my_code/App-client/test/1.jpg", it, this);

        // 将 FriendListItem 添加到垂直布局中
        ui_->verticalLayout_friend_list->addWidget(demo);
    }

    // 添加一个拉伸项，使好友项顶上去
    ui_->verticalLayout_friend_list->addStretch();
    // ui_->stackedWidget->setCurrentWidget(ui_->page_friendlist);
    // ui_->listWidget_friend_list->setContextMenuPolicy(Qt::CustomContextMenu);
    // connect(ui_->listWidget_friend_list, &QListWidget::customContextMenuRequested, this, &AddressBookWindow::showContextMenu);
    // for (const auto it : PersonManager::singleton::getInstance()->getPrivateInfo().friend_list) {
    //     FriendListItem *demo =  new FriendListItem("/home/myq/Desktop/my_code/App-client/test/1.jpg", it);
    //     QListWidgetItem *item = new QListWidgetItem;
    //     item->setSizeHint(demo->sizeHint());
    //     ui_->listWidget_friend_list->addItem(item);
    //     ui_->listWidget_friend_list->setItemWidget(item, demo);
    // }
}
void AddressBookWindow::showContextMenu(const QPoint &point) {
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
void AddressBookWindow::showFindWindow() {
    find_window_ = new FindWindow(nullptr, clientcommunicator_);
    find_window_->show();
}
void AddressBookWindow::showFriendInform() {
    std::vector<PersonalPublicInfo> friend_apply = PersonManager::singleton::getInstance()->getPrivateInfo().friend_apply;
    QLayoutItem *item;
    while ((item = ui_->verticalLayout_request_list->takeAt(0)) != nullptr) {
        delete item->widget();  // 删除子部件
        delete item;  // 删除布局项
    }
    for (const PersonalPublicInfo &request : friend_apply) {
        auto *friendItem = new FriendApplyItem("", request, this, clientcommunicator_);
        ui_->verticalLayout_request_list->addWidget(friendItem);
    }
    ui_->verticalLayout_request_list->addStretch();
}



