//
// Created by T0mmy on 12.01.2024.
//

#include "codegenerator.h"
#include "fstream"

using namespace std::filesystem;

const path CodeGenerator::codeGenDir = "./code_generation/";

vector<char> CodeGenerator::generateField(const string &className, const string &fieldName) {

    vector<char> bytes;
    vector<char> buffer;

    // флаги
    FieldTableItem fieldTableItem = ClassTable::Instance()->getField(className, fieldName);

    unsigned int accessFlag = uint16_t(AccessFlags::Public);
    if (fieldTableItem.isConst) {
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
    bytes.push_back((char) 0x00);
    bytes.push_back((char) 0x00);

    return bytes;
}

vector<char>
CodeGenerator::generateMethod(const string &className, const string &methodName) {

    std::vector<char> bytes;
    std::vector<char> buffer;

    MethodTableItem methodTableItem = ClassTable::Instance()->getMethod(className, methodName);
    ConstTable constTable = ClassTable::Instance()->getClass(className).constTable;

    // флаги доступа
    unsigned int accessFlags = uint16_t(AccessFlags::Public);

    if (methodTableItem.isStatic) {
        accessFlags |= uint16_t(AccessFlags::Static);
    }

    buffer = IntToBytes(accessFlags);
    bytes.insert(bytes.end(), u2(buffer));

    // имя метода
    if (!methodName.empty()) {
        buffer = IntToBytes(constTable.UTF8(methodName));
        bytes.insert(bytes.end(), u2(bytes));
    }

    string decscriptor = methodTableItem.paramsToConstTableFormat();
    // количество атрибутов метода
    buffer = IntToBytes(constTable.UTF8(decscriptor));
    bytes.insert(bytes.end(), u2(bytes));

    // количество атрибутов метода
    if (methodTableItem.body == NULL) {
        bytes.push_back((char) 0x00);
        bytes.push_back((char) 0x00);
        return bytes;
    }

    bytes.push_back((char) 0x00);
    bytes.push_back((char) 0x01);

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
    vector<char> bodyCodeBytes;
    if (methodName == ConstTable::constructorName) {
        bodyCodeBytes = generateConstructor(className); // конструктор
    } else {
        bodyCodeBytes = methodTableItem.body->generate(); // не конструктор
    }

    buffer = IntToBytes(bodyCodeBytes.size());
    codeAttributeBytes.insert(codeAttributeBytes.end(), buffer.begin(), buffer.end());

    // байт-код
    codeAttributeBytes.insert(codeAttributeBytes.end(), bodyCodeBytes.begin(), bodyCodeBytes.end());

    // количество записи в таблице исключений - не ебет
    codeAttributeBytes.push_back((char) 0x00);
    codeAttributeBytes.push_back((char) 0x00);

    // количество атрибутов - не ебет
    codeAttributeBytes.push_back((char) 0x00);
    codeAttributeBytes.push_back((char) 0x00);

    // длина атрибута (кроме первых 6-ти
    //байт, описывающих имя и длину)
    buffer = IntToBytes(codeAttributeBytes.size());
    bytes.insert(bytes.end(), buffer.begin(), buffer.end());

    // собственно добавление самого атрибута
    bytes.insert(bytes.end(), codeAttributeBytes.begin(), codeAttributeBytes.end());
    return bytes;
}

void CodeGenerator::generateClass(const string &className) {

    // создание файла
    string fileName = className + ".class";
    path filepath = codeGenDir / fileName;
    create_directory(filepath.parent_path());

    std::ofstream outfile;
    outfile.open(filepath, std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);


    ClassTableItem classTableItem = ClassTableItem();

    // заполнение файла
    vector<char> bytes = {(char) 0xCA, (char) 0xFE, (char) 0xBA, (char) 0xBE}; // CAFEBABE
    vector<char> buffer = {(char) 0x00, (char) 0x00, (char) 0x00,
                           (char) 0x3E}; // // JAVA 8 (version 52.0 (0x34)) ///TODO заменить

    bytes.insert(bytes.end(), u2(buffer));

    vector<char> constants = ClassTable::Instance()->getClass(className).constTable.toBytes(); // consttable

    buffer = IntToBytes(constants.size() + 1);

    bytes.insert(bytes.end(), u2(buffer)); // размер constable
    bytes.insert(bytes.end(), u2(constants)); // размер constable

    // Добавление флагов
    unsigned int accessFlags = uint16_t(AccessFlags::Public) | uint16_t(AccessFlags::Super);
    buffer = IntToBytes(accessFlags);
    bytes.insert(bytes.end(), u2(buffer));

    // текущий класс
    int classNameNum = ClassTable::addUTF8ToConstTable(className, className);
    buffer = IntToBytes(classNameNum);
    bytes.insert(bytes.end(), u2(buffer));

    // класс-родитель
    string parentName = ConstTable::objectClassName;
    if (ClassTable::isHaveParent(className)) {
        parentName = classTableItem.parentName;
    }

    int parentNameNum = ClassTable::addUTF8ToConstTable(className, parentName);
    buffer = IntToBytes(parentNameNum);
    bytes.insert(bytes.end(), u2(buffer));


    bytes.push_back((char) 0x00);
    bytes.push_back((char) 0x00);  // таблица интерфейсов

    auto fieldTable = classTableItem.fieldTable.items;
    auto methodTable = classTableItem.methodTable.items;

    // количество полей
    int fieldSize = fieldTable.size();
    buffer = IntToBytes(fieldSize);
    bytes.insert(bytes.end(), u2(buffer));

    // добавление полей
    for (auto &field: fieldTable) {
        vector<char> fieldElement = generateField(className, field.first);
        bytes.insert(bytes.end(), all(fieldElement));
    }

    // количество методов c учетом конструктора
    int methodSize = methodTable.size() + 1;
    buffer = IntToBytes(methodSize);
    bytes.insert(bytes.end(), u2(buffer));


    buffer = generateMethod(className, ConstTable::constructorName);
    bytes.insert(bytes.end(), u2(buffer));

    for (auto &method: methodTable) {
        buffer = generateMethod(className, method.first);
        bytes.insert(bytes.end(), u2(buffer));
    }

    // атрибуты
    bytes.push_back((char) 0x00);
    bytes.push_back((char) 0x00);

    outfile.write(bytes.data(), bytes.size());
}

void CodeGenerator::generate() {


    if (exists(CodeGenerator::codeGenDir)) {
        filesystem::remove_all(codeGenDir);
    }

    filesystem::create_directory(codeGenDir);
    for (auto &[className, classTableItem]: ClassTable::getItems()) {

        if (className == ClassTable::RTLClassName) continue;

        generateClass(className);
    }

}

vector<char> CodeGenerator::generateConstructor(const string &className) {
    std::vector<char> bytes;
    bytes.push_back(char(Command::aload));
    bytes.push_back(char(0));

    bytes.push_back(char(Command::invokespecial));
    auto methodRefId = IntToBytes(
            ClassTable::addMethodRefToConstTable(className, ConstTable::objectClassName, ConstTable::constructorName,
                                                 vector<DataType>(), DataType(DataType::void_)));
    bytes.insert(bytes.end(), u2(methodRefId));

    bytes.push_back(char(Command::return_));
    return bytes;
}
