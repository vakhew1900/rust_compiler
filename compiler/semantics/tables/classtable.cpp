//
// Created by T0mmy on 28.11.2023.
//

#include "classtable.h"

ClassTableItem::ClassTableItem() {

}

ClassTableItem::ClassTableItem(FieldTable fieldTable, MethodTable methodTable, string parentName) {
    this->fieldTable = fieldTable;
    this->methodTable = methodTable;
    this->parentName = parentName;
}

string ClassTableItem::toString() {
    string res = "";

    if (isPub) {
        res += " public ";
    } else {
        res += " package ";
    }

    switch (classType) {

        case struct_:
            res += varName(struct_);
            break;
        case enum_:
            res += varName(enum_);
            break;
        case trait_:
            res += varName(trait_);
            break;
        case mod_:
            res += varName(mod_);
            break;
    }


    if (parentName.size()) {
        res += " parent: " + parentName;
    }

    res += "\nfieldTable:\n" + fieldTable.toString();
    res += "\nmethodTable:\n" + methodTable.toString() + "\n";

    return res;
}

bool ClassTableItem::isHaveParent() {
    return !this->parentName.empty();
}


string ClassTable::toString() {
    string res;

    for (auto elem: items) {
        string tmp = elem.first + " " + elem.second.toString();
        res += tmp;
    }

    return res;
}

ClassTable *ClassTable::_instanse = NULL;

ClassTable *ClassTable::Instance() {
    if (_instanse == NULL) {
        _instanse = new ClassTable();
    }

    return _instanse;
}

ClassTable::ClassTable() {

}

void ClassTable::addMethod(string className, string methodName, MethodTableItem methodTableItem) {
    if (ClassTable::Instance()->isMethodExist(className, methodName)) {
        throw Exception(Exception::DEFINED_MULTIPLE, methodName + "DEFINED_MULTIPLE in namespace");
    }

    this->items[className].methodTable.items[methodName] = methodTableItem;
}

void ClassTable::updateMethod(string className, string methodName, MethodTableItem methodTableItem) {
    if (!ClassTable::Instance()->isMethodExist(className, methodName)) {
        throw Exception(Exception::NOT_EXIST, methodName + " method not exist in class" + className);
    }

    this->items[className].methodTable.items[methodName] = methodTableItem;
}

void ClassTable::addField(string className, string fieldName, FieldTableItem fieldTableItem) {
    if (ClassTable::Instance()->isFieldExist(className, fieldName)) {
        throw Exception(Exception::DEFINED_MULTIPLE, fieldName + " DEFINED_MULTIPLE in namespace");
    }

    this->items[className].fieldTable.items[fieldName] = fieldTableItem;
}

void ClassTable::updateField(string className, string fieldName, FieldTableItem fieldTableItem) {
    if (!ClassTable::Instance()->isFieldExist(className, fieldName)) {
        throw Exception(Exception::NOT_EXIST, fieldName + " field not exist in class" + className);
    }
    this->items[className].fieldTable.items[fieldName] = fieldTableItem;
}


void ClassTable::addClass(string className, ClassTableItem classTableItem) {

    if (ClassTable::Instance()->isClassExist(className)) {
        throw Exception(Exception::DEFINED_MULTIPLE, className + "DEFINED_MULTIPLE in namespace");
    }

    this->items[className] = classTableItem;
}

bool ClassTable::isClassExist(const string &className) {
    return this->items.find(className) != this->items.end();
}

bool ClassTable::isMethodExist(const std::string &className, const std::string &methodName) {
    return this->items[className].methodTable.items.find(methodName) != this->items[className].methodTable.items.end();
}

bool ClassTable::isFieldExist(const string &className, const string &fieldName) {
    return this->items[className].fieldTable.items.find(fieldName) != this->items[className].fieldTable.items.end();
}

ClassTableItem ClassTable::getClass(const string &className) {
    return this->items[className];
}

const string ClassTable::moduleClassName = "moduleClass";
const string ClassTable::globalClassName = "GLOBAL_CLASS";

string ClassTable::getDirectory(string className) {
    vector<string> classPath = split(className, '/');

    string res = "";

    res += classPath[0];
    for (int i = 1; i < classPath.size() - 1; i++) {
        res += "/" + classPath[i];
    }

    return res;
}

void ClassTable::addParent(string childName, string parentName) {
    if (ClassTable::Instance()->getClass(childName).isHaveParent()) {
        throw Exception(Exception::STRUCT_WITH_TWO_TRAIT, "struct" + childName + "should not has two traits");
    }

    this->items[childName].parentName = parentName;
    cout << childName << " " << parentName << "\n";
}

