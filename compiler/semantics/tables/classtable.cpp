//
// Created by T0mmy on 28.11.2023.
//

#include "classtable.h"
#include <fstream>

ClassTableItem::ClassTableItem() {
    MethodTableItem methodTableItem =  MethodTableItem::initMethod();
    this->methodTable.items[ConstTable::init] = methodTableItem;
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
    return !this->parentName.empty() && this->parentName != ConstTable::objectClassName;
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

void ClassTable::addMethod(const string& className, const string& methodName, MethodTableItem methodTableItem) {
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

const string ClassTable::moduleClassName = ConstTable::moduleClassName;
const string ClassTable::globalClassName = ConstTable::globalClassName;
const string ClassTable::RTLClassName = ConstTable::RTLClassName;


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

        string currentParentName = ClassTable::getParentClassName(childName);
        if(ClassTable::Instance()->isParent(currentParentName, parentName)){
           parentName = currentParentName;
        }
        else if (!ClassTable::Instance()->isParent(parentName, currentParentName)) {
            throw Exception(Exception::STRUCT_WITH_TWO_TRAIT, "struct" + childName + " should not has two traits");
        }
    }

    this->items[childName].parentName = parentName;
  //  cout << childName << " " << parentName << "\n";
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
            throw Exception(Exception::NOT_EXIST, fieldName + " not declaration in struct");
        }
    }

    for (auto elem: Instance()->getClass(parentName).methodTable.items) {
        string methodName = elem.first;

        if (!Instance()->isMethodExist(childName, methodName)
            && Instance()->getMethod(parentName, methodName).isHasBody == false) {
            throw Exception(Exception::NOT_EXIST, methodName + " not declaration in struct");
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

            string parentName = ClassTable::getParentClassName(elem.first);

            while(!parentName.empty()){
                isCorrectTraitImpl(elem.first, parentName);

                if(ClassTable::isHaveParent(parentName)){
                    parentName =  ClassTable::getParentClassName(parentName);
                }
                else {
                    break;
                }
            }

        }
    }

}

