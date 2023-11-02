//
// Created by arsen on 27.10.2023.
//
#include "classesnodes.h"
int globId = 0;

ProgramNode::ProgramNode(ItemListNode *item_list) {
    this->id = ++globId;
    this->item_list = item_list;
}

TypeNode::TypeNode(Type type) {
    this->id = ++globId;
    this->type = type;
}

TypeNode::TypeNode(Type type, TypeNode* type_node, ExprNode* expr) {
    this->id = ++globId;
    if(type_node->typeArr != NULL){
        this->type = type;
        this->typeArr = type_node;
    }
    this->exprArr = expr;
}


// --- toDot, toXml ---
string* ProgramNode::toDot(){

}

string* ProgramNode::toXml(){

}

string* TypeNode::toDot(){

}

string* TypeNode::toXml(){

}

string* ExprNode::toDot(){

}

string* ExprNode::toXml(){

}

string* ExprListNode::toDot(){

}

string* ExprListNode::toXml(){

}

string* StmtNode::toDot(){

}

string* StmtNode::toXml(){

}

string* StmtListNode::toDot(){

}

string* StmtListNode::toXml(){

}

string* LetStmtNode::toDot(){

}

string* LetStmtNode::toXml(){

}

string* ItemNode::toDot(){

}

string* ItemNode::toXml(){

}

string* ItemListNode::toDot(){

}

string* ItemListNode::toXml(){

}

string* ModuleStmtNode::toDot(){

}

string* ModuleStmtNode::toXml(){

}

string* StructStructNode::toDot(){

}

string* StructStructNode::toXml(){

}

string* StructFieldNode::toDot(){

}

string* StructFieldNode::toXml(){

}

string* StructFieldListNode::toDot(){

}

string* StructFieldListNode::toXml(){

}

string* EnumStmtNode::toXml(){

}

string* EnumStmtNode::toDot(){

}

string* EnumItemNode::toXml(){

}

string* EnumItemNode::toDot(){

}

string* EnumItemListNode::toXml(){

}

string* EnumItemListNode::toDot(){

}

string* FuncStmtNode::toXml(){

}

string* FuncStmtNode::toDot(){

}

string* FuncParamNode::toDot(){

}

string* FuncParamNode::toXml(){

}

string* FuncParamListNode::toDot(){

}

string* FuncParamListNode::toXml(){

}

string* ConstStmtNode::toXml(){

}

string* ConstStmtNode::toDot(){

}

string* AssociatedItemNode::toDot(){

}

string* AssociatedItemNode::toXml(){

}

string* TraitNode::toDot(){

}

string* TraitNode::toXml(){

}

string* AssociatedItemListNode::toDot(){

}

string* AssociatedItemListNode::toXml(){

}

string* ImplStmtNode::toDot(){

}

string* ImplStmtNode::toXml(){

}