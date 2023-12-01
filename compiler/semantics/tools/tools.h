//
// Created by T0mmy on 27.11.2023.
//

#ifndef COMPILER_TOOLS_H
#define COMPILER_TOOLS_H
#define varName(x) #x
#include <iostream>
#include <vector>

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
    };

    ExceptionType exceptionType;
    string getMessage();
    Exception(ExceptionType exceptionType, string message);
};

#endif //COMPILER_TOOLS_H

