#ifndef CHATWINIDOW_H
#define CHATWINIDOW_H

#include <iostream>
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

#include "ui_friendwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {class FriendWindow;}
QT_END_NAMESPACE

class FriendWindow : public QWidget {
    Q_OBJECT
public:
    FriendWindow(QWidget *parent = nullptr);
    ~FriendWindow() = default;

    void updateChatWindow();
    

private:
    std::shared_ptr<Ui::FriendWindow> ui_;
};

#endif // CHATWINIDOW_H