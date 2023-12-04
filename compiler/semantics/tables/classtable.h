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
    void addField(string className, string fieldName, FieldTableItem fieldTableItem);
    void addClass(string  className, ClassTableItem classTableItem);
    bool isClassExist(const string& className);
    bool isMethodExist(const string& className, const string& methodName);
    bool isFieldExist(const string& className, const string& methodName);
    ClassTableItem getClass(const string& className);
    static string getDirectory(string className);
};


#endif //COMPILER_CLASSTABLE_H
