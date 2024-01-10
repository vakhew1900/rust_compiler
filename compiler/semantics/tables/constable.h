//
// Created by T0mmy on 28.11.2023.
//

#ifndef COMPILER_CONSTTABLE_H
#define COMPILER_CONSTTABLE_H

#include <iostream>
#include <map>
#include <vector>
#include "semantics/tools/datatype.h"

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
    vector<char> toBytes();
};


class ConstTable {
public:
    std::vector<ConstTableItem> items;

    string toString();
    string toCSV();
    int Class(const string& className);
    int Int(int val);
    int Double(double val);
    int String(const string& str);
    int UTF8(const string& str);
    int Val(ConstTableItem::ConstTableType constTableType, int val);
    int Val(ConstTableItem::ConstTableType constTableType, int val1, int val2);
    string MethodParam(const vector<DataType> &params, const DataType &returnType);
    int Method(const string& method, const vector<DataType> &params,const DataType &returnType);
    int Field(const string& field, const DataType& dataType);
    int MethodRef(const string& className, const string& method, const vector<DataType> &params,const DataType &returnType);
    int FieldRef(const string& className, const string& field, const DataType& dataType);
    int add(ConstTableItem constTableItem);
    ConstTable();
    vector<char> toBytes();
};


#endif //COMPILER_CONSTTABLE_H
