//
// Created by T0mmy on 04.01.2024.
//

#include "RTLContainer.h"

void RTLContainer::addReadFunctions() {
    vector<string> methodName = {"read", "read_int", "read_float", "read_char", "read_bool"};
    vector<DataType> returnTypes = {DataType(DataType::string_), DataType(DataType::int_), DataType(DataType::float_),
                                    DataType(DataType::char_), DataType(DataType::bool_)};

    for (int i = 0; i < methodName.size(); i++) {
        MethodTableItem methodTableItem = MethodTableItem();
        methodTableItem.isPub = true;
        methodTableItem.isHasBody = true;
        methodTableItem.isStatic = true;
        methodTableItem.returnDataType = returnTypes[i];
        methodTableItem.isRTL = true;
        rtlClass.methodTable.items[methodName[i]] = methodTableItem;
    }
}

void RTLContainer::addPrintFunctions() {
    vector<string> methodName = {"println", "println_int", "println_float", "println_char", "println_bool"};
    DataType returnDataType = DataType(DataType::void_);
    vector<DataType> params = {DataType(DataType::string_), DataType(DataType::int_), DataType(DataType::float_),
                                    DataType(DataType::char_), DataType(DataType::bool_)};


    for (int i = 0; i < methodName.size(); i++) {
        MethodTableItem methodTableItem = MethodTableItem();
        methodTableItem.isPub = true;
        methodTableItem.isHasBody = true;
        methodTableItem.isStatic = true;
        methodTableItem.returnDataType = returnDataType;

        VarTableItem varTableItem = VarTableItem("str", DataType(DataType::string_), false, true, false, false);
        methodTableItem.paramTable.items.push_back(varTableItem);
        varTableItem = VarTableItem("val",params[i] , false, true, false, false);
        methodTableItem.paramTable.items.push_back(varTableItem);

        methodTableItem.isRTL = true;
        rtlClass.methodTable.items[methodName[i]] = methodTableItem;
    }
}

RTLContainer::RTLContainer() {
    addReadFunctions();
    addPrintFunctions();
    rtlClass.isPub = true;
    ClassTable::Instance()->addClass(ClassTable::RTLClassName, rtlClass);
}
