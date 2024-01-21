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
    string res = "";

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
            for (auto elem: arrLength) res += to_string(elem) + " ";
            break;
        case undefined_:
            res += varName(undefined_);
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
    return this->type == undefined_;
}

void DataType::addArrType(DataType arrType) {
    if (this->type != DataType::array_) {
        throw Exception(Exception::UNEXPECTED, "POKA NASRAT`");
    } else {
        this->arrType = arrType.type;
        this->id = arrType.id;
    }
}

bool DataType::isEquals(vector<DataType> types) {
    if (types.size() == 0) {
        return true;
    }

    DataType type = types.front();

    bool res = true;

    for (auto elem: types) {
        res = res && elem.isEquals(type);
    }

    return res;
}

DataType DataType::getArrDataType() const {
    DataType dataType = *this;
    if (this->type != array_) {
        throw Exception(Exception::TYPE_ERROR, "cannot get ArrType because it is not array_");
    }

    dataType.arrDeep--;
    dataType.arrLength.pop_back();

    if (dataType.arrDeep == 0) {
        dataType.type = dataType.arrType;
    }

    return dataType;
}

bool DataType::isCanConvert(DataType first, DataType second) {

    if (first.type == second.type && first.type != class_ && first.type != array_ && first.type != void_) {
        return true;
    }

    if (first.type == int_ && second.type == float_) {
        return true;
    }

    if (first.type == int_ && second.type == char_) {
        return true;
    }

    if (first.type == float_ && second.type == int_) {
        return true;
    }

    if (first.type == char_ && second.type == int_) {
        return true;
    }

    return false;
}

string DataType::toConstTableFormat() const {
    string res;
    switch (type) {

        case void_:
            res = "V";
            break;
        case int_:
            res = "I";
            break;
        case float_:
            res = "F";
            break;
        case char_:
            res = "C";
            break;
        case bool_:
            res = "I";
            break;
        case string_:
            res = "Ljava/lang/String;";
            break;
        case class_:
            res = "L" + id + ";";
            break;
        case array_:
            res += "[";
            res += getArrDataType().toConstTableFormat();
            break;
        case undefined_:
            throw Exception(Exception::UNEXPECTED, "cannot convert type for consttable");
            break;
    }

    return res;
}

bool DataType::isClass() {
    return  this->type == DataType::class_ ||
               this->type == DataType::array_ && this->arrType == DataType::class_;
}

bool DataType::isSimple() {
    return this->type != array_ && this->type != class_ && this->type != string_;
}

bool DataType::isInt() {
    return this->type == int_;
}

bool DataType::isFloat() {
    return this->type == float_;
}

bool DataType::isVoid() {
    return this->type == void_;
}

bool DataType::isString() {
    return this->type == string_;
}

bool DataType::isChar() {
    return this->type == char_;
}

bool DataType::isArray() {
    return this->type == array_;
}

bool DataType::isBool() {
    return this->type == bool_;
}
