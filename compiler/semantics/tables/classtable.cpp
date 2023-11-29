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
