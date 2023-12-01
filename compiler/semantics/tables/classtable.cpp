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

    if(parentName.size())
    {
        res += "parent: " + parentName;
    }

    res += "\nfieldTable:" + fieldTable.toString();
    res += "methodTable" + fieldTable.toString();

    return res;
}

bool ClassTableItem::isHaveParent() {
    return !this->parentName.empty();
}


string ClassTable::toString() {
    string res;

    for(auto  elem : items)
    {
        string tmp = elem.first + " " + elem.second.toString();
    }

    return res;
}

ClassTable* ClassTable::_instanse = NULL;

ClassTable *ClassTable::Instance() {
    if(_instanse == NULL)
    {
        _instanse = new ClassTable();
    }

    return _instanse;
}

ClassTable::ClassTable() {

}

void ClassTable::addMethod(string className, string methodName, MethodTableItem methodTableItem) {
    this->items[className].methodTable.items[methodName] = methodTableItem;
}

void ClassTable::addField(string className, string fieldName, FieldTableItem fieldTableItem) {
    this->items[className].fieldTable.items[fieldName] = fieldTableItem;
}

void ClassTable::addClass(string className, ClassTableItem classTableItem) {
    this->items[className] = classTableItem;
}

bool ClassTable::isClassExist(const string& className) {
    return this->items.find(className) == this->items.end();
}

bool ClassTable::isMethodExist(const std::string& className, const std::string& methodName) {
    return this->items[className].methodTable.items.find(methodName) ==this->items[className].methodTable.items.end();
}

bool ClassTable::isFieldExist(const string& className, const string& fieldName) {
    return this->items[className].fieldTable.items.find(fieldName) ==this->items[className].fieldTable.items.end();
}

ClassTableItem ClassTable::getClass(const string &className) {
    return this->items[className];
}


