//
// Created by T0mmy on 28.11.2023.
//

#ifndef COMPILER_CLASSTABLE_H
#define COMPILER_CLASSTABLE_H


#include "methodtable.h"
#include "fieldtable.h"
#include "constable.h"
#include <map>

using namespace std;

class ClassTableItem{
public:
    enum Type{
        struct_, enum_, trait_, mod_ // не факт что правильно
    };

    Type classType;
    string name;
    MethodTable methodTable;
    FieldTable fieldTable;
    string parentName; // имя родителя
    bool isPub = false;

    ConstTable constTable;

    ClassTableItem();
    ClassTableItem(FieldTable fieldTable, MethodTable methodTable, string parentName = "");
    string toString();
    bool isHaveParent();
};

class ClassTable {
private:
    static ClassTable* _instanse;
    map<string, ClassTableItem> items;
    ClassTable();
public:

    string toString();
    static const string moduleClassName;
    static const string globalClassName;

    static ClassTable* Instance();
    void addMethod(string className, string methodName, MethodTableItem methodTableItem);
    void updateMethod(string className, string methodName, MethodTableItem methodTableItem);
    void addField(string className, string fieldName, FieldTableItem fieldTableItem);
    void updateField(string className, string fieldName, FieldTableItem fieldTableItem);
    void addClass(string  className, ClassTableItem classTableItem);
    void addParent(string childName, string parentName);
    void addLocalParam(string className,string methodName, VarTableItem varTableItem);
    void addFuncParam(string className,string methodName, VarTableItem varTableItem);
    bool isClassExist(const string& className);
    bool isMethodExist(const string& className, const string& methodName);
    bool isFieldExist(const string& className, const string& methodName);
    bool isParamExist(const string& className, const string& methodName, const string& varName);
    bool isLocalVarExist(const string& className, const string& methodName, const string& varName);
    bool isLocalVarExist(const string& className, const string& methodName, const string& varName, const ExprNode* blockExpr);
    bool isParent(const string& child, const string& parentName);
    ClassTableItem getClass(const string& className);
    ClassTableItem getParentClass(const string &className);
    FieldTableItem getField(const string& className, const string& fieldName);
    MethodTableItem getMethod(const string& className, const string& methodName);
    VarTableItem getParam(const string& className, const string& methodName, int paramNum);
    VarTableItem getLocalVar(const string& className, const string& methodName, int localVarNum);
    static string getDirectory(string className);
    static void isCorrectChild(string childName, string parentName);
    static void isCorrectTraitsImpl();
};


#endif //COMPILER_CLASSTABLE_H
