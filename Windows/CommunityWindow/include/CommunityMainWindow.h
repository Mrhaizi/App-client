#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <qtmetamacros.h>
#include <qwidget.h>

#include "ui_community.h"

QT_BEGIN_NAMESPACE
namespace Ui {class Community;};
QT_END_NAMESPACE


class CommunityMainWindow : public QWidget {
    Q_OBJECT
public:
    CommunityMainWindow(QWidget* parent);
private:
    std::shared_ptr<Ui::Community> ui_;
};
#endif // MAINWINDOW_H