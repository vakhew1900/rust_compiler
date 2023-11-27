//
// Created by T0mmy on 27.11.2023.
//

#ifndef COMPILER_VARTABLE_H
#define COMPILER_VARTABLE_H

#include "semantics/tools/datatype.h"

class ExprNode;
class VarTableItem {
public:
    VarTableItem(DataType dataType, bool isMut, bool isRef, bool isInit);

    VarTableItem(DataType dataType, bool isMut, bool isRef, bool isInit, ExprNode *blockExpr);

    DataType dataType;
    bool isMut = false;
    bool isRef = false; // является передачей по ссылке или нет
    bool isConst = false;
    bool isInit = false;
    ExprNode* blockExpr; // блок, с которым связан файл

    VarTableItem();
    VarTableItem(DataType dataType, bool isMut,bool isRef,bool isInit, bool isConst);
    VarTableItem(DataType dataType, bool isMut,bool isRef,bool isInit, bool isConst, ExprNode* blockExpr);
};

class VarTable {

    vector<VarTableItem> items;

};


#endif //COMPILER_VARTABLE_H
