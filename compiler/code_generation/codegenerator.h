//
// Created by T0mmy on 12.01.2024.
//

#ifndef COMPILER_CODEGENERATOR_H
#define COMPILER_CODEGENERATOR_H
#include "classesnodes.h"
#include "command.h"
#include "tools/utils.h"
#include "tools/byte_convert.h"

using namespace std::filesystem;

class CodeGenerator {
private:

    static const path codeGenDir;

    vector<char>generateField(const string& className, const string& fieldName);
    vector<char>generateMethod(const string& className, const string& fieldName);
    void generateClass(const string& className);

public:
    void generate();
};



#endif //COMPILER_CODEGENERATOR_H