void ClassTable::isCorrectTraitImpl(const std::string &childName, const std::string &parentName) {

    ClassTableItem item = ClassTable::Instance()->getClass(childName);
    auto elem = make_pair(childName, item);

        ClassTableItem parentItem = ClassTable::Instance()->getClass(parentName);
        ClassTableItem curItem = elem.second;

        for (auto method: parentItem.methodTable.items) {

            if (!ClassTable::Instance()->isMethodExist(elem.first, method.first)) { // случай когда мы не переопределяли методж
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
                        "var with this name " + varTableItem.id + " in method " + methodName + " " + className +
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

    if (!ClassTable::isHaveParent(child)){
        return false;
    }

    if(child.empty() || parentName.empty()){
        return false;
    }

    if(ClassTable::Instance()->getClass(child).parentName == parentName){
        return true;
    }
    else {
        return ClassTable::Instance()->isParent(ClassTable::getParentClassName(child), parentName);
    }

}

bool ClassTable::isHaveParent(const string &child) {
    return ClassTable::Instance()->getClass(child).isHaveParent();
}

bool ClassTable::isHaveAccess(const string &requesterClass, const string &requestedClass) {

    if(requestedClass == ClassTable::RTLClassName){
        return true;
    }

    string requesterDirectory = getDirectory(requesterClass);
    string requestedDirectory = getDirectory(requestedClass);

    vector<string> requester = split(requesterDirectory, '/');
    vector<string> requested = split(requestedDirectory, '/');

    int counter = 0;
    string res = "";
    for (counter; counter < min(requester.size(), requested.size()); counter++) {
        if (requester[counter] != requested[counter])
            break;

        if (counter) res += "/";
        res += requested[counter];
    }


    if(counter == requested.size()){
        return true;
    }

    ClassTable classTable = *ClassTable::Instance();

    res += "/"  + requested[counter];
    counter++;

    if(res + "/" + ClassTable::moduleClassName == requestedClass){
        return true;
    }

    bool isSameLevel = true;
    for (int i = counter; i < requested.size(); i++) {
        if (!res.empty()) {
            res += "/";
        }

        if (!ClassTable::Instance()->getClass(res + moduleClassName).isPub && !isSameLevel) {
            return false;
        }

        isSameLevel = false;
        res += requested[i];
    }

    bool f = ClassTable::Instance()->getClass(requestedClass).isPub;
    bool debug_f = isEqualDirectory(requestedClass, requesterClass) || ClassTable::Instance()->getClass(requestedClass).isPub;
    return isEqualDirectory(requestedClass, requesterClass) || ClassTable::Instance()->getClass(requestedClass).isPub;
}

bool ClassTable::isHaveAccessToMethtod(const string &requesterClass, const string &requestedClass,
                                       const string &requestedMethod) {

    try {
        bool isHaveAccessToClass = ClassTable::isHaveAccess(requesterClass, requestedClass);
        bool isPub = ClassTable::getMethodDeep(requestedClass, requestedMethod).isPub;
        bool tmp = isSubDirectory(getDirectory(requesterClass), getDirectory(requestedClass));
        return isHaveAccessToClass && (isPub || tmp);
    } catch (Exception e) {
        throw e;
    }
}

bool ClassTable::isHaveAccessToField(const string &requesterClass, const string &requestedClass,
                                     const string &requestedField) {

    try {
        bool isHaveAccessToClass = ClassTable::isHaveAccess(requesterClass, requestedClass);
        bool isPub = ClassTable::getFieldDeep(requestedClass, requestedField).isPub;
        bool tmp = isSubDirectory(getDirectory(requesterClass), getDirectory(requestedClass));
        return isHaveAccessToClass && (isPub || tmp);
    } catch (Exception e) {
        throw e;
    }
}

bool ClassTable::isEqualDirectory(const string &first, const string &second) {
    return getDirectory(first) == getDirectory(second);
}

int ClassTable::addIntToConstTable(const string &className, int val) {
    Instance();
    return _instanse->items[className].constTable.Int(val);
}

int ClassTable::addFloatToConstTable(const string &className, float val) {
    Instance();
    return _instanse->items[className].constTable.Float(val);
}

int ClassTable::addStringToConstTable(const string &className, const string &str) {
    Instance();
    return _instanse->items[className].constTable.String(str);
}

int ClassTable::addClassToConstTable(const string &className, const string &addingClassName) {
    Instance();
    return _instanse->items[className].constTable.Class(addingClassName);
}

int ClassTable::addMethodRefToConstTable(const string &className, const string &addingClassName, const string &method,
                                         const vector<DataType> &params, const DataType &returnType) {
    Instance();
    return _instanse->items[className].constTable.MethodRef(addingClassName, method, params, returnType);
}

int ClassTable::addFieldRefToConstTable(const string &className, const string &addingClassName, const string &field,
                                        const DataType &dataType) {
    Instance();
    return _instanse->items[className].constTable.FieldRef(addingClassName, field, dataType);
}

int ClassTable::addUTF8ToConstTable(const string &className, const string &utf8) {
    Instance();
    return _instanse->items[className].constTable.UTF8(utf8);
}


void ClassTable::isMainFunctionExist() {
    if (ClassTable::Instance()->isMethodExist(globalClassName + "/" + moduleClassName, "main")) {
        MethodTableItem methodTableItem = ClassTable::Instance()->getMethod(globalClassName + "/" + moduleClassName,
                                                                            "main");

        if (methodTableItem.paramTable.items.size()) {
            throw Exception(Exception::UNEXPECTED,
                            "incorrect number of function parameters in `main`. expected 0 params");
        }
        if (!methodTableItem.returnDataType.isEquals(DataType(DataType::void_))) {
            throw Exception(Exception::TYPE_ERROR,
                            "`main` can only void_. ReturnType now: " + methodTableItem.returnDataType.toString());
        }
    } else {
        throw Exception(Exception::NOT_EXIST, "consider adding a `main` function");
    }
}

int ClassTable::getStructFieldCount(const string &className) {
    ClassTableItem classTableItem = ClassTable::Instance()->getClass(className);

    if (classTableItem.classType != ClassTableItem::struct_) {
        throw Exception(Exception::TYPE_ERROR, className + " is not struct");
    }

    int res = 0;

    for (auto elem: classTableItem.fieldTable.items) {
        res += elem.second.isConst == false;
    }
    return res;
}

void ClassTable::createConstTableCSV() {
    path classtable_dir = "./classtable/";

    if (!exists(classtable_dir)) {
        create_directory(classtable_dir);
        cout << "Directory created: " << classtable_dir << endl;
    }

    for(auto elem : ClassTable::Instance()->items){
        string filename = elem.first + ".csv";
        path filepath = classtable_dir / filename;
        if(!exists(filepath.parent_path())){
            create_directory(filepath.parent_path());
        }
        ofstream out(filepath);
        if (out.is_open()) {
            out << elem.second.constTable.toCSV() << endl;
            out.close();

        }
        else {
            // Handle the case if any error occured
            cerr << "Failed to create file: " << filepath << endl;
        }
    }
}

bool ClassTable::isMethodExistDeep(const string &className, const string &methodName) {

    if (ClassTable::Instance()->isMethodExist(className, methodName)) {
        return true;
    }

    return ClassTable::isHaveParent(className) &&
            isMethodExistDeep(ClassTable::getParentClassName(className), methodName);
}

bool ClassTable:: isFieldExistDeep(const string& className, const string& fieldName){
    if (ClassTable::Instance()->isFieldExist(className, fieldName)) {
        return true;
    }

    return ClassTable::isHaveParent(className) &&
            isFieldExistDeep(ClassTable::getParentClassName(className), fieldName);
}

string ClassTable::getParentClassName(const std::string &className) {
    ClassTableItem classTableItem = ClassTable::Instance()->getClass(className);
    if (!ClassTable::isHaveParent(className)){
        throw Exception(Exception::NOT_EXIST, className + " not has parent");
    }
    return classTableItem.parentName;
}

MethodTableItem ClassTable::getMethodDeep(const string &className, const string &methodName) {
    if(!ClassTable::isMethodExistDeep(className, methodName)){
        throw Exception(Exception::NOT_EXIST, className + " not has method " + methodName);
    }

    if(ClassTable::Instance()->isMethodExist(className, methodName)){
        return ClassTable::Instance()->getMethod(className, methodName);
    }

    return ClassTable::getMethodDeep(ClassTable::getParentClassName(className), methodName);
}

FieldTableItem ClassTable::getFieldDeep(const string &className, const string &fieldName) {
    if(!ClassTable::isFieldExistDeep(className, fieldName)){
        throw Exception(Exception::NOT_EXIST, className + " not has field " + fieldName);
    }

    if(ClassTable::Instance()->isFieldExist(className, fieldName)){
        return ClassTable::Instance()->getField(className, fieldName);
    }

    return ClassTable::getFieldDeep(ClassTable::getParentClassName(className), fieldName);
}

bool ClassTable::isSubDirectory(const string &subdir, const string &dir) {

    vector<string> dirContainer = split(dir, '/');
    vector<string> subdirContainer = split(subdir, '/');

    if (subdirContainer.size() < dirContainer.size())
    {
        return false;
    }

    while(subdirContainer.size() > dirContainer.size()){
        subdirContainer.pop_back();
    }

    return subdirContainer == dirContainer;
}

bool ClassTable::isEnum(const string &className) {
    return ClassTable::Instance()->getClass(className).classType == ClassTableItem::enum_;
}

map<string, ClassTableItem> ClassTable::getItems() {
    return ClassTable::Instance()->items;
}

void ClassTable::makeMainForJavaFormat() {
    string mainClass = ConstTable::globalClassName + "/" + ConstTable::moduleClassName;
    string main = "main";
    MethodTableItem methodTableItem = ClassTable::Instance()->getMethod(mainClass, main);
    VarTableItem varTableItem = VarTableItem();
    varTableItem.id = "args";
    varTableItem.dataType = DataType::ArrayDataType(DataType::string_, 1, {1});
    methodTableItem.paramTable.items.push_back(varTableItem);
    ClassTable::Instance()->updateMethod(mainClass, main, methodTableItem);
}

int ClassTable::addLoopCounterVar(string className, string methodName) {
    VarTableItem varTableItem = VarTableItem();
    varTableItem.id = "$$"; // спецсимвол
    varTableItem.dataType = DataType(DataType::int_);
    ClassTable::Instance()->items[className].methodTable.items[methodName].localVarTable.items.push_back(varTableItem);
    int res = ClassTable::Instance()->items[className].methodTable.items[methodName].localVarTable.items.size() - 1;
    return  res;
}
