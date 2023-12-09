//
// Created by T0mmy on 27.11.2023.
//

#ifndef COMPILER_TOOLS_H
#define COMPILER_TOOLS_H
#define varName(x) #x
#define all(x) x.begin(), x.end()
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> split(string &str, char separator);

class Exception{
private:
    string message;
public:
    enum ExceptionType {
        STRUCT_WITH_TWO_TRAIT,
        DEFINED_MULTIPLE,
        NOT_IMPLEMICATION,
        NOT_A_METHOD,
        INCORRECT_CONST,
        INCORRECT_ARR_LENGTH,
        NOT_EXIST,
        NOT_SUPPORT,
        NOT_LITERAL_OPERATION,
        NOT_EQUAL_DATA_TYPE,
        NOT_CONST,
        OPERATION_NOT_SUPPORTED,
        NULL_DIVIDE,
        CANNOT_CONVERTED,
        INCORRECT_ENUM_VALUE,
        INCORRECT_TYPE,
    };

    ExceptionType exceptionType;
    string getMessage();
    Exception(ExceptionType exceptionType, string message);
};

#endif //COMPILER_TOOLS_H

