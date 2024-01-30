//
// Created by T0mmy on 27.11.2023.
//

#include <string>
#include "vartable.h"

VarTableItem::VarTableItem() {

}


VarTableItem::VarTableItem(string name, DataType dataType, bool isMut, bool isRef, bool isInit, bool isConst) {
    this->id = name;
    this->dataType = dataType;
    this->isMut = isMut;
    this->isInit = isInit;
    this->isRef = isRef;
    this->isConst = isConst;
}

VarTableItem::VarTableItem(string name, DataType dataType, bool isMut, bool isRef, bool isInit, bool isConst,
                           ExprNode *blockExpr) {
    this->id = name;
    this->dataType = dataType;
    this->isMut = isMut;
    this->isInit = isInit;
    this->isRef = isRef;
    this->blockExpr = blockExpr;
    this->isConst = isConst;
}

VarTableItem::VarTableItem(string name, DataType dataType, bool isMut, bool isRef, bool isInit, bool isConst,
                           ExprNode *blockExpr, ExprNode *value) {
    this->id = name;
    this->dataType = dataType;
    this->isMut = isMut;
    this->isInit = isInit;
    this->isRef = isRef;
    this->isConst = isConst;
    this->blockExpr = blockExpr;
    this->value = value;
}

string VarTableItem::toString() {
    string res = "";

    res = this->id;
    if (isRef) {
        res += "&";
    }

    if (isMut) {
        res += "mut";
    }

    if (isConst) {
        res += "const";
    }

    res += " " + dataType.toString();

    return res;
}

bool VarTableItem::isEquals(const VarTableItem &varTableItem) {

    bool res = true;

    res = res && this->id == varTableItem.id;
    res = res && this->isMut == varTableItem.isMut;
    res = res && this->isConst == varTableItem.isConst;
    res = res && this->dataType.isEquals(varTableItem.dataType);
    res = res && this->isInit == varTableItem.isInit;
    res = res && this->value == varTableItem.value;

    return res;
}


string VarTable::toString() {

    string res = "";

    for (int i = 0; i < items.size(); i++) {
        res += to_string(i) + ": " + items[i].toString() + "\n";
    }
    return res;
}

bool VarTable::isExist(const string &varName) {
    bool res = false;

    for (auto elem: this->items) {
        res = res || elem.id == varName;
    }
    return res;
}

bool VarTable::isExist(const string &varName, const ExprNode* blockExpr) {
    bool res = false;

    for (auto i = items.rbegin(); i != items.rend(); ++i) {
        res = res || (i->id == varName &&  i->blockExpr == blockExpr);
        bool f = i->id == varName;
        bool f2 = i->blockExpr == blockExpr;
        "fffffff";
    }
    return res;
}

bool VarTable::isEquals(const VarTable &varTable) {

    bool res = true;
    res = res && this->items.size() == varTable.items.size();
    if (res == false) {
        return res;
    }
    for(int i = 0; i < varTable.items.size(); i++){
        //TODO пофиксить мэйби костыль
        res = res && (this->items[i].isEquals(varTable.items[i]) || (items[i].id == SELF_PARAM &&  varTable.items[i].id == SELF_PARAM));
    }
    return res;
}

VarTableItem VarTable::getVar(int varNum) {
    if (items.size() <= varNum || varNum < 0)
    {
        throw Exception(Exception::NOT_EXIST, "param not exist in method ");

    }

    return items[varNum];
}

const string VarTable::SELF_PARAM = "self";

int VarTable::getVarNumber(const string &varName, const ExprNode *blockExpr) {

    int cnt = items.size() - 1;
    for (auto i = items.rbegin(); i != items.rend(); ++i) {
        if (i->id == varName &&  i->blockExpr == blockExpr){
            return cnt;
        }
        cnt--;
    }
    return -1;
}

size_t VarTable::size() const {
    return items.size();
}
