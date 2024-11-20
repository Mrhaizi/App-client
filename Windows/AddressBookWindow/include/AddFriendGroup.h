#ifndef ADDFRIENDGROUP_H
#define ADDFRIENDGROUP_H

#include <QtGui/qwindowdefs.h>
#include <QtWidgets/qwidget.h>
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
#include "FriendListItem.h"
#include "ui_findfriend.h"

QT_BEGIN_NAMESPACE
namespace Ui {class FindWindow;}
QT_END_NAMESPACE
class FindWindow : public QWidget {
    Q_OBJECT
public:
    FindWindow(QWidget* parent = nullptr, std::shared_ptr<ClientCommunicator> clientcommunicator = nullptr);
private slots:
    void performSearch();
private:
   std::shared_ptr<Ui::FindWindow> ui_;
   std::shared_ptr<ClientCommunicator> clientcommunicator_;
};
#endif // ADDFRIENDGROUP_H