//
// Created by T0mmy on 27.11.2023.
//

#include "datatype.h"

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

DataType DataType::ArrayDataType(DataType::Type arrType, int arrDeep, int arrLength) {

    DataType dataType = ArrayDataType(arrType, arrDeep);
    dataType.arrLength = arrLength;
    return dataType;
}

DataType DataType::StructDataType(vector<string> structPath) {
    DataType dataType = DataType(struct_);
    dataType.structPath = structPath;
    return dataType;
}

DataType::DataType() {
    this->type = int_;
}
