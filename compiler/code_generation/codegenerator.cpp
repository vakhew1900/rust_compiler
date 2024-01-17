//
// Created by T0mmy on 12.01.2024.
//

#include "codegenerator.h"
#include "fstream"

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

    // флаги доступаConstTable
    unsigned int accessFlags = uint16_t(AccessFlags::Public);

    if (methodTableItem.isStatic) {
        accessFlags |= uint16_t(AccessFlags::Static);
    }

    if (methodTableItem.body == NULL && methodName != ConstTable::init && methodName != ConstTable::clinit) {
        accessFlags |= uint16_t(AccessFlags::Abstract);
    }

    buffer = IntToBytes(accessFlags);
    bytes.insert(bytes.end(), u2(buffer));

    // имя метода
    if (!methodName.empty()) {
        buffer = IntToBytes(ClassTable::addUTF8ToConstTable(className, methodName));
        bytes.insert(bytes.end(), u2(buffer));
    }

    string decscriptor = methodTableItem.paramsToConstTableFormat();
    // количество атрибутов метода
    buffer = IntToBytes(ClassTable::addUTF8ToConstTable(className, decscriptor));
    bytes.insert(bytes.end(), u2(buffer));

    // количество атрибутов метода
    if (methodTableItem.body == NULL && methodName != ConstTable::init && methodName != ConstTable::clinit) {
        bytes.push_back((char) 0x00);
        bytes.push_back((char) 0x00);
        return bytes;
    }

    bytes.push_back((char) 0x00);
    bytes.push_back((char) 0x01);

    // имя атрибута Code
    buffer = IntToBytes(ClassTable::addUTF8ToConstTable(className, "Code"));
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
    if (methodName == ConstTable::init) {
        bodyCodeBytes = generateConstructor(className); // конструктор
    } else if (methodName == ConstTable::clinit) {
        bodyCodeBytes = generateStaticConstructor(className);
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
                           (char) 0x3D}; // // JAVA 8 (version 52.0 (0x34)) ///TODO заменить

    merge(bytes, buffer);

    vector<char> classBody = generateClassBody(className);
    vector<char> constants = ClassTable::Instance()->getClass(className).constTable.toBytes(); // consttable
    auto constantTable = ClassTable::Instance()->getClass(className).constTable.items;
    buffer = IntToBytes(constantTable.size());

    bytes.insert(bytes.end(), u2(buffer)); // размер constable
    merge(bytes, constants);
    merge(bytes, classBody);

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
            ClassTable::addMethodRefToConstTable(className, ConstTable::objectClassName, ConstTable::init,
                                                 vector<DataType>(), DataType(DataType::void_)));
    bytes.insert(bytes.end(), u2(methodRefId));

    bytes.push_back(char(Command::return_));
    return bytes;
}

vector<char> CodeGenerator::generateClassBody(const string &className) {
    vector<char> bytes;
    vector<char> buffer;

    ClassTableItem classTableItem = ClassTable::Instance()->getClass(className);

    ClassTable::addClassToConstTable(className, className);

    // Добавление флагов
    unsigned int accessFlags = uint16_t(AccessFlags::Public) | uint16_t(AccessFlags::Super);
    if (classTableItem.classType == ClassTableItem::trait_) {
        accessFlags |= uint16_t(AccessFlags::Abstract);
    }
    buffer = IntToBytes(accessFlags);
    bytes.insert(bytes.end(), u2(buffer));

    // текущий класс
    int classNameNum = ClassTable::addClassToConstTable(className, className);
    buffer = IntToBytes(classNameNum);
    bytes.insert(bytes.end(), u2(buffer));

    // класс-родитель
    string parentName = ConstTable::objectClassName;
    if (ClassTable::isHaveParent(className)) {
        parentName = classTableItem.parentName;
    }

    ConstTable constTable = classTableItem.constTable;
    int parentNameNum = ClassTable::addClassToConstTable(className, parentName);
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
    bool isConst = false;
    for (auto &field: fieldTable) {
        ClassTable::addFieldRefToConstTable(className, className, field.first,
                                            field.second.dataType);

        vector<char> fieldElement = generateField(className, field.first);
        bytes.insert(bytes.end(), all(fieldElement));
        isConst = isConst || field.second.isConst;
    }

    // количество методов c учетом конструктора

    if (isConst) {
        methodTable[ConstTable::clinit] = MethodTableItem::clinitMethod();
    }

    int methodSize = methodTable.size();
    buffer = IntToBytes(methodSize);
    bytes.insert(bytes.end(), u2(buffer));


    for (auto &method: methodTable) {
        ClassTable::addMethodRefToConstTable(className, className, method.first,
                                            method.second.getParamDataTypes(), method.second.returnDataType);
        buffer = generateMethod(className, method.first);
        merge(bytes, buffer);
    }

    // атрибуты
    bytes.push_back((char) 0x00);
    bytes.push_back((char) 0x00);

    return bytes;
}

vector<char> CodeGenerator::generateStaticConstructor(const string &className) {

    vector<char> bytes;
    ClassTableItem classTableItem = ClassTable::Instance()->getClass(className);

    for (auto &[fieldName, field]: classTableItem.fieldTable.items) {
        if (!field.isConst) {
            continue;
        }

        merge(bytes, field.value->generate());
        merge(bytes, commandToBytes(Command::putstatic));
        int fieldPosition = ClassTable::addFieldRefToConstTable(className, className,
                                                                fieldName,
                                                                field.dataType);
        merge(bytes, Int16ToBytes(fieldPosition));
    }

    merge(bytes, commandToBytes(Command::return_));
    return bytes;
}
