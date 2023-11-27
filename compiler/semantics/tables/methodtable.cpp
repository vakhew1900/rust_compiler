//
// Created by T0mmy on 27.11.2023.
//

#include "methodtable.h"

MethodTableItem::MethodTableItem(const VarTable &paramTable) : paramTable(paramTable) {}

MethodTableItem::MethodTableItem() {

}

MethodTableItem::MethodTableItem(DataType returnDataType, VarTable paramTable, VarTable localVarTable, bool isStatic) {
    this->returnDataType = returnDataType;
    this->paramTable = paramTable;
    this->localVarTable = localVarTable;
    this->isStatic = isStatic;
}

