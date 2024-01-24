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
    vector<string> methodName = {"print", "print_int", "print_float", "print_char", "print_bool", "println", "println_int", "println_float", "println_char", "println_bool"};
    DataType returnDataType = DataType(DataType::void_);
    vector<DataType> params = {DataType(DataType::string_), DataType(DataType::int_), DataType(DataType::float_),
                                    DataType(DataType::char_), DataType(DataType::bool_), DataType(DataType::string_), DataType(DataType::int_), DataType(DataType::float_),
                               DataType(DataType::char_), DataType(DataType::bool_)};


    for (int i = 0; i < methodName.size(); i++) {
        MethodTableItem methodTableItem = MethodTableItem();
        methodTableItem.isPub = true;
        methodTableItem.isHasBody = true;
        methodTableItem.isStatic = true;
        methodTableItem.returnDataType = returnDataType;

        VarTableItem varTableItem = VarTableItem("str", DataType(DataType::string_), false, true, false, true);
        methodTableItem.paramTable.items.push_back(varTableItem);
        varTableItem = VarTableItem("val",params[i] , false, params[i].type == DataType::string_ , false, false);
        methodTableItem.paramTable.items.push_back(varTableItem);

        methodTableItem.isRTL = true;
        rtlClass.methodTable.items[methodName[i]] = methodTableItem;
    }
}

RTLContainer::RTLContainer() {
    addReadFunctions();
    addPrintFunctions();
    addStringFunctions();
    addCharAt();
    rtlClass.isPub = true;
    ClassTable::Instance()->addClass(ClassTable::RTLClassName, rtlClass);
}

void RTLContainer::addStringFunctions() {

    vector<string> methodName = {"push_char", "push_str"};
    DataType returnDataType = DataType(DataType::string_);
    vector<DataType> params = {DataType(DataType::char_), DataType(DataType::string_)};


    for (int i = 0; i < methodName.size(); i++) {
        MethodTableItem methodTableItem = MethodTableItem();
        methodTableItem.isPub = true;
        methodTableItem.isHasBody = true;
        methodTableItem.isStatic = true;
        methodTableItem.returnDataType = returnDataType;

        VarTableItem varTableItem = VarTableItem("str", DataType(DataType::string_), false, true, false, false);
        methodTableItem.paramTable.items.push_back(varTableItem);
        varTableItem = VarTableItem("val",params[i] , false, params[i].type == DataType::string_ , false, false);
        methodTableItem.paramTable.items.push_back(varTableItem);

        methodTableItem.isRTL = true;
        rtlClass.methodTable.items[methodName[i]] = methodTableItem;
    }

}

void RTLContainer::addCharAt() {

    string methodName = "charAt";
    DataType returnDataType = DataType(DataType::char_);
    DataType param = DataType(DataType::int_);

    MethodTableItem methodTableItem = MethodTableItem();
    methodTableItem.isPub = true;
    methodTableItem.isHasBody = true;
    methodTableItem.isStatic = true;
    methodTableItem.returnDataType = returnDataType;

    VarTableItem varTableItem = VarTableItem("str", DataType(DataType::string_), false, true, false, false);
    methodTableItem.paramTable.items.push_back(varTableItem);
    varTableItem = VarTableItem("val", param , false, param.isString(), false, false);
    methodTableItem.paramTable.items.push_back(varTableItem);

    methodTableItem.isRTL = true;
    rtlClass.methodTable.items[methodName] = methodTableItem;
}
