//
// Created by T0mmy on 11.01.2024.
//

#ifndef COMPILER_CODE_GENERATOR_H
#define COMPILER_CODE_GENERATOR_H
#include <cstdint>
#include "classesnodes.h"
using namespace std;

class CodeGenerator {
private:
    vector<char>generateField(const string& className, const string& fieldName, FieldTableItem fieldTableItem);
    vector<char>generateMethod(const string& className, const string& fieldName, MethodTableItem methodTableItem);
};


#endif //COMPILER_CODE_GENERATOR_H
