#include "AddFriendGroup.h"

FindWindow::FindWindow(QWidget* parent, std::shared_ptr<ClientCommunicator> clientcommunicator) : 
    QWidget(parent),
    ui_(std::make_shared<Ui::FindWindow>()),
    clientcommunicator_(clientcommunicator) {
    ui_->setupUi(this);
    connect(ui_->lineEdit_search, &QLineEdit::returnPressed, this, &FindWindow::performSearch);
}
void FindWindow::performSearch() {
    QString keyword = ui_->lineEdit_search->text();
    if (keyword.isEmpty()) {
        QMessageBox::information(this, "提示", "请输入关键词进行搜索");
        return;
    }
    auto search_results = PersonManager::singleton::getInstance()->searchPerson(keyword.toStdString());

    // 清空现有的列表项（如果需要）
    ui_->listWidget_all->clear();
    ui_->listWidget_user->clear();
    // 遍历搜索结果，将每个搜索到的好友信息添加到两个列表中
    // 创建 FriendListItem 对象
    for (auto info : search_results) {
        auto *item_widget = new FriendListItem(":/path/to/image.png", info, this, clientcommunicator_);
        // 创建 QListWidgetItem，设置大小，并将 FriendListItem 作为子控件
        auto *list_item_all = new QListWidgetItem();
        list_item_all->setSizeHint(item_widget->sizeHint());

        // 将 FriendListItem 添加到 widgetlist_all
        ui_->listWidget_all->addItem(list_item_all);
        ui_->listWidget_all->setItemWidget(list_item_all, item_widget);

        // 将 FriendListItem 添加到 widgetlist_friend
        auto *item_widget_copy = new FriendListItem(":/path/to/image.png", info, this, clientcommunicator_);
        auto *list_item_friend = new QListWidgetItem();
        list_item_friend->setSizeHint(item_widget_copy->sizeHint());

        ui_->listWidget_user->addItem(list_item_friend);
        ui_->listWidget_user->setItemWidget(list_item_friend, item_widget_copy);
    }
    // AddFriendRequestMessage temp( keyword.toStdString(), 0, temp_value.username, temp_value.id);
    // clientcommunicator_->sendMessage(AddFriendRequest, QString::fromStdString(temp.toJson().dump()).toUtf8());
}