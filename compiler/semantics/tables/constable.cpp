//
// Created by T0mmy on 28.11.2023.
//

#include "constable.h"

ConstTableItem::ConstTableItem(ConstTableItem::ConstTableType constTableType, string utf8) {
    this->constTableType = constTableType;
    this->utf8 = utf8;
}

ConstTableItem::ConstTableItem(ConstTableItem::ConstTableType constTableType, int val1) {
    this->constTableType = constTableType;
    this->val1 = val1;
}

ConstTableItem::ConstTableItem(ConstTableItem::ConstTableType constTableType, int val1, int val2) {
    this->constTableType = constTableType;
    this->val1 = val1;
    this->val2 = val2;
}

ConstTableItem::ConstTableItem(ConstTableItem::ConstTableType constTableType, double floatVal) {
    this->constTableType = constTableType;
    this->floatVal = floatVal;
}
