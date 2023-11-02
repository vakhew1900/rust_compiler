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

// Expr from + - * / и тд
ExprNode* ExprNode::OperatorExpr(Type type, ExprNode* left, ExprNode* right){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = left;
    new_node->expr_right = right;
    return new_node;
}

ExprNode* ExprNode::PathCallExpr(Type type, string* name, ExprNode* expr){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Name = name;
    new_node->expr_left = expr;
    return new_node;
}

ExprNode* ExprNode::ExprFromBoolLiteral(Type type, bool value){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Bool = value;
    return new_node;
}

ExprNode* ExprNode::ExprFromIntLiteral(Type type, int value){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Int = value;
    return new_node;
}

ExprNode* ExprNode::ExprFromFloatLiteral(Type type, float value){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Float = value;
    return new_node;
}

ExprNode* ExprNode::ExprFromCharLiteral(Type type, char value){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Char = value;
    return new_node;
}

ExprNode* ExprNode::ExprFromStringLiteral(Type type, string* value){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->String = value;
    return new_node;
}

ExprNode* ExprNode::StaticMethod(Type type, ExprNode* expr, ExprListNode* expr_list){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->expr_list = expr_list;
    return new_node;
}

ExprNode* ExprNode::FieldListAccess(Type type, ExprNode* expr, StructFieldListNode* field_list){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->field_list = field_list;
    return new_node;
}

ExprNode* ExprNode::CallAccessExpr(Type type, string* name, ExprNode* expr, ExprListNode* expr_list){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Name = name;
    new_node->expr_left = expr;
    new_node->expr_list = expr_list;
    return new_node;
}

// StaticMethodExpr
ExprNode* ExprNode::StaticMethodExpr(Type type, string* name, string* parent_id, ExprListNode* expr_list){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Name = name;
    new_node->ParentID = parent_id;
    new_node->expr_list = expr_list;
    return new_node;
}

ExprNode* ExprNode::BlockExpr(Type type, ExprListNode* expr_list){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_list = expr_list;
    return new_node;
}

ExprNode* ExprNode::ArrExprFromList(Type type, ExprListNode* expr_list){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_list = expr_list;
    return new_node;
}

ExprNode* ExprNode::ArrExprAutoFill(Type type, ExprNode* first, ExprNode* second){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = first;
    new_node->expr_right = second;
    return new_node;
}

ExprNode* ExprNode::TupleExpr(Type type, ExprNode* expr, int value){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->Int = value;
    return new_node;
}

ExprNode* ExprNode::CycleExpr(Type type, ExprNode* condition, ExprNode* body, string* id){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->body = body;
    new_node->expr_left = condition;
    new_node->Name = id;
    return new_node;
}

ExprNode* ExprNode::RangeExpr(Type type, ExprNode* left, ExprNode* right){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = left;
    new_node->expr_right = right;
    return new_node;
}

ExprNode* ExprNode::IfExpr(Type type, ExprNode* condition, ExprNode* body, ExprNode* else_body){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = condition;
    new_node->body = body;
    new_node->else_body = else_body;
    return new_node;
}

ExprNode* ExprNode::AddIfBlock(Type type, ExprNode* expr, ExprNode* condition, ExprNode* body){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->expr_right = condition;
    new_node->body = body;
    return new_node;
}

ExprNode* ExprNode::StructExpr(Type type, string* name, ExprListNode* expr_list){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_list = expr_list;
    new_node->Name = name;
    return new_node;
}

ExprNode* ExprNode::ExprFromStructField(Type type, string* name, ExprNode* expr){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->Name = name;
    return new_node;
}

// expr list
ExprListNode::ExprListNode(ExprNode* expr){
    this->id = ++globId;
    this->exprs = new list <ExprNode*>{ expr };
}

ExprListNode::ExprListNode(ExprListNode* exprs_list){
    this->id = ++globId;
    this->exprs = exprs_list->exprs;
}

void ExprListNode::Append(ExprListNode *list, ExprNode *expr) {
    list->exprs->push_back(expr);
}

// STATEMENT FUNCTIONS
// ConstStmt
ConstStmtNode* ConstStmtNode::ConstStmt(string* name, TypeNode* type, ExprNode* expr){
    ConstStmtNode* new_node = new ConstStmtNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->name = name;
    new_node->expr = expr;
    return new_node;
}

// Trait
TraitNode::TraitNode(string* name, AssociatedItemListNode* items){
    this->id = ++globId;
    this->name=name;
    this->items=items;
}

// AssociatedItemNode
AssociatedItemNode::AssociatedItemNode(Visibility vis, FuncStmtNode* fn, ConstStmtNode* const_stmt){
    this->id = ++globId;
    this->visibility = vis;
    this->fn = fn;
    this->const_stmt = const_stmt;
}

//AssociatedItemList
AssociatedItemListNode::AssociatedItemListNode(AssociatedItemNode* item){
    this->id = ++globId;
    this->items = new list <AssociatedItemNode*>{ item };

}

AssociatedItemListNode::AssociatedItemListNode(AssociatedItemListNode* list){
    this->id = ++globId;
    this->items = list->items;
}

void AssociatedItemListNode::Append(AssociatedItemListNode* list, AssociatedItemNode* item) {
    list->items->push_back(item);
}

// --- toDot, toXml функции ---
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