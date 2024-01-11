//
// Created by T0mmy on 11.01.2024.
//
#include "command.h"
#include "code_generator.h"
#include "code_generation/command.h"
#include "code_generation/tools/utils.h"
#include "code_generation/tools/byte_convert.h"

vector<char> CodeGenerator::generateField(const string& className, const string &fieldName,  FieldTableItem fieldTableItem) {

    vector<char> bytes;
    vector<char> buffer;

    // флаги
    unsigned int accessFlag  = uint16_t(AccessFlags::Public);
    if(fieldTableItem.isConst){
        accessFlag |= uint16_t(AccessFlags::Static);
    }
    bytes = IntToBytes(accessFlag);

    // имя поля
    buffer = IntToBytes(ClassTable::addUTF8ToConstTable(className, fieldName));
    bytes.insert(bytes.end(), u2(buffer));

    // дескриптор поля
    buffer = IntToBytes(ClassTable::addUTF8ToConstTable(className, fieldTableItem.dataType.toConstTableFormat()));
    bytes.insert(bytes.end(), u2(buffer));

    // количество атрибутов поля, таблица атрибутов поля
    bytes.push_back((char)0x00); bytes.push_back((char)0x00);

    return bytes;
}

vector<char>
CodeGenerator::generateMethod(const string &className, const string &fieldName, MethodTableItem methodTableItem) {

    std::vector<char> bytes;
    std::vector<char> buffer;
    return bytes;
}
