//
// Created by T0mmy on 28.11.2023.
//

#include <string>
#include "constable.h"
#include "semantics/tools/tools.h"

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

    switch(constTableType)
    {
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
            row += ", " + to_string(val1) + to_string(val2);
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

string ConstTable::toCSV() {

    string csv = "Const №, Const Type, Const Value\n";
    int index = 0;
    for (auto item: items) {
        csv += item.toString(index++);
    }

    return csv;
}

string ConstTable::toString() {
    return toCSV();
}
