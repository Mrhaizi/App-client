#ifndef ADDRESSBOOKWINDOW_H
#define ADDRESSBOOKWINDOW_H


#include <iostream>
#include <qlist.h>
#include <string>
#include <memory>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>
#include <QFile>
#include <QtWidgets/QMenu>
#include <QThread>

#include "CommunicatorClient.h"
#include "global.h"
#include "ChatMessage.h"
#include "PersonManager.h"
#include "ConnectPool.h"
#include "ServerConfigManager.h"
#include "ui_addressbookwindow.h"
#include "FriendListItem.h"
#include "AddFriendGroup.h"

QT_BEGIN_NAMESPACE
namespace Ui {class AddressBookWindow;}
QT_END_NAMESPACE
class AddressBookWindow : public QWidget {
    Q_OBJECT
public:
    AddressBookWindow(QWidget* parent = nullptr);
private:
    void initAddressBookList();
    void showContextMenu(const QPoint &point);
private slots:
    void showFindWindow();
    void showFriendInform();
    
    // void addFriend();
    // void deleteFriend();
private:
    std::shared_ptr<Ui::AddressBookWindow> ui_;
    FindWindow* find_window_;
    std::shared_ptr<ClientCommunicator> clientcommunicator_;
};
#endif // ADDRESSBOOKWINDOW_H