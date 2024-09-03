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
#include <QString>

#include "ui_friendlistitem.h"
#include "ListItemBase.h"

QT_BEGIN_NAMESPACE
namespace Ui {class FriendListItemWindow;} 
QT_END_NAMESPACE

class FriendListItemWindow : public ListItemBase {
    Q_OBJECT
public:
    FriendListItemWindow(const QString image_path, const QString &name, QWidget *parent = nullptr);
    QSize sizeHint() const override {
        return QSize(200, 100);

    };
    QString getName();
private:
    std::shared_ptr<Ui::FriendListItemWindow> ui_;
};

#endif // FRIENDLISTITEMWINIDOW_H