void ClassTable::isCorrectChild(string childName, string parentName) {

    if (!ClassTable::Instance()->isClassExist(childName)) {
        throw Exception(Exception::NOT_EXIST, childName + " DEFINED_MULTIPLE in namespace");
    }

    if (!ClassTable::Instance()->isClassExist(parentName)) {
        throw Exception(Exception::NOT_EXIST, parentName + " NOT_EXIST in namespace");
    }

    bool res = true;

    for (auto elem: Instance()->getClass(parentName).fieldTable.items) {
        string fieldName = elem.first;

        if (!Instance()->isFieldExist(childName, fieldName)
            && Instance()->getField(parentName, fieldName).isInit == false) {
            throw Exception(Exception::NOT_EXIST, fieldName + "not declaration in struct");
        }
    }

    for (auto elem: Instance()->getClass(parentName).methodTable.items) {
        string methodName = elem.first;

        if (!Instance()->isMethodExist(childName, methodName)
            && Instance()->getMethod(parentName, methodName).isHasBody == false) {
            throw Exception(Exception::NOT_EXIST, methodName + "not declaration in struct");
        }
    }
}

FieldTableItem ClassTable::getField(const string &className, const string &fieldName) {

    if (!ClassTable::Instance()->isFieldExist(className, fieldName)) {
        throw Exception(Exception::NOT_EXIST, fieldName + " NOT_EXIST in namespace " + className);
    }

    return Instance()->getClass(className).fieldTable.items[fieldName];
}

MethodTableItem ClassTable::getMethod(const string &className, const string &methodName) {

    if (!ClassTable::Instance()->isMethodExist(className, methodName)) {
        throw Exception(Exception::NOT_EXIST, methodName + " NOT_EXIST in namespace " + className);
    }

    return Instance()->getClass(className).methodTable.items[methodName];
}

void ClassTable::addFuncParam(string className, string methodName, VarTableItem varTableItem) {
    this->items[className].methodTable.items[methodName].paramTable.items.push_back(varTableItem);
}

bool ClassTable::isParamExist(const string &className, const string &methodName, const string &varName) {
    return this->getMethod(className, methodName).paramTable.isExist(varName);
}

void ClassTable::isCorrectTraitsImpl() {


    for (auto elem: _instanse->items) {
        if (elem.second.isHaveParent()) {
            ClassTableItem parentItem = ClassTable::Instance()->getParentClass(elem.first);
            ClassTableItem curItem = elem.second;

            for (auto method: parentItem.methodTable.items) {

                if (ClassTable::Instance()->isMethodExist(elem.first, method.first) ==
                    false) { // случай когда мы не переопределяли методж
                    continue;
                }

                if (!method.second.isEqualsDeclaration(curItem.methodTable.items[method.first])) {
                    throw Exception(Exception::IMPL_AND_TRAIT_DECLARATION,
                                    " method " + method.first + "in trait " + curItem.parentName + " and in " +
                                    elem.first +
                                    " have different declaration");
                }
            }

            for (auto field: parentItem.fieldTable.items) {

                if (!ClassTable::Instance()->isFieldExist(elem.first, field.first)) {
                    continue;
                }
                if (!field.second.isEquals(curItem.fieldTable.items[field.first])) {
                    throw Exception(Exception::IMPL_AND_TRAIT_DECLARATION,
                                    "field " + field.first + " in trait " + curItem.parentName + " and in " +
                                    elem.first +
                                    "have different declaration");
                }
            }
        }
    }

}

ClassTableItem ClassTable::getParentClass(const string &className) {
    if (!ClassTable::Instance()->getClass(className).isHaveParent()) {
        throw Exception(Exception::NO_HAVE_PARENT, className + " NO HAVE PARENT");
    }
    string parentName = ClassTable::Instance()->getClass(className).parentName;
    return ClassTable::Instance()->getClass(parentName);
}

bool ClassTable::isLocalVarExist(const string &className, const string &methodName, const string &varName,
                                 const ExprNode *blockExpr) {
    return this->getMethod(className, methodName).localVarTable.isExist(varName, blockExpr);
}

bool ClassTable::isLocalVarExist(const string &className, const string &methodName, const string &varName) {
    return this->getMethod(className, methodName).localVarTable.isExist(varName);
}

void ClassTable::addLocalParam(string className, string methodName, VarTableItem varTableItem) {

    if (ClassTable::Instance()->isLocalVarExist(className, methodName, varTableItem.id, varTableItem.blockExpr)) {
        throw Exception(Exception::VAR_ALREADY_EXISTS,
                        "var with this name " + varTableItem.id + "in method " + methodName + " " + className +
                        " is already exists");
    }

    ClassTable::Instance()->items[className].methodTable.items[methodName].localVarTable.items.push_back(varTableItem);
}

VarTableItem ClassTable::getParam(const string &className, const string &methodName, int paramNum) {

    try {
        return ClassTable::Instance()->getMethod(className, methodName).paramTable.getVar(paramNum);
    }
    catch (Exception e) {
        throw Exception(Exception::NOT_EXIST, e.getMessage() + " " + className + " " + methodName);
    }
}

