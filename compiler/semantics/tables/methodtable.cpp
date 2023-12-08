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

string MethodTableItem::toString() {
    string res = "";
    if(isStatic)
    {
        res += " - static ";
    }

    if (isPub)
    {
        res += "public ";
    }
    else
    {
        res += "package ";
    }

    res += "returnType: " + returnDataType.toString() + "\n";
    res += "paramTable: \n" + paramTable.toString() + "localVarTable\n" + localVarTable.toString() + "\n";

    return res;
}

string MethodTable::toString() {
    string res = "";

    for(auto elem : items)
    {
        string tmp = elem.first + elem.second.toString();
        res += tmp;
    }

    return res;
}
