//
// Created by T0mmy on 27.11.2023.
//

#ifndef COMPILER_METHODTABLE_H
#define COMPILER_METHODTABLE_H


#include "semantics/tools/datatype.h"
#include "vartable.h"
#include <map>

using namespace std;

class MethodTableItem {
public:
    explicit MethodTableItem(const VarTable &paramTable);

public:
    DataType returnDataType;
    VarTable paramTable;
    VarTable localVarTable;
    bool isStatic = true; // статический или не статический метод
    bool isHasBody = false;
    bool isPub = false;
    bool isRefSelf = false;
    bool isRTL = false;
    ExprNode* body;

    MethodTableItem();
    MethodTableItem(DataType returnDataType, VarTable paramTable,VarTable localVarTable, bool isStatic = true);
    string toString();
    bool isEqualsDeclaration(const MethodTableItem& other);
};


class MethodTable{
public:
    map<string, MethodTableItem> items; // название класса
    string toString();
};


#endif //COMPILER_METHODTABLE_H
