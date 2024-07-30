#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <iostream>
#include <memory>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>
#include <QFile>

#include "ui_homewindow.h"
#include "ui_chatpage.h"

QT_BEGIN_NAMESPACE
namespace Ui {class homewindow;}
QT_END_NAMESPACE  

class HomeWindow : public QWidget {
    Q_OBJECT
public:
    HomeWindow(QWidget *parent);
    ~HomeWindow() = default;
public:
    std::shared_ptr<Ui::homewindow>  ui_;
};

#endif // HOMEWINDOW_H