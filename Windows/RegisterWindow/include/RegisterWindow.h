#ifndef REGISTERUI_H
#define REGISTERUI_H

#include <iostream>
#include <memory>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>

#include "PersonManager.h"
#include "ui_register.h"
// #include "LogInUi.h"

QT_BEGIN_NAMESPACE 
namespace Ui {class RegisterWindow;}
QT_END_NAMESPACE

class RegisterWindow : public QWidget {
    Q_OBJECT
public:
    RegisterWindow(QWidget *parent, std::shared_ptr<PersonManager> personmanager = nullptr);
    ~RegisterWindow() = default;
private slots:
    void registerUserInfo();
    // void backLoginWindow();
private:
    std::shared_ptr<PersonManager> infomanager_;
    std::shared_ptr<Ui::RegisterWindow> ui_;
};


#endif // REGISTERUI_H
