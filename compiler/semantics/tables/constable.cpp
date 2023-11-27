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
        case UTF8:
            row += varName(UTF8);
            row += ", " + utf8;
            break;
        case CLASS:
            row += varName(CLASS);
            row += ", " + to_string(val1);
            break;
        case STRING:
            row += varName(STRING);
            row += ", " + to_string(val1);
            break;
        case FIELD_REF:
            row += varName(FIELD_REF);
            row += ", " + to_string(val1) + " " + to_string(val2);
            break;
        case INTEGER:
            row += varName(INTEGER);
            row += ", " + to_string(val1);
            break;
        case METHOD_REF:
            row += varName(METHOD_REF);
            row += ", " + to_string(val1) + " " + to_string(val2);
            break;
        case DOUBLE:
            row += varName(DOUBLE);
            row += ", " + to_string(floatVal);
            break;
        case NAME_AND_TYPE:
            row += varName(NAME_AND_TYPE);
            row += ", " + to_string(val1) + to_string(val2);
            break;

        case FLOAT:
        case LONG:
        case METHOD_HANDLE:
        case METHOD_TYPE:
        case INVOKE_DYNAMIC:
        case INTERFACE_METHOD_REF:
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
