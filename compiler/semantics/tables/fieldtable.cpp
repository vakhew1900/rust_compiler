//
// Created by T0mmy on 27.11.2023.
//

#include "fieldtable.h"

FieldTableItem::FieldTableItem() {
}

FieldTableItem::FieldTableItem(DataType dataType, bool isConst) {
    this->dataType = dataType;
    this->isConst = isConst;
}

FieldTableItem::FieldTableItem(DataType dataType, bool isConst, ExprNode *value) {
    this->dataType = dataType;
    this->isConst = isConst;
    this->value = value;
}
