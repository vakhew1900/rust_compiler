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

ExprNode* ExprNode::FieldListAccess(Type type, ExprNode* expr, ExprListNode* field_list){
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

ExprNode* ExprNode::IfExpr(Type type, ExprNode* condition, ExprNode* body){
    ExprNode* new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;

    ExprNode* if_node = new ExprNode();
    if_node->expr_left = condition;
    if_node->body = body;

    new_node->ifList = new list<ExprNode*> {if_node};

    return new_node;
}

ExprNode* ExprNode::AddIfBlock(ExprNode* ifExpr, ExprNode* someIfExpr){
    ifExpr->ifList->push_back(someIfExpr);
    return ifExpr;
}

ExprNode* ExprNode::AddElseBlock(ExprNode* ifExpr, ExprNode* else_body){
    ifExpr->else_body = else_body;
    return else_body;
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

ExprListNode* ExprListNode::Append(ExprListNode *list, ExprNode *expr) {
    list->exprs->push_back(expr);
    return list;
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

AssociatedItemListNode* AssociatedItemListNode::Append(AssociatedItemListNode* list, AssociatedItemNode* item) {
    list->items->push_back(item);
    return list;
}

//ImplNode
ImplStmtNode::ImplStmtNode(Type impl_type, TypeNode* type, string* name, AssociatedItemListNode* list){
    this->id = ++globId;
    this->impl_type = impl_type;
    this->type = type;
    this->name = name;
    this->items = list;
}

//Struct
StructStructNode::StructStructNode(string* name, StructFieldListNode* items){
    this->id = ++globId;
    this->name = name;
    this->items = items;
}

StructFieldNode::StructFieldNode(string* name, TypeNode* type, Visibility visibility){
    this->id = ++globId;
    this->name = name;
    this->type = type;
    this->visibility = visibility;
}

StructFieldListNode::StructFieldListNode(StructFieldNode *item){
    this->id = ++globId;
    this->items = new list <StructFieldNode*>{ item };
}

StructFieldListNode::StructFieldListNode(StructFieldListNode *list){
    this->id = ++globId;
    this->items = list->items;
}

StructFieldListNode* StructFieldListNode::Append(StructFieldListNode *list, StructFieldNode* item) {
    list->items->push_back(item);
    return list;
}

//Function
FuncStmtNode::FuncStmtNode(string* name, TypeNode* returnType, FuncParamListNode* params, ExprNode* body){
    this->id = ++globId;
    this->name = name;

    if(returnType == NULL){
        TypeNode* new_type_node = new TypeNode(TypeNode::emptyType_);
        new_type_node->id = ++globId;
        this->returnType=new_type_node;
    } else{
        this->returnType=returnType;
    }
    this->params=params;
    this->body=body;
}

FuncParamNode::FuncParamNode(string* name, TypeNode* type, Type param_type){
    this->id = ++globId;
    this->name = name;
    this->type = type;
    this->param_type = param_type;
}

FuncParamListNode::FuncParamListNode(FuncParamNode *item){
    this->id = ++globId;
    this->items = new list <FuncParamNode*>{ item };
}

FuncParamListNode::FuncParamListNode(FuncParamListNode *list){
    this->id = ++globId;
    this->items = list->items;
}

FuncParamListNode* FuncParamListNode::FunctionParamsFinal(Type func_type, FuncParamListNode *list){
    if(list == NULL){
        FuncParamListNode* new_node = new FuncParamListNode(list);
        new_node->id = ++globId;
        new_node->func_type = func_type;
        return new_node;
    }else{
        list->func_type = func_type;
        return list;
    }
}

FuncParamListNode* FuncParamListNode::Append(FuncParamListNode *list, FuncParamNode* item) {
    list->items->push_back(item);
    return list;
}

// Enum
EnumStmtNode::EnumStmtNode(string* name, EnumItemListNode* items){
    this->id = ++globId;
    this->name = name;
    this->items=items;
}

EnumItemNode::EnumItemNode(string* name, Visibility visibility, StructFieldListNode* struct_list, ExprNode* expr){
    this->id = ++globId;
    this->name = name;
    this-> expr = expr;
    this-> struct_list = struct_list;
    this->visibility=visibility;
}

EnumItemListNode::EnumItemListNode(EnumItemNode *item){
    this->id = ++globId;
    this->items = new list <EnumItemNode*>{ item };
}

EnumItemListNode::EnumItemListNode(EnumItemListNode *list){
    this->id = ++globId;
    this->items = list->items;
}

EnumItemListNode* EnumItemListNode::Append(EnumItemListNode *list, EnumItemNode* item) {
    list->items->push_back(item);
    return list;
}

// ModuleStmt
ModuleStmtNode::ModuleStmtNode(Type type, string* name, EnumItemListNode* items){
    this->id = ++globId;
    this->type = type;
    this->name = name;
    this->items = items;
}

// Items (declarations)
ItemNode* ItemNode::DeclarationEnum(Visibility visibility, EnumStmtNode* node){
    ItemNode* new_node = new ItemNode();
    new_node->id = ++globId;
    new_node->type = enum_;
    new_node->visibility=visibility;
    new_node->enum_item=node;

    Visibility current_vis = visibility;
    if(visibility != pub){
        current_vis = self;
    }

    if(node->items!=NULL){
        for(auto iter = node->items->items->begin(); iter != node->items->items->end(); ++iter){
            if((*iter)->visibility == emptyVisibility){
                (*iter)->visibility = current_vis;
            }
        }
    }

    return new_node;
}

ItemNode* ItemNode::DeclarationFunction(Visibility visibility, FuncStmtNode* node){
    ItemNode* new_node = new ItemNode();
    new_node->id = ++globId;

    new_node->type=function_;
    new_node->visibility = visibility;
    new_node->function_item = node;
    return new_node;
}

ItemNode* ItemNode::DeclarationConst(Visibility visibility, ConstStmtNode* node){
    ItemNode* new_node = new ItemNode();
    new_node->id = ++globId;

    new_node->type=constStmt_;
    new_node->visibility = visibility;
    new_node->const_stmt_item = node;
    return new_node;
}

ItemNode* ItemNode::DeclarationStruct(Visibility visibility, StructStructNode* node){
    ItemNode* new_node = new ItemNode();
    new_node->id = ++globId;

    new_node->type=struct_;
    new_node->visibility = visibility;
    new_node->struct_item = node;
    return new_node;
}

ItemNode* ItemNode::DeclarationTrait(Visibility visibility, TraitNode* node){
    ItemNode* new_node = new ItemNode();
    new_node->id = ++globId;
    new_node->type=trait_;
    new_node->visibility = visibility;
    new_node->trait_item = node;

    Visibility currentVisibility = visibility;
    if (visibility != pub){
        currentVisibility = self;
    }

    if(node->items!=NULL){
        for(auto iter = node->items->items->begin(); iter != node->items->items->end(); ++iter){
            if((*iter)->visibility == emptyVisibility){
                (*iter)->visibility = currentVisibility;
            }
        }
    }

    return new_node;
}

ItemNode* ItemNode::DeclarationImpl(Visibility visibility, ImplStmtNode* node){
    ItemNode* new_node = new ItemNode();
    new_node->id = ++globId;

    new_node->type=impl_;
    new_node->visibility = visibility;
    new_node->impl_item = node;
    return new_node;
}

ItemNode* ItemNode::DeclarationModule(Visibility visibility, ModuleStmtNode* node){
    ItemNode* new_node = new ItemNode();
    new_node->id = ++globId;

    new_node->type=module_;
    new_node->visibility = visibility;
    new_node->module_item = node;
    return new_node;
}

ItemNode::ItemNode(Visibility visibility, ItemNode* node){
    this->id = ++globId;
    this->item_node = node;
    this->item_node->visibility = visibility;
}

// ItemListNode
ItemListNode::ItemListNode(ItemNode *item){
    this->id = ++globId;
    this->items = new list <ItemNode*>{ item };
}

ItemListNode::ItemListNode(ItemListNode *list){
    this->id = ++globId;
    this->items = list->items;
}

ItemListNode* ItemListNode::Append(ItemListNode *list, ItemNode* item) {
    list->items->push_back(item);
    return list;
}

// LetStmt
LetStmtNode::LetStmtNode(string* name, TypeNode* type, Type let_type, ExprNode* expr){
    this->id = ++globId;
    this->name = name;

    if(type == NULL){
        TypeNode* new_type_node = new TypeNode(TypeNode::emptyType_);
        new_type_node->id = ++globId;
        this->type = new_type_node;
    } else {
        this->type = type;
    }

    this->expr = expr;
    this->let_type = let_type;
}

//StmtListNode
StmtListNode::StmtListNode(StmtNode *item){
    this->id = ++globId;
    this->stmts = new list <StmtNode*>{ item };
}


StmtListNode* StmtListNode::Append(StmtListNode *list, StmtNode* item) {
    list->stmts->push_back(item);
    return list;
}

// StmtNode
StmtNode::StmtNode(Type type, ExprNode* expr_node, ItemNode* decl_node, LetStmtNode* let_node){
    this->id = ++globId;
    this->type = type;
    this->expr = expr_node;
    this->decl_stmt = decl_node;
    this->let_stmt = let_node;
}

StmtNode::StmtNode(Type type, StmtNode* stmt){
    this->id = ++globId;
    this->type = type;
    this->stmt= stmt;
}

// --- toDot, toXml функции ---
void ProgramNode::toDot(string &dot){

    dot = "digraph rustProgram {\n";

    for(auto item : *this->item_list->items)
    {
        createVertexDot(dot, this->id, "program");
        item->toDot(dot);
        connectVerticesDots(dot, this->id, this->item_list->id);
    }

    dot += "}\n";

}

void TypeNode::toDot(string &dot){


}

void ProgramNode::toXml(string &xml){

}

void TypeNode::toXml(string &xml){

}

void ExprNode::toDot(string &dot){

}

void ExprNode::toXml(string &xml){

}

void ExprListNode::toDot(string &dot){

}

void ExprListNode::toXml(string &xml){

}

void StmtNode::toDot(string &dot){

}

void StmtNode::toXml(string &xml){

}

void StmtListNode::toDot(string &dot){

}

void StmtListNode::toXml(string &xml){

}

void LetStmtNode::toDot(string &dot){

}

void LetStmtNode::toXml(string &xml){

}

void ItemNode::toDot(string &dot){

}

void ItemNode::toXml(string &xml){

}

void ItemListNode::toDot(string &dot){

}

void ItemListNode::toXml(string &xml){

}

void ModuleStmtNode::toDot(string &dot){

}

void ModuleStmtNode::toXml(string &xml){

}

void StructStructNode::toDot(string &dot){

}

void StructStructNode::toXml(string &xml){

}

void StructFieldNode::toDot(string &dot){

}

void StructFieldNode::toXml(string &xml){

}

void StructFieldListNode::toDot(string &dot){

}

void StructFieldListNode::toXml(string &xml){

}

void EnumStmtNode::toXml(string &xml){

}

void EnumStmtNode::toDot(string &dot){

}

void EnumItemNode::toXml(string &xml){

}

void EnumItemNode::toDot(string &dot){

}

void EnumItemListNode::toXml(string &xml){

}

void EnumItemListNode::toDot(string &dot){

}

void FuncStmtNode::toXml(string &xml){

}

void FuncStmtNode::toDot(string &dot){

}

void FuncParamNode::toDot(string &dot){

}

void FuncParamNode::toXml(string &xml){

}

void FuncParamListNode::toDot(string &dot){

}

void FuncParamListNode::toXml(string &xml){

}

void ConstStmtNode::toXml(string &xml){

}

void ConstStmtNode::toDot(string &dot){

}

void AssociatedItemNode::toDot(string &dot){

}

void AssociatedItemNode::toXml(string &xml){

}

void TraitNode::toDot(string &dot){

}

void TraitNode::toXml(string &xml){

}

void AssociatedItemListNode::toDot(string &dot){

}

void AssociatedItemListNode::toXml(string &xml){

}

void ImplStmtNode::toDot(string &dot){

}

void ImplStmtNode::toXml(string &xml){

}

void connectVerticesDots(int parentId, int childId, string &s) {

    string tmp = "id" + to_string(parentId) + " -> " + "id" + to_string(childId) + ";";
    s += tmp;
}

void createVertexDot(string &s, int id, string name, string type) {

    if(!type.empty()){
        type = "type="+type;
    }

    string tmp = to_string(id) + to_string(id) +
                " [label=\"" + name + type + "id="+ to_string(id) + "\"]";

    s += tmp;
}
