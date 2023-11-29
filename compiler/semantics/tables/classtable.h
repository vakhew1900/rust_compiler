//
// Created by T0mmy on 28.11.2023.
//

#ifndef COMPILER_CLASSTABLE_H
#define COMPILER_CLASSTABLE_H


#include "methodtable.h"
#include "fieldtable.h"
#include "constable.h"
#include <map>

using namespace std;

class ClassTableItem{
public:
    enum Type{
        struct_, enum_, trait_, mod_ // не факт что правильно
    };

    Type classType;
    string name;
    MethodTable methodTable;
    FieldTable fieldTable;
    string parentName; // имя родителя

    ConstTable constTable;

    ClassTableItem();
    ClassTableItem(FieldTable fieldTable, MethodTable methodTable, string parentName = "");
    string toString();
};

class ClassTable {
public:
    map<string, ClassTableItem> items;
    string toString();
};


#endif //COMPILER_CLASSTABLE_H
