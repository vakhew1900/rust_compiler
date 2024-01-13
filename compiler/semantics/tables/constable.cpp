//
// Created by T0mmy on 28.11.2023.
//

#include <string>
#include "constable.h"
#include "semantics/tools/tools.h"
#include "code_generation/tools/byte_convert.h"


ConstTableItem::ConstTableItem(ConstTableItem::ConstTableType constTableType, string utf8) {
    this->constTableType = constTableType;
    this->utf8 = utf8;
}

ConstTableItem::ConstTableItem(ConstTableItem::ConstTableType constTableType, int val1) {
    this->constTableType = constTableType;
    this->val1 = val1;
}

ConstTableItem::ConstTableItem(ConstTableItem::ConstTableType constTableType, int val1, int val2) {
    this->constTableType = constTableType;
    this->val1 = val1;
    this->val2 = val2;
}

ConstTableItem::ConstTableItem(ConstTableItem::ConstTableType constTableType, double floatVal) {
    this->constTableType = constTableType;
    this->floatVal = floatVal;
}

string ConstTableItem::toString(int index) {

    string row = to_string(index) + ", ";

    switch (constTableType) {
        case CONSTANT_UTF8:
            row += varName(CONSTANT_UTF8);
            row += ", " + utf8;
            break;
        case CONSTANT_CLASS:
            row += varName(CONSTANT_CLASS);
            row += ", " + to_string(val1);
            break;
        case CONSTANT_STRING:
            row += varName(CONSTANT_STRING);
            row += ", " + to_string(val1);
            break;
        case CONSTANT_FIELD_REF:
            row += varName(CONSTANT_FIELD_REF);
            row += ", " + to_string(val1) + " " + to_string(val2);
            break;
        case CONSTANT_INTEGER:
            row += varName(CONSTANT_INTEGER);
            row += ", " + to_string(val1);
            break;
        case CONSTANT_METHOD_REF:
            row += varName(CONSTANT_METHOD_REF);
            row += ", " + to_string(val1) + " " + to_string(val2);
            break;
        case CONSTANT_DOUBLE:
            row += varName(CONSTANT_DOUBLE);
            row += ", " + to_string(floatVal);
            break;
        case CONSTANT_NAME_AND_TYPE:
            row += varName(CONSTANT_NAME_AND_TYPE);
            row += ", " + to_string(val1) + " " + to_string(val2);
            break;

        case CONSTANT_FLOAT:
        case CONSTANT_LONG:
        case CONSTANT_METHOD_HANDLE:
        case CONSTANT_METHOD_TYPE:
        case CONSTANT_INVOKE_DYNAMIC:
        case CONSTANT_INTERFACE_METHOD_REF:
            break;

    }

    row += "\n";
    return row;
}

