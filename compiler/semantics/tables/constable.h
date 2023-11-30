//
// Created by T0mmy on 28.11.2023.
//

#ifndef COMPILER_CONSTTABLE_H
#define COMPILER_CONSTTABLE_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class ConstTableItem {
public:
    enum ConstTableType {
        CONSTANT_CLASS = 7,
        CONSTANT_FIELD_REF = 9,
        CONSTANT_METHOD_REF = 10,
        CONSTANT_INTERFACE_METHOD_REF = 11,
        CONSTANT_STRING = 8,
        CONSTANT_INTEGER = 3,
        CONSTANT_FLOAT = 4,
        CONSTANT_LONG = 5,
        CONSTANT_DOUBLE = 6,
        CONSTANT_NAME_AND_TYPE = 12,
        CONSTANT_UTF8 = 1,
        CONSTANT_METHOD_HANDLE = 15,
        CONSTANT_METHOD_TYPE = 16,
        CONSTANT_INVOKE_DYNAMIC = 18,
    };

    ConstTableType constTableType;
    string utf8;
    double floatVal = -1;
    int val1 = -1, val2 = -1;

    ConstTableItem();
    ConstTableItem(ConstTableType constTableType, string utf8);
    ConstTableItem(ConstTableType constTableType, int val1);
    ConstTableItem(ConstTableType constTableType, int val1, int val2);
    ConstTableItem(ConstTableType constTableType, double  floatVal);
    string toString(int index);
};


class ConstTable {
public:
    std::vector<ConstTableItem> items;

    string toString();
    string toCSV();
};


#endif //COMPILER_CONSTTABLE_H
