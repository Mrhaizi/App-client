#include <iostream>
#include <qdebug.h>
#include <unistd.h>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>

#include "ChatWindow.h"
#include "ChatMessage.h"
#include "PersonManager.h"


ChatWindow::ChatWindow(QWidget *parent, std::shared_ptr<ClientCommunicator> clientcommunicator) :
    QWidget(parent),
    clientcommunicator_(clientcommunicator),
    ui_(std::make_shared<Ui::ChatWindow>())
    {
        ui_->setupUi(this);
        m_message_layout = new QVBoxLayout(ui_->scrollAreaWidgetContents_message_container);
        m_message_layout->setAlignment(Qt::AlignTop); // 消息从顶部开始排列
        ui_->scrollArea->setWidget(ui_->scrollAreaWidgetContents_message_container);
        ui_->scrollArea->setWidgetResizable(true);
        if (clientcommunicator_ == nullptr) {
            clientcommunicator_ = ConnectPool::getInstance(
            ServerConfigManager::getInstance().getIP(),
            ServerConfigManager::getInstance().getPort()).getConnection(500);
        // 尝试连接到主机
            clientcommunicator_->connectToHost();
        }
        initFriendList();
        connect(ui_->pushButton_send, &QPushButton::clicked, this, &ChatWindow::sendMsg);
        connect(ui_->listWidget_friend_list, &QListWidget::itemClicked, this, &ChatWindow::chooseChatObject);
        connect(this, &ChatWindow::haveMsg, this, &ChatWindow::addMsg);
        connect(clientcommunicator_.get(), &ClientCommunicator::messageReceivedChat, this, &ChatWindow::receiveMsg);
    }
void ChatWindow::addMsg(const QString &text, bool isSentByUser) {
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
    // 将 QHBoxLayout 添加到主的 m_message_layout 中
    QWidget *messageContainerWidget = new QWidget();
    messageContainerWidget->setLayout(messageContainerLayout);
    m_message_layout->addWidget(messageContainerWidget);
    // 自动滚动到底部
    ui_->scrollArea->verticalScrollBar()->setValue(ui_->scrollArea->verticalScrollBar()->maximum());
}
void ChatWindow::sendMsg() {
    try {
        if (clientcommunicator_->state() == QAbstractSocket::ConnectedState) {
            // 获取用户输入
            QString user_input = ui_->textEdit_chat->toPlainText();
            // 检查输入是否为空且连接是否成功
            if (!user_input.isEmpty()) {
                // 构造聊天消息
                ChatMessage msg = ChatMessage(
                    user_input.toStdString(),
                    PersonManager::singleton::getInstance()->getPublicInfo().username,
                    chatobject_.username,
                    chatobject_.id,
                    PersonManager::singleton::getInstance()->getPublicInfo().id);
                QString send_msg = QString::fromStdString(msg.toJson().dump());
                clientcommunicator_->sendMessage(Chat, send_msg.toUtf8());
                emit haveMsg(user_input, true);
                // 清空输入框
                ui_->textEdit_chat->clear();
            } else {
                // 处理消息为空或未连接的情况
                qDebug() << "消息为空或未连接到服务器。";
            }
        }
    } catch (const std::exception& e) {
        // 处理异常并输出日志
        qDebug() << "发送消息时发生异常: " << e.what();
        clientcommunicator_->connectToHost();
    }
}

void ChatWindow::receiveMsg(const QString& msg) {
    std::cout << "have_msg" << std::endl;
    ChatMessage chat_msg =  ChatMessage();
    chat_msg.castFromString(msg.toStdString());
    std::cout << "content :"  << chat_msg.getConent() << std::endl;
    emit haveMsg(QString::fromStdString(chat_msg.getConent()), false);
}

void ChatWindow::initFriendList() {
    ui_->listWidget_friend_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui_->listWidget_friend_list, &QListWidget::customContextMenuRequested, this, &ChatWindow::showContextMenu);
    for (const auto it : PersonManager::singleton::getInstance()->getPrivateInfo().friend_list) {
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
void ChatWindow::chooseChatObject(QListWidgetItem *item) {
    FriendChatListItemWindow *frienditem = qobject_cast<FriendChatListItemWindow *>(ui_->listWidget_friend_list->itemWidget(item));
    if (frienditem) {
        QFont font;
        font.setPointSize(25); // 设置字体大小
        ui_->label_friend_name->setFont(font);
        ui_->label_friend_name->setText(frienditem->getName());
        ui_->label_friend_name->setAlignment(Qt::AlignCenter);
        chatobject_ = PersonalPublicInfo(frienditem->getName().toStdString(), frienditem->getId(), frienditem->getAge(), frienditem->getemail().toStdString());
    }
}
void ChatWindow::saveChatHistory() {
}
void ChatWindow::updateFriendList() {
}