VarTableItem ClassTable::getLocalVar(const string &className, const string &methodName, int localVarNum) {
    try {
        return ClassTable::Instance()->getMethod(className, methodName).localVarTable.getVar(localVarNum);
    }
    catch (Exception e) {
        throw Exception(Exception::NOT_EXIST, e.getMessage() + " " + className + " " + methodName);
    }
}

bool ClassTable::isParent(const string &child, const string &parentName) {
    return ClassTable::Instance()->getClass(child).parentName == parentName;
}

bool ClassTable::isHaveParent(const string &child) {
    return ClassTable::Instance()->getClass(child).isHaveParent();
}

bool ClassTable::isHaveAccess(const string &requesterClass, const string &requestedClass) {
    string requesterDirectory = getDirectory(requestedClass);
    string requestedDirectory = getDirectory(requestedClass);

    vector<string> requester = split(requestedDirectory, '/');
    vector<string> requested = split(requestedDirectory, '/');

    int counter = 0;
    string res = "";
    for (counter; counter < min(requester.size(), requested.size()); counter++) {
        if (requester[counter] != requested[counter])
            break;

        if (counter) res += "/";
        res += requested[counter];
    }

    for (int i = counter; i < requested.size(); i++) {
        if (!res.empty()) {
            res += "/";
        }

        if (!ClassTable::Instance()->getClass(res + moduleClassName).isPub) {
            return false;
        }

        res += requested[i];
    }

    return isEqualDirectory(requestedClass, requesterClass) || ClassTable::Instance()->getClass(requestedClass).isPub;
}

bool ClassTable::isHaveAccessToMethtod(const string &requesterClass, const string &requestedClass,
                                       const string &requestedMethod) {

    try {
        bool res = ClassTable::isHaveAccess(requesterClass, requestedClass);
        return res && (ClassTable::Instance()->getMethod(requestedClass, requestedMethod).isPub || isEqualDirectory(requesterClass, requestedClass));
    } catch (Exception e) {
        throw e;
    }
}

bool ClassTable::isHaveAccessToField(const string &requesterClass, const string &requestedClass,
                                     const string &requestedField) {

    try {
        bool res = ClassTable::isHaveAccess(requesterClass, requestedClass);
        return res && (ClassTable::Instance()->getField(requestedClass, requestedField).isPub || isEqualDirectory(requesterClass, requestedClass));
    } catch (Exception e) {
        throw e;
    }
}

bool ClassTable::isEqualDirectory(const string &first, const string &second) {
    return getDirectory(first) == getDirectory(second);
}

int ClassTable::addIntToConstTable(const string& className, int val){
    Instance();
    return _instanse->items[className].constTable.Int(val);
}

int ClassTable::addFloatToConstTable(const string& className, double val){
    Instance();
    return _instanse->items[className].constTable.Double(val);
}

int ClassTable::addStringToConstTable(const string& className, const string& str){
    Instance();
    return _instanse->items[className].constTable.String(str);
}

int ClassTable::addClassToConstTable(const string& className, const string& addingClassName){
    Instance();
    return _instanse->items[className].constTable.Class(addingClassName);
}

int ClassTable::addMethodRefToConstTable(const string& className, const string& addingClassName, const string& method, const vector<DataType> &params,const DataType &returnType){
    Instance();
    return _instanse->items[className].constTable.MethodRef(addingClassName, method, params, returnType);
}

int ClassTable::addFieldRefToConstTable(const string& className, const string& addingClassName, const string& field, const DataType& dataType){
    Instance();
    return _instanse->items[className].constTable.FieldRef(addingClassName, field, dataType);
}

void ClassTable::isMainFunctionExist() {
    if(ClassTable::Instance()->isMethodExist(globalClassName + "/" + moduleClassName, "main")){
        MethodTableItem methodTableItem = ClassTable::Instance()->getMethod(globalClassName + "/" + moduleClassName, "main");

        if(methodTableItem.paramTable.items.size()){
           throw Exception(Exception::UNEXPECTED, "incorrect number of function parameters in `main`. expected 0 params");
        }
        if(!methodTableItem.returnDataType.isEquals(DataType(DataType::void_))){
            throw Exception(Exception::TYPE_ERROR, "`main` can only void_. ReturnType now: " + methodTableItem.returnDataType.toString());
        }
    }
    else {
        throw Exception(Exception::NOT_EXIST, "consider adding a `main` function");
    }
}

int ClassTable::getStructFieldCount(const string &className) {
    ClassTableItem classTableItem = ClassTable::Instance()->getClass(className);

    if(classTableItem.classType != ClassTableItem::struct_){
        throw Exception(Exception::TYPE_ERROR, className + " is not struct");
    }

    int res = 0;

    for(auto elem : classTableItem.fieldTable.items){
        res += elem.second.isConst == false;
    }
    return res;
}
