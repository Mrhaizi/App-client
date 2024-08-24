#ifndef LISTITEMBASE_H
#define LISTITEMBASE_H

#include <iostream>
#include <QObject>
#include <QtWidgets/QWidget>
#include "global.h"

class ListItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit ListItemBase(QWidget *parent = nullptr);
    void setItemType(const ListItemType &type);
private:
    ListItemType type_;
signals:

};
#endif