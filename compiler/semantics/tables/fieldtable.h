//
// Created by T0mmy on 27.11.2023.
//

#ifndef COMPILER_FIELDTABLE_H
#define COMPILER_FIELDTABLE_H

#pragma once
#include "semantics/tools/datatype.h"
#include <map>
#include <iostream>

using namespace std;

class  ExprNode;
class FieldTableItem {
public:
    DataType dataType;
    bool isConst = false;
    bool isInit = false;
    bool isPub = false;
    ExprNode *value; // хз  надо ли

    FieldTableItem();
    FieldTableItem(DataType dataType, bool  isConst);
    FieldTableItem(DataType dataType, bool  isConst, ExprNode *value);
    string toString();
};


class FieldTable {
public:
    map<string, FieldTableItem> items; // ключ - имя, значение понятно
    string toString();
};


#endif //COMPILER_FIELDTABLE_H
