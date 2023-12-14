//
// Created by T0mmy on 27.11.2023.
//

#include <string>
#include "datatype.h"
#include "tools.h"

DataType::DataType(DataType::Type type) {
    this->type = type;
}

DataType DataType::ArrayDataType(DataType::Type arrType, int arrDeep) {
    DataType dataType = DataType(array_);
    dataType.arrType = arrType;
    dataType.arrDeep = arrDeep; //
    if (arrDeep < 0) {
        cout << "array deep incorrect";
    }
    return dataType;
}

DataType DataType::ArrayDataType(DataType::Type arrType, int arrDeep, vector<int> arrLength) {

    DataType dataType = ArrayDataType(arrType, arrDeep);
    dataType.arrLength = arrLength;
    return dataType;
}

DataType DataType::StructDataType(vector<string> structPath) {
    DataType dataType = DataType(class_);
    dataType.structPath = structPath;
    return dataType;
}

DataType::DataType() {
    this->type = undefined_;
}

string DataType::toString() {
    string res ="";

    switch (type) {

        case void_:
            res += varName(void_);
            break;
        case int_:
            res += varName(int_);
            break;
        case float_:
            res += varName(float_);
            break;
        case char_:
            res += varName(char_);
            break;
        case bool_:
            res += varName(bool_);
            break;
        case string_:
            res += varName(string_);
            break;
        case class_:
            res += varName(class_);
            res += " name " + id;
            break;
        case array_:
            res += "array_ " + TypeToString(this->arrType) + " " + id;
            res += "deep: " + to_string(this->arrDeep);
            res += " len: ";
            for (auto elem : arrLength) res += to_string(elem) + " ";
            break;
    }

    return res;
}

DataType DataType::StructDataType(string id) {
    DataType dataType = DataType(class_);
    dataType.id = id;
    return dataType;
}

string DataType::TypeToString(DataType::Type type) {
    string res = "";
    switch (type) {

        case void_:
            res = varName(void_);
            break;
        case int_:
            res = varName(int_);
            break;
        case float_:
            res = varName(float_);
            break;
        case char_:
            res = varName(char_);
            break;
        case bool_:
            res = varName(bool_);
            break;
        case string_:
            res = varName(string_);
            break;
        case class_:
            res = varName(class_);
            break;
        case array_:
            res = varName(array_);
            break;
        case undefined_:
            res = varName(undefined_);
            break;
    }

    return res;
}

bool DataType::isEquals(const DataType &other) {
    bool res = true;
    res = res && this->type == other.type;

    switch (this->type) {

        case void_:
        case int_:
        case float_:
        case char_:
        case bool_:
        case string_:
        case undefined_:
            break;
        case class_:
            res = res && this->id == other.id;
            break;
        case array_:
            res = res && this->arrType == other.arrType;
            res = res && this->arrDeep == other.arrDeep;
            res = res && this->arrLength == other.arrLength;
            break;
    }
    return res;
}

bool DataType::isUndefined() {
    return this->type != undefined_;
}

void DataType::addArrType(DataType arrType) {
    if(array_){
        throw Exception(Exception::UNEXPECTED, "POKA NASRAT`");
    }
    else
    {
        this->arrType = arrType.type;
        this->id = arrType.id;
    }
}
