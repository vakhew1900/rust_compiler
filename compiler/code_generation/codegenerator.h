//
// Created by T0mmy on 12.01.2024.
//

#ifndef COMPILER_CODEGENERATOR_H
#define COMPILER_CODEGENERATOR_H
#include "classesnodes.h"
#include "command.h"
#include "tools/utils.h"
#include "tools/byte_convert.h"

class CodeGenerator {
private:
    vector<char>generateField(const string& className, const string& fieldName, FieldTableItem fieldTableItem);
    vector<char>generateMethod(const string& className, const string& fieldName, MethodTableItem methodTableItem);
};



#endif //COMPILER_CODEGENERATOR_H

