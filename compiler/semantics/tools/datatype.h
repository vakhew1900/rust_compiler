//
// Created by T0mmy on 27.11.2023.
//

#ifndef COMPILER_DATATYPE_H
#define COMPILER_DATATYPE_H

#include <iostream>
#include <vector>

using  namespace  std;

class DataType {
public:
    enum Type {
        void_, int_, float_, char_, bool_, string_, struct_, array_
    };

    Type type;
    Type arrType; // тип значений которые хранятся в массиве
    int arrDeep = 0; // 1 - одномерный массив, 2 - двумерный массив и т.д.
    int arrLength = -1; // -1 - undefined
    vector<string> structPath; // полный путь до структуры т. е.  последнее слово в массиве название структуры - остальное путь
    string id; // мб лучше это использовать

    DataType();
    DataType(Type type);
    static DataType ArrayDataType(Type arrType, int arrDeep);
    static DataType ArrayDataType(Type arrType, int arrDeep, int arrLength);
    static DataType StructDataType(vector<string> structPath);
};




#endif //COMPILER_DATATYPE_H
