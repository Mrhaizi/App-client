#ifndef FRIENDLISTITEMWINDOW_H
#define FRIENDLISTITEMWINDOW_H

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

#include "ui_friendlistitem.h"

QT_BEGIN_NAMESPACE
namespace Ui {class FriendListItemWindow;} 
QT_END_NAMESPACE

class FriendListItemWindow : public QWidget {
    Q_OBJECT
public:
    FriendListItemWindow(const QString image_path, const QString &name, QWidget *parent = nullptr);
private:
    QLabel *image_label;
    QLabel *name_label;
    std::shared_ptr<Ui::FriendListItemWindow> ui_;
};

#endif // FRIENDLISTITEMWINIDOW_H