vector<char> ConstTableItem::toBytes() {

    vector<char> bytes;
    std::vector<char> buffer;

    switch(this->constTableType){

        case CONSTANT_INTEGER:
            bytes.push_back((char) ConstTableItem::CONSTANT_INTEGER);
            buffer = IntToBytes(val1);
            bytes.insert(bytes.end(), all(buffer));
            break;

        case CONSTANT_DOUBLE:
            bytes.push_back((char) ConstTableItem::CONSTANT_DOUBLE);
            buffer = DoubleToBytes(this->floatVal);
            bytes.insert(bytes.end(), all(buffer));
            break;

        case CONSTANT_CLASS:
            bytes.push_back((char) ConstTableItem::CONSTANT_CLASS);
            buffer = IntToBytes(this->val1);
            bytes.insert(bytes.end(), u2(buffer));
            break;

        case CONSTANT_FIELD_REF:
            bytes.push_back((char) ConstTableItem::CONSTANT_FIELD_REF);

            buffer = IntToBytes(this->val1);
            bytes.insert(bytes.end(), u2(buffer));

            buffer = IntToBytes(this->val2);
            bytes.insert(bytes.end(), u2(buffer));
            break;

        case CONSTANT_METHOD_REF:
            bytes.push_back((char) ConstTableItem::CONSTANT_METHOD_REF);

            buffer = IntToBytes(this->val1);
            bytes.insert(bytes.end(), u2(buffer));

            buffer = IntToBytes(this->val2);
            bytes.insert(bytes.end(), u2(buffer));
            break;

        case CONSTANT_STRING:
            bytes.push_back((char) ConstTableItem::CONSTANT_STRING);
            buffer = IntToBytes(this->val1);
            bytes.insert(bytes.end(), u2(buffer));
            break;

        case CONSTANT_NAME_AND_TYPE:
            bytes.push_back((char) ConstTableItem::CONSTANT_NAME_AND_TYPE);

            buffer = IntToBytes(this->val1);
            bytes.insert(bytes.end(), u2(buffer));

            buffer = IntToBytes(this->val2);
            bytes.insert(bytes.end(), u2(buffer));
            break;

        case CONSTANT_UTF8:
        {
            bytes.push_back((char) ConstTableItem::CONSTANT_UTF8);

            char const *str =  ConstTable::formatClassName(utf8).c_str();
            buffer = IntToBytes(strlen(str));
            bytes.insert(bytes.end(), u2(buffer));
            bytes.insert(bytes.end(), str, str + strlen(str));
        }
            break;

        case CONSTANT_METHOD_HANDLE:
        case CONSTANT_METHOD_TYPE:
        case CONSTANT_INVOKE_DYNAMIC:
        case CONSTANT_LONG:
        case CONSTANT_FLOAT:
        case CONSTANT_INTERFACE_METHOD_REF:
            break;
    }

    return bytes;
}

string ConstTable::toCSV() {

    string csv = "Const №, Const Type, Const Value\n";
    int index = 0;
    for (auto item: items) {
        if(index) {
            csv += item.toString(index);
        }
        index++;
    }

    return csv;
}

string ConstTable::toString() {
    return toCSV();
}

int ConstTable::Class(const string &className) {

    int utf8Val = UTF8(className);
    int res = Val(ConstTableItem::CONSTANT_CLASS, utf8Val);

    if(res <= 0){
        ConstTableItem item = ConstTableItem(ConstTableItem::CONSTANT_CLASS, utf8Val);
        res = this->add(item);
    }
    return res;
}

int ConstTable::Int(int val) {

    for (int i = 0; i < this->items.size(); i++) {
        if (items[i].constTableType == ConstTableItem::CONSTANT_INTEGER && items[i].val1 == val) {
            return i;
        }
    }

    ConstTableItem constTableItem = ConstTableItem(ConstTableItem::CONSTANT_INTEGER, val);
    return add(constTableItem);
}

int ConstTable::Double(double val) {

    for (int i = 0; i < this->items.size(); i++) {
        if (items[i].constTableType == ConstTableItem::CONSTANT_DOUBLE && items[i].floatVal == val) {
            return i;
        }
    }
    ConstTableItem constTableItem = ConstTableItem(ConstTableItem::CONSTANT_DOUBLE, val);
    return add(constTableItem);
}

int ConstTable::String(const string &str) {

    int utf8Val = UTF8(str);
    if(utf8Val <= 0){
        ConstTableItem constTableItem = ConstTableItem(ConstTableItem::CONSTANT_UTF8, str);
        utf8Val = add(constTableItem);
    }

    int res = Val(ConstTableItem::CONSTANT_STRING, utf8Val);

    if(res <= 0) {
        ConstTableItem constTableItem = ConstTableItem(ConstTableItem::CONSTANT_STRING, utf8Val);
        res = add(constTableItem);
    }
    return res;
}

int ConstTable::UTF8(const string &str) {

    for (int i = 1; i < this->items.size(); i++) {
        if (items[i].constTableType == ConstTableItem::CONSTANT_UTF8 && items[i].utf8 == str) {
            return i;
        }
    }

    return  add(ConstTableItem(ConstTableItem::CONSTANT_UTF8, str));
}

