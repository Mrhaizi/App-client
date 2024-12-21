#include <iostream>
#include <qdebug.h>
#include <qjsondocument.h>
#include <unistd.h>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QJsonObject>
#include "ChatWindow.h"
#include "ChatMessage.h"
#include "MessageMgr.h"
#include "PersonManager.h"


ChatWindow::ChatWindow(QWidget *parent, std::shared_ptr<ClientCommunicator> clientcommunicator) :
    QWidget(parent),
    clientcommunicator_(clientcommunicator),
    ui_(std::make_shared<Ui::ChatWindow>()),
    message_mgr_(new MessageManager(this))
    {
        ui_->setupUi(this);
        m_message_layout = new QVBoxLayout(ui_->scrollAreaWidgetContents_message_container);
        m_message_layout->setAlignment(Qt::AlignTop);
        ui_->scrollArea->setWidget(ui_->scrollAreaWidgetContents_message_container);
        ui_->scrollArea->setWidgetResizable(true);
        connect(ui_->pushButton_send, &QPushButton::clicked, this, &ChatWindow::sendMsg);
        connect(ui_->listWidget_friend_list, &QListWidget::itemClicked, this, &ChatWindow::switchChatObject);
        connect(this, &ChatWindow::haveMsg, this, &ChatWindow::addtextMsg);
        connect(WebSocketHandler::GetInstance().get(), &WebSocketHandler::chatmessageReceived, this, &ChatWindow::machineMsg);
        connect(message_mgr_, &MessageManager::privateMessageDispatched, this, &ChatWindow::handlePrivateMessage);
        connect(message_mgr_, &MessageManager::groupMessageDispatched, this, &ChatWindow::handleGroupMessage);
    }
void ChatWindow::init() {
    initFriendList();
}
void ChatWindow::addtextMsg(const QString &text, bool isSentByUser) {
    QLabel *message_label = new QLabel(text, this);
    message_label->setWordWrap(true); // 设置自动换行
    // 设置消息样式
    if (isSentByUser) {
        message_label->setStyleSheet("background-color: #DCF8C6; border-radius: 10px; padding: 8px;");
    } else {
        message_label->setStyleSheet("background-color: #FFFFFF; border-radius: 10px; padding: 8px;");
    }
    // 创建一个 QHBoxLayout 用于设置对齐
    QHBoxLayout *messageContainerLayout = new QHBoxLayout();
    if (isSentByUser) {
        messageContainerLayout->setAlignment(Qt::AlignRight); // 右对齐
    } else {
        messageContainerLayout->setAlignment(Qt::AlignLeft); // 左对齐
    }
    // 将消息标签添加到 QHBoxLayout
    messageContainerLayout->addWidget(message_label);
    QWidget *messageContainerWidget = new QWidget();
    messageContainerWidget->setLayout(messageContainerLayout);
    m_message_layout->addWidget(messageContainerWidget);
    // 自动滚动到底部
    ui_->scrollArea->verticalScrollBar()->setValue(ui_->scrollArea->verticalScrollBar()->maximum());
}
void ChatWindow::machineMsg(const QJsonObject& msg) {
}
void ChatWindow::sendMsg() {
    QString user_input = ui_->textEdit_chat->toPlainText();
    if (!user_input.isEmpty()) {
        QJsonObject msg_object;
        msg_object["type"] = "chat_message";
        msg_object["from_user_id"] = (int)PersonManager::singleton::getInstance()->getPublicInfo().id;
        msg_object["to_user_id"] = (int)chatobject_.id;
        msg_object["content"] = user_input;
        // 发送消息
        WebSocketHandler::GetInstance()->sendMessage(msg_object);
        // 创建 ChatMessage 对象并添加到消息管理器
        ChatMessage chat_msg;
        chat_msg.setContent(user_input.toStdString());
        chat_msg.setTimestamp(QDateTime::currentDateTime().toString().toStdString());
        chat_msg.setSendByUser(true);
        message_mgr_->addPrivateMessage(chatobject_.id, chat_msg);
        ui_->textEdit_chat->clear();
    }
}


