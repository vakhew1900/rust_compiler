//
// Created by T0mmy on 27.11.2023.
//

#ifndef COMPILER_DATATYPE_H
#define COMPILER_DATATYPE_H

#include <iostream>
#include <vector>
#include "tools.h"


using  namespace  std;

class DataType {
public:
    enum Type {
        void_, int_, float_, char_, bool_, string_, class_, array_, undefined_
    };

    Type type;
    Type arrType; // тип значений которые хранятся в массиве
    int arrDeep = 0; // 1 - одномерный массив, 2 - двумерный массив и т.д.
    vector<int> arrLength; // -1 - undefined
    vector<string> structPath; // полный путь до структуры т. е.  последнее слово в массиве название структуры - остальное путь
    string id; // мб лучше это использовать
    vector<DataType> arrTypes;
    DataType();
    DataType(Type type);
    static DataType ArrayDataType(Type arrType, int arrDeep);
    static DataType ArrayDataType(Type arrType, int arrDeep, vector<int> arrLength);
    static DataType StructDataType(vector<string> structPath);
    static DataType StructDataType(string id);
    string toString();
    static string TypeToString(Type type);
    bool isEquals(const DataType &other);
    bool isUndefined();
    void addArrType(DataType arrType);
    static bool isEquals(vector<DataType> types);
};




#endif //COMPILER_DATATYPE_H