int ConstTable::Val(ConstTableItem::ConstTableType constTableType, int val) {

    for (int i = 0; i < this->items.size(); i++) {
        if (items[i].constTableType == constTableType && items[i].val1 == val) {
            return i;
        }
    }
    return -1;
}

int ConstTable::add(ConstTableItem constTableItem) {

    this->items.push_back(constTableItem);
    int res = items.size() - 1;
    return res;
}

string ConstTable::MethodParam(const vector<DataType> &params, const DataType &returnType) {

    string res = "(";

    for (int i = 0; i < params.size(); i++)
        res += params[i].toConstTableFormat();


    res += ")";
    res += returnType.toConstTableFormat();

    return res;
}

int ConstTable::Method(const string &method, const vector<DataType> &params, const DataType &returnType) {

    int name = UTF8(method);
    int type = UTF8(MethodParam(params, returnType));
    int res = Val(ConstTableItem::CONSTANT_NAME_AND_TYPE, name, type);

    if(res <= 0){
        ConstTableItem constTableItem = ConstTableItem(ConstTableItem::CONSTANT_NAME_AND_TYPE, name, type);
        res = add(constTableItem);
    }
    return res;
}

int ConstTable::Val(ConstTableItem::ConstTableType constTableType, int val1, int val2) {

    for (int i = 0; i < this->items.size(); i++) {
        if (items[i].constTableType == constTableType && items[i].val1 == val1 && items[i].val2 == val2) {
            return i;
        }
    }
    return -1;
}

int ConstTable::Field(const string &field, const DataType &dataType) {

    int name = UTF8(field);
    int type = UTF8(dataType.toConstTableFormat());
    int res = Val(ConstTableItem::CONSTANT_NAME_AND_TYPE, name, type);

    if(res <= 0){
        ConstTableItem constTableItem = ConstTableItem(ConstTableItem::CONSTANT_NAME_AND_TYPE, name, type);
        res = add(constTableItem);
    }
    return res;
}

int ConstTable::FieldRef(const string &className, const string &field, const DataType &dataType) {

    int classRef = Class(className);
    int fieldRef = Field(field, dataType);
    int res = Val(ConstTableItem::CONSTANT_FIELD_REF, classRef, fieldRef);

    if(res <= 0){
        ConstTableItem constTableItem = ConstTableItem(ConstTableItem::CONSTANT_FIELD_REF, classRef, fieldRef);
        res = add(constTableItem);
    }

    return res;
}

int ConstTable::MethodRef(const string &className, const string &method, const vector<DataType> &params,
                          const DataType &returnType) {

    int classRef = Class(className);
    int methodRef = Method(method,params, returnType);
    int res = Val(ConstTableItem::CONSTANT_METHOD_REF, classRef, methodRef);

    if(res <= 0){
        ConstTableItem constTableItem = ConstTableItem(ConstTableItem::CONSTANT_METHOD_REF, classRef, methodRef);
        res = add(constTableItem);
    }

    return res;
}

ConstTable::ConstTable() {

        ConstTableItem item = ConstTableItem(ConstTableItem::CONSTANT_UTF8, "java/lang/Object");
        items.push_back(item);
        item = ConstTableItem(ConstTableItem::CONSTANT_UTF8, "Code");
        this->MethodRef("java/lang/Object", "<init>", vector<DataType>(), DataType(DataType::void_));
        items.push_back(item);
}

vector<char> ConstTable::toBytes() {
    vector<char> bytes;
    int cnt = 0;
    for(auto& constant : this->items){
        if (cnt) {
            vector<char> buffer = constant.toBytes();
            bytes.insert(bytes.end(), all(buffer));
        }
        cnt++;
    }

    return bytes;
}


string ConstTable::formatClassName(const string&  className){
    if(className == ConstTable::RTLClassName) {
        return RTLClassName;
    }
    else {
        int size = ConstTable::globalClassName.size() + 1;
        return className.substr(size);
    }
}