void ChatWindow::initFriendList() {
    ui_->listWidget_friend_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui_->listWidget_friend_list, &QListWidget::customContextMenuRequested, this, &ChatWindow::showContextMenu);
    for (const auto it : PersonManager::singleton::getInstance()->getPrivateInfo().friend_list) {
        std::cout << it.username << std::endl;
        std::cout << it.id << std::endl;
        FriendChatListItemWindow *demo =  new FriendChatListItemWindow("/home/myq/Desktop/my_code/App-client/test/1.jpg", it);
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(demo->sizeHint());
        ui_->listWidget_friend_list->addItem(item);
        ui_->listWidget_friend_list->setItemWidget(item, demo);
    }
}

void ChatWindow::showContextMenu(const QPoint &point) {
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
void ChatWindow::switchChatObject(QListWidgetItem *item) {
    // 获取点击的好友项
    FriendChatListItemWindow *friendItem = qobject_cast<FriendChatListItemWindow *>(ui_->listWidget_friend_list->itemWidget(item));
    if (friendItem) {
        uint64_t new_chat_id = friendItem->getId();
        // 如果切换到了不同的聊天对象
        if (new_chat_id != currentChatId_) {
            // 更新当前聊天对象 ID
            currentChatId_ = new_chat_id;
            // 更新聊天窗口的标题
            QFont font;
            font.setPointSize(25); // 设置字体大小
            ui_->label_friend_name->setFont(font);
            ui_->label_friend_name->setText(friendItem->getName());
            ui_->label_friend_name->setAlignment(Qt::AlignCenter);
            // 更新聊天对象的信息
            chatobject_ = PersonalPublicInfo(friendItem->getName().toStdString(), friendItem->getId(), friendItem->getAge(), friendItem->getemail().toStdString());
            // 加载新的聊天历史
            loadChatHistory(new_chat_id);
            // 清除未读消息计数
            unreadCounts_[new_chat_id] = 0;
            updateUnreadCount(new_chat_id);
        }
    }
}

void ChatWindow::saveChatHistory() {
}
void ChatWindow::updateFriendList() {
}
void ChatWindow::handlePrivateMessage(uint64_t user_id, const ChatMessage& msg) {
    if (chatobject_.id == user_id) { // 如果是当前聊天对象
        emit haveMsg(QString::fromStdString(msg.getConent()), msg.isSendByUser());
    } else {
        markMessageAsUnread(user_id);
        updateUnreadCount(user_id);
    }
}

void ChatWindow::handleGroupMessage(uint64_t groupId, const ChatMessage &msg) {
    // qDebug() << "收到群组消息：" << QString::fromStdString(msg.getConent());
}

void ChatWindow::loadChatHistory(uint64_t chatId) {
    // 清空当前消息界面
    QLayoutItem *item;
    while ((item = m_message_layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    // 获取聊天记录
    QVector<ChatMessage> messages = message_mgr_->getPrivateMessages(chatId);
    // 加载聊天记录到界面
    for (const auto &msg : messages) {
        emit haveMsg(QString::fromStdString(msg.getConent()), msg.isSendByUser());
    }
}

void ChatWindow::markMessageAsUnread(uint64_t senderId) {
    if (!unreadCounts_.contains(senderId)) {
        unreadCounts_[senderId] = 0;
    }
    unreadCounts_[senderId]++;
}

void ChatWindow::updateUnreadCount(uint64_t chatId) {
    // 更新好友列表项的未读消息计数
    for (int i = 0; i < ui_->listWidget_friend_list->count(); ++i) {
        QListWidgetItem *item = ui_->listWidget_friend_list->item(i);
        FriendChatListItemWindow *friendItem = qobject_cast<FriendChatListItemWindow *>(ui_->listWidget_friend_list->itemWidget(item));
        if (friendItem && friendItem->getId() == chatId) {
            QString displayName = friendItem->getName();
            if (unreadCounts_[chatId] > 0) {
                displayName += QString(" (%1)").arg(unreadCounts_[chatId]); // 添加未读计数
            }
            item->setText(displayName);
            break;
        }
    }
}