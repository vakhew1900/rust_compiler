//
// Created by T0mmy on 28.11.2023.
//

#ifndef COMPILER_CONSTTABLE_H
#define COMPILER_CONSTTABLE_H

#include <iostream>
#include <map>
#include <vector>
#include "semantics/tools/datatype.h"
#include "code_generation/tools/utils.h"

using namespace std;

class ConstTableItem {
public:
    enum ConstTableType : uint8_t {
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
    float floatVal = -1;
    int val1 = -1, val2 = -1;

    ConstTableItem();

    ConstTableItem(ConstTableType constTableType, string utf8);

    ConstTableItem(ConstTableType constTableType, int val1);

    ConstTableItem(ConstTableType constTableType, int val1, int val2);

    ConstTableItem(ConstTableType constTableType, float floatVal);

    string toString(int index);

    vector<char> toBytes();
};


class ConstTable {
public:
    std::vector<ConstTableItem> items;

    string toString();

    string toCSV();

    int Class(const string &className);

    int Int(int val);

    int Float(float val);

    int String(const string &str);

    int UTF8(const string &str);

    int Val(ConstTableItem::ConstTableType constTableType, int val);

    int Val(ConstTableItem::ConstTableType constTableType, int val1, int val2);

    int Method(const string &method, const vector<DataType> &params, const DataType &returnType);

    int Field(const string &field, const DataType &dataType);

    int MethodRef(const string &className, const string &method, const vector<DataType> &params,
                  const DataType &returnType);

    int FieldRef(const string &className, const string &field, const DataType &dataType);

    int add(ConstTableItem constTableItem);

    static string MethodParam(const vector<DataType> &params, const DataType &returnType);

    ConstTable();

    vector<char> toBytes();
    static string formatClassName(const string& className);

    inline static const string moduleClassName = "ModuleClass";
    inline static const string globalClassName = "src";
    inline static const string RTLClassName = "RTL";
    inline static const string init = "<init>";
    inline static const string clinit = "<clinit>";
    inline static const string objectClassName = "java/lang/Object";
    inline static const string stringClassName = "java/lang/String";
};


#endif //COMPILER_CONSTTABLE_H
