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

string FieldTableItem::toString() {
    string res = "";

    if(isConst)
    {
        res += "const ";
    }

    if (isPub)
    {
        res += "public ";
    }
    else
    {
        res += "package ";
    }


    res += dataType.toString();

    return res;
}

bool FieldTableItem::isEquals(const FieldTableItem &fieldTableItem) {
    bool res = this->isConst == fieldTableItem.isConst;
    res = res && this->isPub == fieldTableItem.isPub;
    res = res && this->isInit == fieldTableItem.isInit;
    res = res && this->dataType.isEquals(fieldTableItem.dataType);
    return res;
}

string FieldTable::toString() {
    string res = "";

    for(auto elem: items)
    {
        string tmp = elem.first + ":" + elem.second.toString() + "\n";
        res += tmp;
    }

    return res;
}
