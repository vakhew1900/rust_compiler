//
// Created by T0mmy on 12.01.2024.
//

#include "codegenerator.h"

vector<char> CodeGenerator::generateField(const string& className, const string &fieldName) {

    vector<char> bytes;
    vector<char> buffer;

    // флаги
    FieldTableItem fieldTableItem = ClassTable::Instance()->getField(className, fieldName);

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
CodeGenerator::generateMethod(const string &className, const string &methodName) {

    std::vector<char> bytes;
    std::vector<char> buffer;

    MethodTableItem methodTableItem = ClassTable::Instance()->getMethod(className, methodName);
    ConstTable constTable = ClassTable::Instance()->getClass(className).constTable;

    // флаги доступа
    unsigned int  accessFlags = uint16_t(AccessFlags::Public);

    if(methodTableItem.isStatic) {
        accessFlags |= uint16_t(AccessFlags::Static);
    }

    buffer = IntToBytes(accessFlags);
    bytes.insert(bytes.end(), u2(buffer));

    // имя метода
    if (!methodName.empty()) {
        buffer = IntToBytes(constTable.UTF8(methodName));
        bytes.insert(bytes.end(), buffer.begin() + 2, buffer.end());
    }

    string decscriptor = methodTableItem.paramsToConstTableFormat();
    // количество атрибутов метода
    buffer = IntToBytes(constTable.UTF8(decscriptor));
    bytes.insert(bytes.end(), buffer.begin() + 2, buffer.end());

    // количество атрибутов метода
    if(methodTableItem.body == NULL){
        bytes.push_back((char)0x00); bytes.push_back((char)0x00);
        return bytes;
    }

    bytes.push_back((char)0x00); bytes.push_back((char)0x01);

    // имя атрибута Code
    buffer = IntToBytes(constTable.UTF8("Code"));
    bytes.insert(bytes.end(), u2(buffer));

    std::vector<char> codeAttributeBytes;

    // размер стека операндов для метода
    const int MAX_SIZE_OPERANDS = 1024;
    buffer = IntToBytes(MAX_SIZE_OPERANDS);
    codeAttributeBytes.insert(codeAttributeBytes.end(), u2(buffer));

    // количество локальных переменных метода
    buffer = IntToBytes(methodTableItem.localVarTable.size());
    codeAttributeBytes.insert(codeAttributeBytes.end(), u2(buffer));

    // длина собственно байт-кода
    vector<char> bodyCodeBytes = methodTableItem.body->generate();
    buffer = IntToBytes(bodyCodeBytes.size());
    codeAttributeBytes.insert(codeAttributeBytes.end(), buffer.begin(), buffer.end());

    // байт-код
    codeAttributeBytes.insert(codeAttributeBytes.end(), bodyCodeBytes.begin(), bodyCodeBytes.end());

    // количество записи в таблице исключений - не ебет
    codeAttributeBytes.push_back((char)0x00); codeAttributeBytes.push_back((char)0x00);

    // количество атрибутов - не ебет
    codeAttributeBytes.push_back((char)0x00); codeAttributeBytes.push_back((char)0x00);

    // длина атрибута (кроме первых 6-ти
    //байт, описывающих имя и длину)
    buffer = IntToBytes(codeAttributeBytes.size());
    bytes.insert(bytes.end(), buffer.begin(), buffer.end());

    // собственно добавление самого атрибута
    bytes.insert(bytes.end(), codeAttributeBytes.begin(), codeAttributeBytes.end());

    return bytes;
}
