//
// Created by T0mmy on 27.11.2023.
//

#include <string>
#include "vartable.h"

VarTableItem::VarTableItem() {

}


VarTableItem::VarTableItem(string name, DataType dataType, bool isMut, bool isRef, bool isInit, bool isConst) {
        this->id = name;
        this->dataType = dataType;
        this->isMut = isMut;
        this->isInit = isInit;
        this->isRef = isRef;
        this->isConst = isConst;
}

VarTableItem::VarTableItem(string name, DataType dataType, bool isMut, bool isRef, bool isInit, bool isConst, ExprNode *blockExpr) {
    this->id = name;
    this->dataType = dataType;
    this->isMut = isMut;
    this->isInit = isInit;
    this->isRef = isRef;
    this->blockExpr = blockExpr;
    this->isConst = isConst;
}

VarTableItem::VarTableItem(string name, DataType dataType, bool isMut, bool isRef, bool isInit, bool isConst, ExprNode *blockExpr, ExprNode *value) {
    this->id = name;
    this->dataType = dataType;
    this->isMut = isMut;
    this->isInit = isInit;
    this->isRef = isRef;
    this->isConst = isConst;
    this->blockExpr = blockExpr;
    this->value = value;
}

string VarTableItem::toString() {
    string res = "";

    res = this->id;
    if(isRef)
    {
        res += "&";
    }

    if(isMut)
    {
        res += "mut";
    }

    if(isConst){
        res += "const";
    }

    res += " " + dataType.toString();

    return res;
}


string VarTable::toString() {

    string res = "";

    for(int i = 0; i < res.size(); i++)
    {
        res += to_string(i) + ": " + items[i].toString() + "\n";
    }

    return res;
}
