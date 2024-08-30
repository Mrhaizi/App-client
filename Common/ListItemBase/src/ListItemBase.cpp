#include "ListItemBase.h"


ListItemBase::ListItemBase(QWidget *parent) {

    
}

void ListItemBase::setItemType(const ListItemType &type) {
    type_ = type;
}