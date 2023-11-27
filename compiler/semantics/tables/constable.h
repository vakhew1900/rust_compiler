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
        CLASS = 7,
        FIELD_REF = 9,
        METHOD_REF = 10,
        INTERFACE_METHOD_REF = 11,
        STRING = 8,
        INTEGER = 3,
        FLOAT = 4,
        LONG = 5,
        DOUBLE = 6,
        NAME_AND_TYPE = 12,
        UTF8 = 1,
        METHOD_HANDLE = 15,
        METHOD_TYPE = 16,
        INVOKE_DYNAMIC = 18,
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
};


class ConstTable {
public:
    std::vector<ConstTableItem> items;
};


#endif //COMPILER_CONSTTABLE_H
