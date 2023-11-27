//
// Created by T0mmy on 27.11.2023.
//

#include "vartable.h"

VarTableItem::VarTableItem() {

}

VarTableItem::VarTableItem(DataType dataType, bool isMut, bool isRef, bool isInit) {
        this->dataType = dataType;
        this->isMut = isMut;
        this->isInit = isInit;
        this->isRef = isRef;
}

VarTableItem::VarTableItem(DataType dataType, bool isMut, bool isRef, bool isInit, ExprNode *blockExpr) {
    this->dataType = dataType;
    this->isMut = isMut;
    this->isInit = isInit;
    this->isRef = isRef;
    this->blockExpr = blockExpr;
}
