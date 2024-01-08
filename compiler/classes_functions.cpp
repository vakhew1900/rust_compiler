//
// Created by arsen on 27.10.2023.
//
#include "classesnodes.h"
#include "semantics/rtl/RTLContainer.h"

int globId = 0;
int loopCnt = 0;
vector<ExprNode *> blockExprList;
vector<DataType> returnTypes;
vector<DataType> breakTypes;

ProgramNode::ProgramNode(ItemListNode *item_list) {
    this->id = ++globId;
    this->item_list = item_list;
}

TypeNode::TypeNode(Type type) {
    this->id = ++globId;
    this->type = type;
}

TypeNode::TypeNode(Type type, TypeNode *type_node, ExprNode *expr) {
    this->id = ++globId;

    this->type = type;
    this->typeArr = type_node;

    this->exprArr = expr;
}

TypeNode::TypeNode(Type type, string *name) {
    this->id = ++globId;
    this->type = type;
    this->name = name;
}

TypeNode::TypeNode(Type type, ExprNode *pathCallExpr) {
    this->id = ++globId;
    this->type = type;
    this->pathCallExpr = pathCallExpr;
}

// Expr from + - * / и тд
ExprNode *ExprNode::OperatorExpr(Type type, ExprNode *left, ExprNode *right) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = left;
    new_node->expr_right = right;
    return new_node;
}

ExprNode *ExprNode::PathCallExpr(Type type, string *name, ExprNode *expr) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Name = name;
    new_node->expr_left = expr;
    return new_node;
}

ExprNode *ExprNode::ExprFromBoolLiteral(Type type, bool value) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Bool = value;
    return new_node;
}

ExprNode *ExprNode::ExprFromIntLiteral(Type type, int value) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Int = value;
    return new_node;
}

ExprNode *ExprNode::ExprFromFloatLiteral(Type type, float value) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Float = value;
    return new_node;
}

ExprNode *ExprNode::ExprFromCharLiteral(Type type, char value) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Char = value;
    return new_node;
}

ExprNode *ExprNode::ExprFromStringLiteral(Type type, string *value) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->String = value;
    return new_node;
}

ExprNode *ExprNode::StaticMethod(Type type, ExprNode *expr, ExprListNode *expr_list) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->expr_list = expr_list;
    return new_node;
}

ExprNode *ExprNode::FieldListAccess(Type type, ExprNode *expr, ExprListNode *field_list) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->field_list = field_list;
    return new_node;
}

ExprNode *ExprNode::CallAccessExpr(Type type, string *name, ExprNode *expr, ExprListNode *expr_list) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Name = name;
    new_node->expr_left = expr;
    new_node->expr_list = expr_list;
    return new_node;
}

// StaticMethodExpr
ExprNode *ExprNode::StaticMethodExpr(Type type, string *name, string *parent_id, ExprListNode *expr_list) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Name = name;
    new_node->ParentID = parent_id;
    new_node->expr_list = expr_list;
    return new_node;
}

ExprNode *ExprNode::BlockExpr(Type type, ExprNode *body, StmtListNode *stmt_list) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->body = body;
    new_node->stmt_list = stmt_list;
    return new_node;
}

ExprNode *ExprNode::ArrExprFromList(Type type, ExprListNode *expr_list) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_list = expr_list;
    return new_node;
}

ExprNode *ExprNode::ArrExprAutoFill(Type type, ExprNode *first, ExprNode *second) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = first;
    new_node->expr_right = second;
    return new_node;
}

ExprNode *ExprNode::TupleExpr(Type type, ExprNode *expr, int value) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->Int = value;
    return new_node;
}

ExprNode *ExprNode::CycleExpr(Type type, ExprNode *condition, ExprNode *body, string *id) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->body = body;
    new_node->expr_left = condition;
    new_node->Name = id;
    return new_node;
}

ExprNode *ExprNode::RangeExpr(Type type, ExprNode *left, ExprNode *right) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = left;
    new_node->expr_right = right;
    return new_node;
}

ExprNode *ExprNode::IfExpr(Type type, ExprNode *condition, ExprNode *body) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = condition;
    new_node->body = body;


    return new_node;
}

ExprNode *ExprNode::IfExprList(ExprNode *ifExpr) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = if_expr_list;
    new_node->ifList = new list<ExprNode *>{ifExpr};
    return new_node;
}

ExprNode *ExprNode::AddIfBlock(ExprNode *ifExpr, ExprNode *someIfExpr) {
    ifExpr->ifList->push_back(someIfExpr);
    return ifExpr;
}

ExprNode *ExprNode::AddElseBlock(ExprNode *ifExpr, ExprNode *else_body) {
    ifExpr->else_body = else_body;
    return ifExpr;
}

ExprNode *ExprNode::AsExpr(ExprNode *expr, TypeNode *typeNode) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = as;
    new_node->expr_left = expr;
    new_node->typeNode = typeNode;
    return new_node;
}

ExprNode *ExprNode::StructExpr(Type type, string *name, ExprListNode *expr_list) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_list = expr_list;
    new_node->Name = name;
    return new_node;
}

ExprNode *ExprNode::ExprFromStructField(Type type, string *name, ExprNode *expr) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->Name = name;
    return new_node;
}

// expr list
ExprListNode::ExprListNode(ExprNode *expr) {
    this->id = ++globId;
    this->exprs = new list<ExprNode *>{expr};
}

ExprListNode::ExprListNode(ExprListNode *exprs_list) {
    this->id = ++globId;
    this->exprs = exprs_list->exprs;
}

ExprListNode *ExprListNode::Append(ExprListNode *list, ExprNode *expr) {
    list->exprs->push_back(expr);
    return list;
}

// STATEMENT FUNCTIONS
// ConstStmt
ConstStmtNode *ConstStmtNode::ConstStmt(string *name, TypeNode *type, ExprNode *expr) {
    ConstStmtNode *new_node = new ConstStmtNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->name = name;
    new_node->expr = expr;
    return new_node;
}

// Trait
TraitNode::TraitNode(string *name, ItemListNode *items) {
    this->id = ++globId;
    this->name = name;
    this->items = items;
}

//ImplNode
ImplStmtNode::ImplStmtNode(Type impl_type, TypeNode *type, ExprNode *exprNode, ItemListNode *list) {
    this->id = ++globId;
    this->impl_type = impl_type;
    this->type = type;
    this->pathCallExpr = exprNode;
    this->items = list;
}

//Struct
StructStructNode::StructStructNode(string *name, StructFieldListNode *items) {
    this->id = ++globId;
    this->name = name;
    this->items = items;
}

StructFieldNode::StructFieldNode(string *name, TypeNode *type, Visibility visibility) {
    this->id = ++globId;
    this->name = name;
    this->type = type;
    this->visibility = visibility;
}

StructFieldListNode::StructFieldListNode(StructFieldNode *item) {
    this->id = ++globId;
    this->items = new list<StructFieldNode *>{item};
}

StructFieldListNode::StructFieldListNode(StructFieldListNode *list) {
    this->id = ++globId;

    if (list != NULL) {
        this->items = list->items;
    } else {
        this->items = new std::list<StructFieldNode *>;
    }
}

StructFieldListNode *StructFieldListNode::Append(StructFieldListNode *list, StructFieldNode *item) {
    list->items->push_back(item);
    return list;
}

//Function
FuncStmtNode::FuncStmtNode(string *name, TypeNode *returnType, FuncParamListNode *params, ExprNode *body) {
    this->id = ++globId;
    this->name = name;
    if (returnType == NULL) {
        TypeNode *new_type_node = new TypeNode(TypeNode::emptyType_);
        new_type_node->id = ++globId;
        this->returnType = new_type_node;
    } else {
        this->returnType = returnType;
    }
    this->params = params;
    this->body = body;
}

FuncParamNode::FuncParamNode(string *name, TypeNode *type, Type param_type) {
    this->id = ++globId;
    this->name = name;
    this->type = type;
    this->param_type = param_type;
}

FuncParamListNode::FuncParamListNode(FuncParamNode *item) {
    this->id = ++globId;
    this->items = new list<FuncParamNode *>{item};
}

FuncParamListNode::FuncParamListNode(Type func_type, FuncParamNode *item) {
    this->id = ++globId;
    this->items = new list<FuncParamNode *>{item};
    this->func_type = func_type;
}

FuncParamListNode::FuncParamListNode(FuncParamListNode *list) {
    this->id = ++globId;
    if (list != NULL) {
        this->items = list->items;
    } else {
        this->items = new std::list<FuncParamNode *>;
    }
}

FuncParamListNode *FuncParamListNode::FunctionParamsFinal(Type func_type, FuncParamListNode *list) {
    if (list == NULL) {
        FuncParamListNode *new_node = new FuncParamListNode(list);
        new_node->id = ++globId;
        new_node->func_type = func_type;
        return new_node;
    } else {
        list->func_type = func_type;
        return list;
    }
}

FuncParamListNode *FuncParamListNode::Append(FuncParamListNode *list, FuncParamNode *item) {
    list->items->push_back(item);
    return list;
}

// Enum
EnumStmtNode::EnumStmtNode(string *name, EnumItemListNode *items) {
    this->id = ++globId;
    this->name = name;
    this->items = items;
}

EnumItemNode::EnumItemNode(string *name, Visibility visibility, StructFieldListNode *struct_list, ExprNode *expr) {
    this->id = ++globId;
    this->name = name;
    this->expr = expr;
    this->struct_list = struct_list;
    this->visibility = visibility;
}

EnumItemListNode::EnumItemListNode(EnumItemNode *item) {
    this->id = ++globId;
    this->items = new list<EnumItemNode *>{item};
}

EnumItemListNode::EnumItemListNode(EnumItemListNode *list) {
    this->id = ++globId;

    if (list != NULL) {
        this->items = list->items;
    } else {
        this->items = new std::list<EnumItemNode *>;
    }
}

EnumItemListNode *EnumItemListNode::Append(EnumItemListNode *list, EnumItemNode *item) {
    list->items->push_back(item);
    return list;
}

// ModuleStmt
ModuleStmtNode::ModuleStmtNode(string *name, ItemListNode *items) {
    this->id = ++globId;
    this->name = name;
    this->items = items;
}

// Items (declarations)
ItemNode *ItemNode::DeclarationEnum(Visibility visibility, EnumStmtNode *node) {
    ItemNode *new_node = new ItemNode();
    new_node->id = ++globId;
    new_node->item_type = enum_;
    new_node->visibility = visibility;
    new_node->name = node->name;
    new_node->enumItems = node->items;

    Visibility current_vis = visibility;
    if (visibility != pub) {
        current_vis = self;
    }

    if (new_node->items != NULL) {
        for (auto iter = new_node->items->items->begin(); iter != new_node->items->items->end(); ++iter) {
            if ((*iter)->visibility == emptyVisibility) {
                (*iter)->visibility = current_vis;
            }
        }
    }

    return new_node;
}

ItemNode *ItemNode::DeclarationFunction(Visibility visibility, FuncStmtNode *node) {
    ItemNode *new_node = new ItemNode();
    new_node->id = ++globId;

    new_node->item_type = function_;
    new_node->visibility = visibility;

    new_node->name = node->name;
    new_node->params = node->params;
    new_node->returnType = node->returnType;
    new_node->body = node->body;

    return new_node;
}

ItemNode *ItemNode::DeclarationConst(Visibility visibility, ConstStmtNode *node) {
    ItemNode *new_node = new ItemNode();
    new_node->id = ++globId;

    new_node->item_type = constStmt_;
    new_node->visibility = visibility;

    new_node->name = node->name;
    new_node->expr = node->expr;
    new_node->type = node->type;


    return new_node;
}

ItemNode *ItemNode::DeclarationStruct(Visibility visibility, StructStructNode *node) {
    ItemNode *new_node = new ItemNode();
    new_node->id = ++globId;

    new_node->item_type = struct_;
    new_node->visibility = visibility;

    new_node->name = node->name;
    new_node->structItems = node->items;

    return new_node;
}

ItemNode *ItemNode::DeclarationTrait(Visibility visibility, TraitNode *node) {
    ItemNode *new_node = new ItemNode();
    new_node->id = ++globId;
    new_node->item_type = trait_;
    new_node->visibility = visibility;

    new_node->name = node->name;
    new_node->items = node->items;

    Visibility currentVisibility = visibility;
    if (visibility != pub) {
        currentVisibility = self;
    }

    if (new_node->items != NULL) {
        for (auto iter = new_node->items->items->begin(); iter != new_node->items->items->end(); ++iter) {
            if ((*iter)->visibility == emptyVisibility) {
                (*iter)->visibility = currentVisibility;
            }
        }
    }

    return new_node;
}

ItemNode *ItemNode::DeclarationImpl(Visibility visibility, ImplStmtNode *node) {
    ItemNode *new_node = new ItemNode();
    new_node->id = ++globId;

    new_node->impl_type = (node->impl_type == ImplStmtNode::inherent) ? inherent : trait;
    new_node->item_type = impl_;
    new_node->visibility = visibility;
    new_node->items = node->items;
    new_node->expr = node->pathCallExpr;
    new_node->type = node->type;
    return new_node;
}

ItemNode *ItemNode::DeclarationModule(Visibility visibility, ModuleStmtNode *node) {
    ItemNode *new_node = new ItemNode();
    new_node->id = ++globId;

    new_node->item_type = module_;
    new_node->visibility = visibility;

    new_node->name = node->name;
    new_node->items = node->items;

    return new_node;
}

ItemNode::ItemNode(Visibility visibility, ItemNode *node) {
    this->id = ++globId;
}

ItemNode *ItemNode::AddVisibility(Visibility visibility, ItemNode *itemNode) {
    itemNode->visibility = visibility;
    return itemNode;
}


// ItemListNode
ItemListNode::ItemListNode(ItemNode *item) {
    this->id = ++globId;
    this->items = new list<ItemNode *>{item};
}

ItemListNode::ItemListNode(ItemListNode *list) {
    this->id = ++globId;

    if (list != NULL) {
        this->items = list->items;
    } else {
        this->items = new std::list<ItemNode *>;
    }

}

ItemListNode *ItemListNode::Append(ItemListNode *list, ItemNode *item) {
    list->items->push_back(item);
    return list;
}

// LetStmt
LetStmtNode::LetStmtNode(string *name, TypeNode *type, Type let_type, ExprNode *expr) {
    this->id = ++globId;
    this->name = name;
    if (type == NULL) {
        TypeNode *new_type_node = new TypeNode(TypeNode::emptyType_);
        new_type_node->id = ++globId;
        this->type = new_type_node;
    } else {
        this->type = type;
    }

    this->expr = expr;
    this->let_type = let_type;
}

//StmtListNode
StmtListNode::StmtListNode(StmtNode *item) {
    this->id = ++globId;
    this->stmts = new list<StmtNode *>;

    if (item != NULL) {
        this->stmts->push_back(item);
    }
}


StmtListNode *StmtListNode::Append(StmtListNode *list, StmtNode *item) {

    if (item != NULL) {
        list->stmts->push_back(item);
    }

    return list;
}

// StmtNode
StmtNode::StmtNode(Type type, ExprNode *expr_node, ItemNode *decl_node, LetStmtNode *let_node) {
    this->id = ++globId;
    this->type = type;
    this->expr = expr_node;
    this->decl_stmt = decl_node;

    if (let_node != NULL) {
        this->let_type = (let_node->let_type == LetStmtNode::mut) ? mut : noMut;
        this->expr = let_node->expr;
        this->typeChild = let_node->type;
        this->name = let_node->name;
    }
}

StmtNode::StmtNode() {

}


StmtNode::StmtNode(Type type, StmtNode *stmt) {
    this->id = ++globId;
    this->type = type;
    this->stmt = stmt;
}

StmtNode *StmtNode::ConstStmtToStmt(ConstStmtNode *node) {
    StmtNode *new_node = new StmtNode();
    new_node->id = ++globId;
    new_node->type = const_;
    new_node->typeChild = node->type;
    new_node->expr = node->expr;
    new_node->name = node->name;
    return new_node;
}

// --- toDot, toXml функции ---
void ProgramNode::toDot(string &dot) {

    dot = "digraph rustProgram {\n";

    createVertexDot(dot, this->id, "program");
    if (this->item_list != NULL) {
        connectVerticesDots(dot, this->id, this->item_list->id);
        this->item_list->toDot(dot);
    }

    dot += "}\n";

}


void TypeNode::toDot(string &dot) {

    switch (this->type) {
        case TypeNode::emptyType_:
            createVertexDot(dot, this->id, "empty_type", "", "");
            break;

        case TypeNode::int_:
            createVertexDot(dot, this->id, "int_type", "", "");
            break;

        case TypeNode::char_:
            createVertexDot(dot, this->id, "char_type", "", "");
            break;

        case TypeNode::string_:
            createVertexDot(dot, this->id, "string_type", "", "");
            break;

        case TypeNode::float_:
            createVertexDot(dot, this->id, "float_type", "", "");
            break;

        case TypeNode::id_:

            createVertexDot(dot, this->id, "id_type", "", *this->name);
            break;

        case bool_:
            createVertexDot(dot, this->id, "bool_type", "", "");
            break;

        case TypeNode::array_:
            createVertexDot(dot, this->id, "array_type", "", "");
            this->typeArr->toDot(dot);
            connectVerticesDots(dot, this->id, this->typeArr->id);

            if (this->exprArr != NULL) {
                this->exprArr->toDot(dot);
                connectVerticesDots(dot, this->id, this->exprArr->id);
            }

            break;
        case path_call_expr_:
            createVertexDot(dot, this->id, "path_call_expr_", "", "");
            this->pathCallExpr->toDot(dot);
            connectVerticesDots(dot, this->id, this->pathCallExpr->id);
            break;
    }
}

void ExprNode::toDot(string &dot, const string &pos) {

    string type = "";
    string value = "";

    switch (this->type) {
        case int_lit:
            type = "int_lit";
            value = to_string(this->Int);
            break;

        case float_lit:
            type = "float_lit";
            value = to_string(this->Float);
            break;

        case char_lit:
            type = "char_lit";
            value = to_string(this->Char);
            break;

        case string_lit:
            type = "string_lit";
            value = *(this->String);
            break;

        case raw_string_lit:
            type = "raw_string_lit";
            value = *(this->RawString);
            break;

        case bool_lit:
            type = "bool_lit";
            value = to_string(this->Bool);
            break;

        case plus:
            type = "plus";
            break;

        case minus:
            type = "minus";
            break;

        case mul_expr:
            type = "mul_expr";
            break;

        case div_expr:
            type = "div_expr";
            break;

        case mod:
            type = "mod";
            break;

        case or_:
            type = "or";
            break;

        case and_:
            type = "and";
            break;

        case asign:
            type = "asign";
            break;

        case equal:
            type = "equal";
            break;

        case not_equal:
            type = "not_equal";
            break;

        case greater:
            type = "greater";
            break;

        case less:
            type = "less";
            break;

        case greater_equal:
            type = "greater_equal";
            break;

        case less_equal:
            type = "less_equal";
            break;

        case uminus:
            type = "uminus";
            break;

        case negotation:
            type = "negotation";
            break;

        case question:
            type = "question";
            break;

        case ustar:
            type = "ustar";
            break;

        case link:
            type = "link";
            break;

        case mut_link:
            type = "mut_link";
            break;
        case array_expr:
            type = "array_expr";
            break;

        case array_expr_auto_fill:
            type = "array_expr_auto_fill";
            break;

        case index_expr:
            type = "index_expr";
            break;

        case field_access_expr:
            type = "field_access_expr";
            if (this->Name != NULL) value = *this->Name;
            break;

        case call_expr:
            type = "call_expr";
            if (this->Name != NULL) value = *this->Name;
            break;

        case method_expr:
            type = "method_expr";
            if (this->Name != NULL) value = *this->Name;
            break;

        case continue_expr:
            type = "continue_expr";
            break;

        case break_expr:
            type = "break_expr";
            break;

        case range_right:
            type = "range_right";
            break;

        case range_left:
            type = "range_left";
            break;

        case return_expr:
            type = "return_expr";
            break;

        case id_:
            type = "id_";
            value = *(this->Name);
            break;

        case self_expr:
            type = "self_expr";
            break;

        case if_expr:
            type = "if_expr";
            break;

        case if_expr_list:
            type = "if_expr_list";
            break;

        case loop_expr:
            type = "loop_expr";
            break;

        case loop_while:
            type = "loop_while";
            break;

        case block_expr:
            type = "block_expr";
            break;

        case struct_expr:
            type = "struct_expr";
            break;

        case struct_field_expr:
            type = "struct_field_expr";
            break;

        case static_method:
            type = "static_method";
            if (this->Name != NULL) value = *this->Name;
            break;

        case struct_creation:
            type = "struct_creation";
            if (this->Name != NULL) value = *this->Name;
            break;

        case tuple_expr:
            type = "tuple_expr";
            break;

        case super_expr:
            type = "super_expr";
            break;

        case path_call_expr:
            type = "path_call_expr";
            if (this->Name != NULL) value = *this->Name;
            break;

        case range_expr:
            type = "range_expr";
            break;

        case loop_for:
            type = "loop_for";
            break;

        case add_if_block:
            type = "add_if_block";
            break;
        case break_with_val_expr:
            type = "break_with_val_expr";
            break;
        case as:
            type = "as";
            break;
        case undefined:
            type = varName(undefined);
            break;
        case field_call:
            type = varName(field_call);
            break;
        case method_call:
            type = varName(method_call);
            break;
        case arr_asign:
            type = varName(arr_asign);
            break;
        case point_assign:
            type = varName(point_assign);
            break;
        case del_object:
            type = varName(del_object);
            break;
        case crate_expr:
            type = varName(crate_expr);
            break;
    }

    if (this->id == 3) {
        int x;
    }
    createVertexDot(dot, this->id, "expr", type, value, "", pos);

    if (this->expr_left != NULL) {
        connectVerticesDots(dot, this->id, this->expr_left->id);
        this->expr_left->toDot(dot, "expr_left");
    }

    if (this->expr_middle != NULL) {
        connectVerticesDots(dot, this->id, this->expr_middle->id);
        this->expr_middle->toDot(dot, "expr_middle");
    }

    if (this->expr_right != NULL) {
        connectVerticesDots(dot, this->id, this->expr_right->id);
        this->expr_right->toDot(dot, "expr_right");
    }

    if (this->expr_list != NULL) {
        connectVerticesDots(dot, this->id, this->expr_list->id);
        this->expr_list->toDot(dot);
    }

    if (this->body != NULL) {
        connectVerticesDots(dot, this->id, this->body->id);
        this->body->toDot(dot, "body");
    }

    if (this->field_list != NULL) {
        connectVerticesDots(dot, this->id, this->field_list->id);
        this->field_list->toDot(dot, "field_list");
    }

    if (this->stmt_list != NULL) {
        connectVerticesDots(dot, this->id, this->stmt_list->id);
        this->stmt_list->toDot(dot);
    }

    if (this->ifList != NULL) {

        int ifCount = 1;

        for (auto elem: *this->ifList) {
            connectVerticesDots(dot, this->id, elem->id);
            elem->toDot(dot, "condition" + to_string(ifCount++));
        }
    }

    if (this->else_body != NULL) {
        connectVerticesDots(dot, this->id, this->else_body->id);
        this->else_body->toDot(dot, "else_body");
    }

    if (this->deleteExprList != NULL && this->deleteExprList->exprs != NULL) {
        for (auto elem: *this->deleteExprList->exprs) {
            elem->toDot(dot, "delete_elem");
        }
    }

    if (this->typeNode != NULL) {
        connectVerticesDots(dot, this->id, this->typeNode->id);
        this->typeNode->toDot(dot);
    }
}

void ExprListNode::toDot(string &dot, const string &type) {

    createVertexDot(dot, this->id, "expr_list", type);

    for (auto elem: *this->exprs) {
        int exprNum = 1;
        connectVerticesDots(dot, this->id, elem->id);
        elem->toDot(dot, "condition" + to_string(exprNum++));
    }
}

void StmtNode::toDot(string &dot) {


    string type = "";
    string value = "";
    switch (this->type) {

        case semicolon:
            type = "semilicon";
            break;

        case expression:
            type = "expression";
            break;

        case exprstmt:
            type = "exprstmt";
            break;

        case let:
            type = "let ";
            type += (this->let_type == mut) ? "mut" : "noMut";
            value = *this->name;
            break;

        case const_:
            type = "const_ ";
            value = *this->name;
            break;
    }


    createVertexDot(dot, this->id, "stmt", type, value);

    if (this->expr != NULL) {
        connectVerticesDots(dot, this->id, this->expr->id);
        this->expr->toDot(dot, "expr");
    }

    if (this->let_stmt != NULL) {
        connectVerticesDots(dot, this->id, this->let_stmt->id);
        this->let_stmt->toDot(dot);
    }

    if (this->stmt != NULL) {
        connectVerticesDots(dot, this->id, this->stmt->id);
        this->stmt->toDot(dot);
    }

    if (this->typeChild != NULL) {
        connectVerticesDots(dot, this->id, this->typeChild->id);
        this->typeChild->toDot(dot);
    }
}


void StmtListNode::toDot(string &dot, const string &type) {

    createVertexDot(dot, this->id, "stmt_list", type);

    for (auto elem: *this->stmts) {
        int exprNum = 1;
        connectVerticesDots(dot, this->id, elem->id);
        elem->toDot(dot);
    }
}

void LetStmtNode::toDot(string &dot) {

    string type = "noMut";
//    string type = "";
    string value = "";

    if (this->name != NULL) {
        value = *this->name;
    }

    if (this->let_type == mut) {
        type = "mut";
    }

    createVertexDot(dot, this->id, "let_stmt", type, value);

    if (this->expr != NULL) {
        connectVerticesDots(dot, this->id, this->expr->id);
        this->expr->toDot(dot);
    }

    if (this->type != NULL) {
        connectVerticesDots(dot, this->id, this->type->id);
        this->type->toDot(dot);
    }
}

void ItemNode::toDot(string &dot) {

    string type = "";
    switch (this->item_type) {

        case enum_:
            type = "enum_";
            break;

        case function_:
            type = "function_";
            break;


        case constStmt_:
            type = "constStmt_";
            break;


        case struct_:
            type = "struct_";
            break;

        case trait_:
            type = "trait_";
            break;

        case impl_:
            type = "impl_ ";
            type += (impl_type == inherent) ? "inherit" : "trait";
            break;

        case module_:
            type = "module_";
            break;
    }

    string visibility = getVisibility(this->visibility);
    string value = "";
    if (this->name != NULL) value = *this->name;
    createVertexDot(dot, this->id, "item", type, value, visibility);

    if (this->type != NULL) {
        connectVerticesDots(dot, this->id, this->type->id);
        this->type->toDot(dot);
    }

    if (this->structItems != NULL) {
        connectVerticesDots(dot, this->id, this->structItems->id);
        this->structItems->toDot(dot);
    }

    if (this->enumItems != NULL) {
        connectVerticesDots(dot, this->id, this->enumItems->id);
        this->enumItems->toDot(dot);
    }

    if (this->items != NULL) {
        connectVerticesDots(dot, this->id, this->items->id);
        this->items->toDot(dot);
    }

    if (this->expr != NULL) {
        connectVerticesDots(dot, this->id, this->expr->id);
        this->expr->toDot(dot);
    }


    if (this->returnType != NULL) {
        connectVerticesDots(dot, this->id, this->returnType->id);
        this->returnType->toDot(dot);
    }


    if (this->params != NULL) {
        connectVerticesDots(dot, this->id, this->params->id);
        this->params->toDot(dot);
    }


    if (this->body != NULL) {
        connectVerticesDots(dot, this->id, this->body->id);
        this->body->toDot(dot);
    }
}

void ItemListNode::toDot(string &dot) {

    createVertexDot(dot, this->id, "item_list");

    for (auto elem: *this->items) {
        int exprNum = 1;
        connectVerticesDots(dot, this->id, elem->id);
        elem->toDot(dot);
    }
}

void ModuleStmtNode::toDot(string &dot) {

    string type = "";
    createVertexDot(dot, this->id, "module_stmt", type);

    if (this->items != NULL) {
        connectVerticesDots(dot, this->id, this->items->id);
        this->items->toDot(dot);
    }
}

void StructStructNode::toDot(string &dot) {

    createVertexDot(dot, this->id, "struct_struct", "", *name);

    if (this->items != NULL) {
        connectVerticesDots(dot, this->id, this->items->id);
        this->items->toDot(dot);
    }
}

void StructFieldNode::toDot(string &dot) {

    string visibility = getVisibility(this->visibility);

    createVertexDot(dot, this->id, "struct_field", "", *name, visibility);

    connectVerticesDots(dot, this->id, this->type->id);
    this->type->toDot(dot);
}

void StructFieldListNode::toDot(string &dot) {

    createVertexDot(dot, this->id, "struct_field_list");

    for (auto elem: *this->items) {
        int structFieldNum = 1;
        connectVerticesDots(dot, this->id, elem->id);
        elem->toDot(dot);
    }
}

void EnumStmtNode::toDot(string &dot) {

    createVertexDot(dot, this->id, "enum_stmt", "", *name);

    if (this->items != NULL) {
        connectVerticesDots(dot, this->id, this->items->id);
        this->items->toDot(dot);
    }

}

void EnumItemNode::toDot(string &dot) {

    createVertexDot(dot, this->id, *this->name, "enum_item");

    if (this->expr != NULL) {
        connectVerticesDots(dot, this->id, this->expr->id);
        this->expr->toDot(dot);
    }

    if (this->struct_list != NULL) {
        connectVerticesDots(dot, this->id, this->struct_list->id);
        this->struct_list->toDot(dot);
    }

}

void EnumItemListNode::toDot(string &dot) {

    createVertexDot(dot, this->id, "enum_item_list");

    for (auto elem: *this->items) {
        int enumItemCnt = 1;
        connectVerticesDots(dot, this->id, elem->id);
        elem->toDot(dot);
    }
}

void FuncStmtNode::toDot(string &dot) {

    createVertexDot(dot, this->id, "func_stmt", "", *name);

    if (this->returnType != NULL) {
        connectVerticesDots(dot, this->id, this->returnType->id);
        this->returnType->toDot(dot);
    }

    if (this->body != NULL) {
        connectVerticesDots(dot, this->id, this->body->id);
        this->body->toDot(dot);
    }

    if (this->params != NULL) {
        connectVerticesDots(dot, this->id, this->params->id);
        this->params->toDot(dot);
    }
}

void FuncParamNode::toDot(string &dot) {

    string type = "";
    switch (this->param_type) {

        case mut:
            type = "mut_";
            break;

        case noMut:
            type = "noMut_";
            break;

        case mut_ref:
            type = "mut_ref_";
            break;

        case link:
            type = "link_";
            break;
    }

    createVertexDot(dot, this->id, "func_param", type, *name);

    if (this->type != NULL) {
        connectVerticesDots(dot, this->id, this->type->id);
        this->type->toDot(dot);
    }
}


void ConstStmtNode::toDot(string &dot) {

    createVertexDot(dot, this->id, "const_stmt", "", *name);

    if (this->type != NULL) {
        connectVerticesDots(dot, this->id, this->type->id);
        this->type->toDot(dot);
    }

    if (this->expr != NULL) {
        connectVerticesDots(dot, this->id, this->expr->id);
        this->expr->toDot(dot);
    }
}

void ImplStmtNode::toDot(string &dot) {

    string type = "";
    switch (this->impl_type) {
        case trait:
            type = "trait_";
            break;
        case inherent:
            type = "inherit_";
            break;
    }

    createVertexDot(dot, this->id, "impl_stmt", type);

    if (this->type != NULL) {
        connectVerticesDots(dot, this->id, this->type->id);
        this->type->toDot(dot);
    }

    if (this->items != NULL) {
        connectVerticesDots(dot, this->id, this->items->id);
        this->items->toDot(dot);
    }
}

void FuncParamListNode::toDot(string &dot) {

    string type = "";
    switch (this->func_type) {
        case self:
            type = "self";
            break;
        case self_ref:
            type = "self_ref";
            break;

        case associated:
            type = "associated";
            break;

        case mut_self_ref:
            type = "mut_self_ref";
            break;

        case static_:
            type = "static_";
            break;

    }

    createVertexDot(dot, this->id, "func_param_list", type);
    for (auto elem: *this->items) {
        int enumItemCnt = 1;
        connectVerticesDots(dot, this->id, elem->id);
        elem->toDot(dot);
    }
}

void TraitNode::toDot(string &dot) {

    createVertexDot(dot, this->id, "train", "", *this->name);

    if (this->items != NULL) {
        connectVerticesDots(dot, this->id, this->items->id);
        this->items->toDot(dot);
    }
}

ItemNode::ItemNode() {

}

void Node::connectVerticesDots(string &s, int parentId, int childId) {
    string tmp = "id" + to_string(parentId) + " -> " + "id" + to_string(childId) + ";\n";
    s += tmp;
}

void Node::createVertexDot(string &s, int id, string name, string type, string value, string visibility, string pos) {
    if (!type.empty()) {
        type = "type=" + type + " ";
    }

    if (!value.empty()) {
        value = "val=[" + value + "]";
    }

    if (!visibility.empty()) {
        visibility = "visib=" + visibility + " ";
    }
    if (!pos.empty()) {
        pos = "pos=" + pos + " ";
    }

    string tmp = "id" + to_string(id) +
                 " [label=\"name=" + name + " " + type + value + visibility + pos + "id=" + to_string(id) + " dtype=" +
                 this->dataType.toString() + "\"];\n";

    s += tmp;

}

string getVisibility(Visibility visibility) {

    string res = "";

    switch (visibility) {
        case pub:
            res = "pub";
            break;

        case self:
            res = "self";
            break;

        case super:
            res = "super";
            break;

        case emptyVisibility:
            res = "empty";
            break;
        case crate:
            break;
    }

    return res;
}


// ------------------------  GetAllItems ------------------------------------
void Node::getAllItems(string className) {

}


void ProgramNode::getAllItems(std::string className) {

    this->classTableItem = ClassTableItem();
    classTableItem.classType = ClassTableItem::mod_;
    ClassTable::Instance()->addClass(className + "/" + ClassTable::moduleClassName, classTableItem);
    try {
        if (item_list != NULL) {
            for (auto elem: *item_list->items) {
                if (elem->item_type == ItemNode::function_ || elem->item_type == ItemNode::constStmt_) {
                    elem->curClassName = className + "/" + ClassTable::moduleClassName;
                    elem->getAllItems(className + "/" + ClassTable::moduleClassName);
                } else {
                    elem->getAllItems(className);
                }
            }
        }

        this->addImpl(className, false);
        if (item_list != NULL) {

            for (auto elem: *item_list->items) {
                if (elem->item_type == ItemNode::function_ || elem->item_type == ItemNode::constStmt_)
                    elem->addDataTypeToDeclaration(className + "/" + ClassTable::moduleClassName);
                else
                    elem->addDataTypeToDeclaration(className);
            }
        }

        ClassTable::isCorrectTraitsImpl();
        ClassTable::isMainFunctionExist();
    }
    catch (Exception e) {
        cerr << e.getMessage() << "\n";
    }
}

void ItemNode::getAllItems(std::string className) {

    try {
        switch (item_type) {
            case function_:
                this->methodTableItem = MethodTableItem();
                if (this->body != NULL) this->methodTableItem.isHasBody = true;
                if (this->visibility == pub) this->methodTableItem.isPub = true;
                if (ClassTable::Instance()->getClass(className).classType != ClassTableItem::trait_ &&
                    this->methodTableItem.isHasBody == false) {
                    throw Exception(Exception::NOT_IMPLEMICATION, *this->name + " NOT_IMPLEMICATION");
                }

                if ((this->params->func_type == FuncParamListNode::self_ref
                     || this->params->func_type == FuncParamListNode::self ||
                     this->params->func_type == FuncParamListNode::mut_self_ref) &&
                    ClassTable::Instance()->getClass(className).classType == ClassTableItem::mod_) {
                    throw Exception(Exception::NOT_A_METHOD, "function " + *this->name + " NOT_A_METHOD");
                }

                if ((this->params->func_type == FuncParamListNode::self_ref
                     || this->params->func_type == FuncParamListNode::self)
                    || this->params->func_type == FuncParamListNode::mut_self_ref) {
                    this->methodTableItem.isStatic = false;

                    if (this->params->func_type == FuncParamListNode::self_ref) {
                        this->methodTableItem.isRefSelf = true;
                    }
                }

                ClassTable::Instance()->addMethod(className, *this->name, this->methodTableItem);
                break;
            case constStmt_:
                this->fieldTableItem = FieldTableItem();
                if (this->expr != NULL) this->fieldTableItem.isInit = true;
                if (this->visibility == pub) this->fieldTableItem.isPub = true;
                if (this->fieldTableItem.isInit == false &&
                    ClassTable::Instance()->getClass(className).classType != ClassTableItem::trait_) {
                    throw Exception(Exception::NOT_IMPLEMICATION, *this->name + " NOT_DEFINED");
                }

                fieldTableItem.isConst = true;
                ClassTable::Instance()->addField(className, *this->name, this->fieldTableItem);
                break;
            case trait_:
                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::trait_;
                if (this->visibility == pub) this->classTableItem.isPub = true;
                ClassTable::Instance()->addClass(className + "/" + *this->name, classTableItem);

                if (this->items != NULL) {
                    for (auto elem: *this->items->items) {
                        if (elem->visibility == pub) {
                            throw Exception(Exception::PUB_NOT_PERMITTED,
                                            "pub` not permitted here because it's implied :" + *this->name + " " +
                                            *elem->name);
                        }
                        elem->visibility = pub;
                        elem->curClassName = className + "/" + *this->name;
                        elem->getAllItems(className + "/" + *this->name);
                    }
                }

                break;
            case module_:
                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::mod_;
                if (this->visibility == pub) this->classTableItem.isPub = true;
                ClassTable::Instance()->addClass(className + "/" + *this->name + "/" + ClassTable::moduleClassName,
                                                 classTableItem);

                if (this->items != NULL) {
                    for (auto elem: *this->items->items) {
                        string str = (elem->item_type == function_ || elem->item_type == constStmt_)
                                     ? "/" + ClassTable::moduleClassName : "";

                        if (!str.empty()) {
                            elem->curClassName = this->className + "/" + *this->name + str;
                        }
                        elem->getAllItems(className + "/" + *this->name + str);
                    }
                }
                break;
            case enum_:
                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::enum_;
                this->curClassName = className + "/" + *this->name;
                if (this->visibility == pub) this->classTableItem.isPub = true;
                ClassTable::Instance()->addClass(className + "/" + *this->name, classTableItem);

                if (this->enumItems != NULL) {
                    for (auto elem: *this->enumItems->items) {
                        elem->curClassName = className + "/" + *this->name;
                        elem->getAllItems(className + "/" + *this->name);
                    }
                }

                break;
            case struct_:
                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::struct_;
                if (this->visibility == pub) this->classTableItem.isPub = true;
                ClassTable::Instance()->addClass(className + "/" + *this->name, classTableItem);
                this->curClassName = className + "/" + *this->name;
                if (this->structItems->items != NULL) {
                    for (auto elem: *this->structItems->items) {
                        elem->curClassName = className + "/" + *this->name;
                        elem->getAllItems(className + "/" + *this->name);
                    }
                }
                break;

            case impl_:
                break;
        }
    }
    catch (Exception e) {
        throw e;
    }
}


void EnumItemNode::getAllItems(std::string className) {
    this->fieldTableItem = FieldTableItem();
    this->fieldTableItem.isConst = true;
    if (this->visibility == pub) this->fieldTableItem.isPub = true;

    try {
        ClassTable::Instance()->addField(className, *this->name, fieldTableItem);
    }
    catch (Exception e) {
        throw e;
    }
}

void StructFieldNode::getAllItems(std::string className) {
    this->fieldTableItem = FieldTableItem();
    this->fieldTableItem.isConst = false;
    if (this->visibility == pub) this->fieldTableItem.isPub = true;

    try {
        ClassTable::Instance()->addField(className, *this->name, fieldTableItem);
    }
    catch (Exception e) {
        throw e;
    }
}

/* ------ addImpl ------------------------------------*/

void Node::addImpl(string className, bool isTrait) {

}

void ProgramNode::addImpl(string className, bool isTrait) {

    try {
        if (this->item_list != NULL) {
            for (auto elem: *item_list->items) {
                if (elem->item_type == ItemNode::module_ || elem->item_type == ItemNode::impl_)
                    elem->addImpl(className, false);
            }
        }
    }
    catch (Exception e) {
        throw e;
    }
}


void ItemNode::addImpl(string className, bool isTrait) {

    string implClassName = "";
    string traitClassName = "";
    try {
        switch (this->item_type) {
            case module_:
                if (this->items != NULL) {
                    for (auto elem: *items->items) {
                        if (elem->item_type == impl_ || elem->item_type == module_) {
                            elem->addImpl(className + "/" + *this->name, false);
                        }
                    }
                }
                break;

            case impl_:

                if (this->type->type != TypeNode::path_call_expr_) {
                    throw Exception(Exception::NOT_SUPPORT, "Impl not struct type NOT SUPPORT");
                }

                this->type->pathCallExpr->transformPathCallExpr(className, ExprNode::undefined, true);
                implClassName = this->type->pathCallExpr->className;
                if (!ClassTable::Instance()->isClassExist(implClassName)) {
                    throw Exception(Exception::NOT_EXIST, "Impl struct " + implClassName + " Not Exist");
                }

                if (this->impl_type == trait) {

                    this->expr->transformPathCallExpr(className, ExprNode::undefined, true);
                    traitClassName = this->expr->className;
                    if (!ClassTable::Instance()->isClassExist(traitClassName)) {
                        throw Exception(Exception::NOT_EXIST, "Trait struct in impl" + traitClassName + "Not Exist");
                    }

                    ClassTable::Instance()->addParent(implClassName, traitClassName);

                }

                if (this->items != NULL) {
                    for (auto elem: *items->items) {
                        if (this->impl_type == trait && elem->visibility == pub) {
                            throw Exception(Exception::PUB_NOT_PERMITTED,
                                            "pub` not permitted here because it's implied :" + implClassName + " " +
                                            *elem->name);
                        }
                        elem->curClassName = implClassName;
                        elem->addImpl(implClassName, this->impl_type == trait);
                    }
                }

                if (this->impl_type == trait) {
                    ClassTable::isCorrectChild(implClassName, traitClassName);
                }

                this->className = implClassName;
                this->curClassName = implClassName;
                break;
            case function_:
                this->methodTableItem = MethodTableItem();
                if (this->body != NULL) this->methodTableItem.isHasBody = true;
                if (this->visibility == pub) this->methodTableItem.isPub = true;

                if (ClassTable::Instance()->getClass(className).classType != ClassTableItem::trait_ &&
                    !this->methodTableItem.isHasBody) {
                    throw Exception(Exception::NOT_IMPLEMICATION, *this->name + " NOT_IMPLEMICATION");
                }

                if (isTrait &&
                    !ClassTable::Instance()->isMethodExist(ClassTable::Instance()->getClass(className).parentName,
                                                           *this->name)) {
                    throw Exception(Exception::NOT_EXIST, "Impl Error: method" + *this->name + "in parent trait");
                }

                if (isTrait) {
                    this->methodTableItem.isPub = ClassTable::Instance()->getMethod(
                            ClassTable::Instance()->getClass(className).parentName, *this->name).isPub;
                }

                if ((this->params->func_type == FuncParamListNode::self_ref
                     || this->params->func_type == FuncParamListNode::self)
                    || this->params->func_type == FuncParamListNode::mut_self_ref) {
                    this->methodTableItem.isStatic = false;

                    if (this->params->func_type == FuncParamListNode::self_ref) {
                        this->methodTableItem.isRefSelf = true;
                    }
                }

                this->className = className;
                ClassTable::Instance()->addMethod(className, *this->name, this->methodTableItem);

                break;
            case constStmt_:
                this->fieldTableItem = FieldTableItem();
                if (this->expr != NULL) this->fieldTableItem.isInit = true;
                if (this->visibility == pub) this->fieldTableItem.isPub = true;
                if (!this->fieldTableItem.isInit &&
                    ClassTable::Instance()->getClass(className).classType != ClassTableItem::trait_) {
                    throw Exception(Exception::NOT_IMPLEMICATION, *this->name + " NOT_DEFINED");
                }

                if (isTrait && !ClassTable::Instance()->
                        isFieldExist(ClassTable::Instance()->getClass(className).parentName, *this->name)) {
                    throw Exception(Exception::NOT_EXIST, "Impl Error: field " + className + " " + *this->name +
                                                          "  not exist in parent trait " +
                                                          ClassTable::Instance()->getClass(className).parentName);
                }

                if (isTrait) {
                    this->fieldTableItem.isPub = ClassTable::Instance()->getField(
                            ClassTable::Instance()->getClass(className).parentName, *this->name).isPub;
                }
                fieldTableItem.isConst = true;
                ClassTable::Instance()->addField(className, *this->name, this->fieldTableItem);
                break;

            case struct_:
            case enum_:
            case trait_:
                break;
        }
    }

    catch (Exception e) {
        throw e;
    }
}


DataType TypeNode::convertToDataType(const string &className) {
    DataType dataType = DataType();

    switch (this->type) {

        case emptyType_:
            dataType.type = DataType::undefined_;
            break;
        case int_:
            dataType.type = DataType::int_;
            break;
        case char_:
            dataType.type = DataType::char_;
            break;
        case string_:
            dataType.type = DataType::string_;
            break;
        case float_:
            dataType.type = DataType::float_;
            break;
        case bool_:
            dataType.type = DataType::bool_;
            break;
        case id_:
            dataType.type = DataType::class_;
            break;
        case array_:
            dataType.type = DataType::array_;
            {
                DataType innerDataType = this->typeArr->convertToDataType(className);
                this->exprArr->transform();
                dataType.arrType = innerDataType.arrType;

                if (exprArr->type != ExprNode::int_lit) {
                    throw Exception(Exception::INCORRECT_CONST, "not INT_LIT");
                }

                if (this->exprArr->Int <= 0) {
                    throw Exception(Exception::INCORRECT_ARR_LENGTH, "array length less than one");
                }

                if (innerDataType.type == DataType::array_) {
                    dataType.arrLength = innerDataType.arrLength;
                    dataType.arrLength.push_back(this->exprArr->Int);
                    dataType.arrDeep = innerDataType.arrDeep + 1;
                    dataType.arrType = innerDataType.arrType;
                } else {
                    dataType.arrLength.push_back(this->exprArr->Int);
                    dataType.arrDeep = 1;
                    dataType.arrType = innerDataType.type;
                    dataType.id = innerDataType.id;
                }
            }

            break;
        case path_call_expr_:
            dataType.type = DataType::class_;
            this->pathCallExpr->transformPathCallExpr(className, ExprNode::undefined, true);
            dataType.id = this->pathCallExpr->className;

            if (ClassTable::Instance()->getClass(dataType.id).classType == ClassTableItem::mod_) {
                throw Exception(Exception::UNEXPECTED, dataType.id + "is module and not a type");
            }
            break;
    }

    return dataType;
}

void Node::addDataTypeToDeclaration(const string &className) {

}

void ItemNode::addDataTypeToDeclaration(const string &className) {

    set<int> enumSt;
    switch (this->item_type) {

        case enum_:

            for (auto elem: *this->enumItems->items) {
                elem->addDataTypeToDeclaration(className + "/" + *this->name, enumSt);
            }
            this->curClassName = className + "/" + *this->name;


            break;
        case function_:
            this->methodTableItem.returnDataType = this->returnType->convertToDataType(className);
            if (this->methodTableItem.returnDataType.type == DataType::undefined_) {
                this->methodTableItem.returnDataType.type = DataType::void_;
            }


            if (this->params != NULL) {

                if (this->params->func_type == FuncParamListNode::self) {
                    VarTableItem varItem = VarTableItem(VarTable::SELF_PARAM, DataType::StructDataType(curClassName),
                                                        false, false, true, false, body);

                    this->methodTableItem.paramTable.items.push_back(varItem);
                }

                if (this->params->func_type == FuncParamListNode::self_ref) {
                    VarTableItem varItem = VarTableItem(VarTable::SELF_PARAM, DataType::StructDataType(curClassName),
                                                        false, true, true, false, body);

                    this->methodTableItem.paramTable.items.push_back(varItem);
                }

                if (this->params->func_type == FuncParamListNode::mut_self_ref) {
                    VarTableItem varItem = VarTableItem(VarTable::SELF_PARAM, DataType::StructDataType(curClassName),
                                                        true, true, true, false, body);

                    this->methodTableItem.paramTable.items.push_back(varItem);
                }

                for (auto elem: *this->params->items) {
                    elem->methodName = *this->name;
                    elem->addDataTypeToDeclaration(className);
                    elem->varTableItem.blockExpr = this->body;

                    if (this->methodTableItem.paramTable.isExist(*elem->name)) {
                        throw Exception(Exception::DEFINED_MULTIPLE,
                                        "Function Param " + *elem->name + " in function " + *this->name +
                                        " DEFINED_MULTIPLE");
                    }
                    this->methodTableItem.paramTable.items.push_back(elem->varTableItem);

                }
            }

            ClassTable::Instance()->updateMethod(className, *this->name, this->methodTableItem);
            break;
        case constStmt_:
            this->fieldTableItem.dataType = this->type->convertToDataType(className);
            this->expr->transformConst();
            this->fieldTableItem.value = this->expr;

            if (!fieldTableItem.dataType.isEquals(this->expr->dataType)) {
                throw Exception(Exception::INCORRECT_TYPE,
                                "Expected type for " + *this->name + " in " + className + ":" +
                                fieldTableItem.dataType.toString() + " Result: " + this->expr->dataType.toString());
            }

            ClassTable::Instance()->updateField(className, *this->name, this->fieldTableItem);
            break;
        case struct_:
            for (auto elem: *this->structItems->items) {
                elem->addDataTypeToDeclaration(className + "/" + *this->name);
            }

            this->curClassName = className + "/" + *this->name;
            break;
        case impl_:

            for (auto elem: *this->items->items) {
                elem->addDataTypeToDeclaration(this->className);
            }
            break;
        case module_:
            this->curClassName = className + "/" + *this->name + "/" + ClassTable::moduleClassName;
            if (this->items != NULL) {
                for (auto elem: *this->items->items) {
                    string str = (elem->item_type == function_ || elem->item_type == constStmt_)
                                 ? "/" + ClassTable::moduleClassName : "";

                    if (elem->item_type == function_ || elem->item_type == constStmt_) {
                        elem->curClassName = this->curClassName;
                    }
                    elem->addDataTypeToDeclaration(className + "/" + *this->name + str);
                }
            }

            break;
        case trait_:
            this->curClassName = className + "/" + *this->name;
            if (this->items != NULL) {
                for (auto elem: *this->items->items) {
                    elem->addDataTypeToDeclaration(className + "/" + *this->name);
                }
            }
            break;
    }
}


void EnumItemNode::addDataTypeToDeclaration(const string &className, set<int> &st) {
    if (this->expr == NULL && st.empty()) {
        this->expr = ExprNode::ExprFromIntLiteral(ExprNode::int_lit, 0);
    }

    if (this->expr == NULL) {
        this->expr = ExprNode::ExprFromIntLiteral(ExprNode::int_lit, *st.rbegin() + 1);
    }

    if (this->expr != NULL) {
        this->expr->transformConst();

        if (this->expr->type != ExprNode::int_lit) {
            throw Exception(Exception::NOT_CONST, "ENUM VALUE SHOULD BE INT LITERAL");
        }
    }

    if (this->expr->Int > 255 || this->expr->Int < 0) {
        throw Exception(Exception::INCORRECT_ENUM_VALUE, "ENUM VALUE SHOULD BE u8");
    }

    if (st.count(this->expr->Int)) {
        throw Exception(Exception::INCORRECT_ENUM_VALUE,
                        "INCORRECT_ENUM_VALUE: ENUM VALUE " + to_string(this->expr->Int) + " occurs twice in " +
                        className);
    }


    this->dataType = DataType(DataType::int_);

    st.insert(this->expr->Int);
    this->fieldTableItem.dataType = DataType::int_;
    this->fieldTableItem.value = this->expr;
    ClassTable::Instance()->updateField(className, *this->name, this->fieldTableItem);
}


void StructFieldNode::addDataTypeToDeclaration(const string &className) {
    this->fieldTableItem.dataType = this->type->convertToDataType(className);
    this->dataType = this->fieldTableItem.dataType;
    ClassTable::Instance()->updateField(className, *this->name, fieldTableItem);
}

void FuncParamNode::addDataTypeToDeclaration(const string &className) {
    this->varTableItem = VarTableItem();
    this->varTableItem.id = *this->name;
    this->varTableItem.dataType = this->type->convertToDataType(className);

    switch (this->param_type) {

        case noMut:
            break;
        case mut:
            this->varTableItem.isMut = true;
            break;
        case mut_ref:
            this->varTableItem.isMut = true;
            this->varTableItem.isRef = true;
            break;
        case link:
            this->varTableItem.isRef = true;
            break;
    }
}

void ExprNode::transformPathCallExpr(string className, ExprNode::Type type, bool isType) {
    ExprNode *cur = this;
    vector<string> namePath;

    while (cur != NULL && cur->type == ExprNode::path_call_expr) {
        namePath.push_back(*cur->Name);
        cur = cur->expr_left;
    }

    reverse(all(namePath));
    ///TODO доделать


    if (isType == false && namePath.size() == 0) {
        this->className = className;
        if (type == ExprNode::static_method) {
            this->methodName = *this->Name;
        } else {
            this->fieldName = *this->Name;
        }
        return;
    }

    if (type == ExprNode::static_method) {
        this->methodName = namePath.back();
        namePath.pop_back();
    } else if (isType == false) {
        this->fieldName = namePath.back();
        namePath.pop_back();
    }

    string res = "";
    switch (cur->type) {
        case ExprNode::id_:

            if (ClassTable::Instance()->isClassExist(className)) {
                res += ClassTable::getDirectory(className);
            } else {
                res += className;
            }
            res += +"/" + *cur->Name;

            break;
        case ExprNode::self_expr:
            ///TODO доделать

            /// пока реализовать случай вызова статика
            if (cur != this) {
                res = className;

                if (ClassTable::Instance()->isClassExist(className)) {
                    res = ClassTable::getDirectory(className);
                }
            } else {
                res = className;
            }

            break;
        case ExprNode::super_expr:
            /// TODO доделать

            /// пока реализовать случай вызова статика
            if (cur != this) {
                if (ClassTable::Instance()->isClassExist(className)) {
                    res = ClassTable::getDirectory(className);
                }
                res = ClassTable::getDirectory(res);
            } else {
                res = ClassTable::Instance()->getClass(className).parentName;
            }
            break;
        case ExprNode::crate_expr:
            res = ClassTable::globalClassName;
            break;
        default:
            break;
    }

    for (auto elem: namePath) {
        res += "/" + elem;
    }

    if (!ClassTable::Instance()->isClassExist(res)) {
        res += "/" + ClassTable::moduleClassName;
    }

    if (!ClassTable::Instance()->isClassExist(res)) {
        throw Exception(Exception::NOT_EXIST, res + "NOT_EXIST");
    }

    this->className = res;

}

bool ExprNode::isLiteral() {
    return this->type == ExprNode::int_lit || this->type == ExprNode::bool_lit ||
           this->type == ExprNode::char_lit || this->type == ExprNode::float_lit ||
           this->type == ExprNode::string_lit || this->type == ExprNode::raw_string_lit;
}

bool ExprNode::isSimpleType() {
    return isLiteral() && this->type != ExprNode::string_lit && this->type != ExprNode::raw_string_lit;
}

void ProgramNode::transform(bool isConvertedToConst) {

    string tmp = ClassTable::globalClassName + "/" + ClassTable::moduleClassName;
    this->curClassName = tmp;
    ClassTable::addClassToConstTable(tmp, tmp);
    if (this->item_list != NULL) {
        for (auto item: *this->item_list->items) {
            try {
                if (item->item_type == ItemNode::function_ || item->item_type == ItemNode::constStmt_) {
                    item->curClassName = this->curClassName;
                }
                item->transform(isConvertedToConst);

            }
            catch (Exception e) {
                cerr << e.getMessage() << endl;
            }
        }
    }

}

void ProgramNode::makeAllConversions() {
    RTLContainer();
    this->getAllItems(ClassTable::globalClassName);
    this->transform(true);
}

void ItemNode::transform(bool isConvertedToConst) {

    try {
        switch (this->item_type) {

            case function_: {
                returnTypes.clear();
                if (body != NULL) {

                    body->curClassName = curClassName;
                    body->curMethodName = *this->name;
                }

                if (*this->name == "selfFunc") {
                    "ffff";
                }

                vector<DataType> paramTypes;
                for (auto elem: ClassTable::Instance()->getMethod(curClassName, *this->name).paramTable.items) {
                    elem.blockExpr = body;
                    paramTypes.push_back(elem.dataType);
                    ClassTable::Instance()->addLocalParam(curClassName, *this->name, elem);
                }

                if (ClassTable::Instance()->getMethod(curClassName, *this->name).isStatic == false) {
                    paramTypes.erase(paramTypes.begin());
                }
                ClassTable::addMethodRefToConstTable(curClassName, curClassName, *this->name, paramTypes,
                                                     ClassTable::Instance()->getMethod(this->curClassName,
                                                                                       *this->name).returnDataType);

                blockExprList.push_back(body);
                if (this->body != NULL) {
                    this->body->transform(isConvertedToConst);
                    MethodTableItem methodTableItem = ClassTable::Instance()->getMethod(this->curClassName,
                                                                                        *this->name);
                    if (!this->body->dataType.isEquals(methodTableItem.returnDataType)) {
                        throw Exception(Exception::TYPE_ERROR,
                                        *this->name + "should return " + methodTableItem.returnDataType.toString() +
                                        "but result: " + body->dataType.toString());
                    }

                    returnTypes.push_back(methodTableItem.returnDataType);
                    if (!DataType::isEquals(returnTypes)) {
                        throw Exception(Exception::TYPE_ERROR,
                                        *this->name + "should return  " + methodTableItem.returnDataType.toString() +
                                        " but result is not");
                    }
                }

                returnTypes.clear();
                blockExprList.pop_back();
                if (blockExprList.size()) {
                    throw Exception(Exception::UNEXPECTED, "blockexpr не удалил(");
                }

                for (auto param: *this->params->items) {
                    try {
                        if (param->dataType.isClass()) {
                            if (!ClassTable::isHaveAccess(curClassName, param->dataType.id)) {
                                throw Exception(Exception::ACCESS_ERROR,
                                                *this->name + " has not access to " + param->dataType.id);
                            }

                            bool isPub = ClassTable::Instance()->getMethod(curClassName, *this->name).isPub;
                            if (isPub && !ClassTable::Instance()->getClass(param->dataType.id).isPub) {
                                throw Exception(Exception::PRIVATE_ERROR,
                                                *this->name + " has param  " + param->dataType.id + " is private");
                            }
                        }
                    }
                    catch (Exception e) {
                        throw e;
                    }
                }

                if (this->dataType.isClass()) {

                    if (!ClassTable::isHaveAccess(curClassName, dataType.id)) {
                        throw Exception(Exception::ACCESS_ERROR, *this->name + " has not access to " + dataType.id);
                    }

                }
            }
                break;
            case constStmt_:
                if (this->expr != NULL) {
                    this->expr->curClassName = curClassName;
                    // this->expr->curMethodName = curMethodName;
                    this->expr->transform(isConvertedToConst);
                }

                if (this->dataType.isClass()) {
                    if (ClassTable::isHaveAccess(curClassName, dataType.id)) {
                        throw Exception(Exception::ACCESS_ERROR, *this->name + " has not access to " + dataType.id);
                    }

                    if (!ClassTable::Instance()->getClass(dataType.id).isPub) {
                        throw Exception(Exception::PRIVATE_ERROR,
                                        *this->name + " is public but type " + dataType.id + " is private");
                    }
                }


                ClassTable::addFieldRefToConstTable(curClassName, curClassName, *this->name,
                                                    ClassTable::Instance()->getField(curClassName,
                                                                                     *this->name).dataType);
                break;
            case trait_:
            case impl_:
            case module_:
                if (items != NULL) {
                    for (auto elem: *this->items->items) {
                        elem->transform(isConvertedToConst);
                    }
                }
                break;
            case struct_: {
                vector<DataType> params;

                for (auto elem: *structItems->items) {
                    if (elem->dataType.isClass()) {

                        if (!ClassTable::isHaveAccess(curClassName, dataType.id)) {
                            throw Exception(Exception::ACCESS_ERROR, *this->name + " has not access to " + dataType.id);
                        }

                        bool isPubField = ClassTable::Instance()->getField(curClassName, *elem->name).isPub;
                        bool isPrivateType = !ClassTable::Instance()->getClass(elem->dataType.id).isPub;
                        if (isPubField && isPrivateType) {
                            throw Exception(Exception::PRIVATE_ERROR,
                                            *elem->name + " is public but type " + elem->dataType.id + " is private");
                        }
                    }

                    params.push_back(elem->dataType);
                    ClassTable::addFieldRefToConstTable(curClassName, curClassName, *elem->name, elem->dataType);

                }

                ClassTable::addMethodRefToConstTable(curClassName, curClassName, "<init>", params,
                                                     DataType(DataType::void_));

                break;
            }
            case enum_:

                for (auto elem: *this->enumItems->items) {
                    ClassTable::addFieldRefToConstTable(curClassName, curClassName, *elem->name, elem->dataType);
                    elem->expr->transform();
                }

                break;
        }
    }
    catch (Exception e) {
        blockExprList.clear();
        cerr << e.getMessage() << endl;
    }
}

void StmtListNode::transform(bool isConvertedToConst) {

    if (this->stmts != NULL) {
        for (auto elem: *this->stmts) {
            elem->curClassName = curClassName;
            elem->curMethodName = curMethodName;
            elem->transform(isConvertedToConst);
        }
    }
}

void StmtNode::transform(bool isConvertedToConst) {

    try {
        switch (this->type) {
            case exprstmt:
                this->expr->curClassName = curClassName;
                this->expr->curMethodName = curMethodName;
                this->expr->transform(isConvertedToConst);
                break;
            case let:
                this->varTableItem = VarTableItem();
                if (this->let_type == mut) {
                    this->varTableItem.isMut = mut;
                }
                varTableItem.id = *this->name;
                varTableItem.blockExpr = blockExprList.back();

                {
                    DataType arrDataType = DataType();

                    if (this->typeChild == NULL || this->typeChild->type == TypeNode::array_) {
                        arrDataType = this->typeChild->convertToDataType(curClassName).getArrDataType();
                    }

                    if (this->expr != NULL) {
                        this->expr->curClassName = curClassName;
                        this->expr->curMethodName = curMethodName;
                        this->expr->arrDataType = arrDataType;
                        this->expr->transform(isConvertedToConst);
                    }

                    if (this->typeChild == NULL || this->typeChild->type == TypeNode::emptyType_) {
                        varTableItem.dataType = expr->dataType;
                    } else {
                        varTableItem.dataType = this->typeChild->convertToDataType(curClassName);
                        if (!this->expr->dataType.isEquals(varTableItem.dataType)) {
                            throw Exception(Exception::INCORRECT_TYPE,
                                            "incorrect let" + varTableItem.id + "datatype. Expected: " +
                                            varTableItem.dataType.toString() +
                                            "result: " + this->expr->dataType.toString());
                        }
                    }
                }

                ClassTable::Instance()->addLocalParam(curClassName, curMethodName, this->varTableItem);
                break;
            case const_:
                this->varTableItem = VarTableItem();

                varTableItem.isConst = true;
                varTableItem.id = *this->name;

                if (this->expr == NULL) {
                    throw Exception(Exception::UNEXPECTED, "const " + *this->name + " must be initialized");
                }

                this->expr->curClassName = curClassName;
                this->expr->curMethodName = curMethodName;
                this->expr->transformConst();
                this->expr->transform();
                varTableItem.dataType = this->typeChild->convertToDataType(curClassName);

                if (!this->expr->dataType.isEquals(varTableItem.dataType)) {
                    throw Exception(Exception::INCORRECT_TYPE, "incorrect datatype");
                }

                varTableItem.blockExpr = blockExprList.back();
                ClassTable::Instance()->addLocalParam(curClassName, curMethodName, this->varTableItem);
                break;
            case semicolon:
            case expression:
                break;
        }
    }
    catch (Exception e) {
        cerr << e.getMessage() << "\n";
    }
}

void ExprNode::transform(bool isConvertedToConst) {

    switch (this->type) {

        case plus:
        case minus:
        case mul_expr:
        case div_expr:

            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);

            if (this->expr_left->isLiteral() && this->expr_right->isLiteral() && isConvertedToConst) {
                this->transformConst();
                this->transform();
            } else {
                if (!this->expr_left->dataType.isEquals(expr_right->dataType)) {
                    throw Exception(Exception::NOT_EQUAL_DATA_TYPE,
                                    "NOT EQUAL DATA_TYPE " + this->expr_left->dataType.toString() + " " +
                                    this->expr_right->dataType.toString());
                }

                if (this->expr_left->dataType.type != DataType::int_
                    && this->expr_left->dataType.type != DataType::float_) {
                    throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                    "datatype " + this->expr_left->dataType.toString() +
                                    " not supported maths operation");
                }

                this->dataType = this->expr_left->dataType;
            }
            break;
        case mod:

            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);

            if (!this->expr_left->dataType.isEquals(expr_right->dataType)) {
                throw Exception(Exception::NOT_EQUAL_DATA_TYPE,
                                "NOT EQUAL DATA_TYPE" + this->expr_left->dataType.toString() + " " +
                                this->expr_right->dataType.toString());
            }

            if (this->expr_left->dataType.type != DataType::int_) {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                "datatype " + this->expr_left->dataType.toString() +
                                " not supported operation mod");
            }

            this->dataType = this->expr_left->dataType;

            if (this->expr_left->isLiteral() && this->expr_right->isLiteral() && isConvertedToConst) {
                this->transformConst();
                this->transform();
            }

            break;

        case equal:
        case not_equal:
        case greater:
        case less:
        case greater_equal:
        case less_equal:

            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);


            if (!this->expr_left->dataType.isEquals(expr_right->dataType)) {
                throw Exception(Exception::NOT_EQUAL_DATA_TYPE,
                                "NOT EQUAL DATA_TYPE" + this->expr_left->dataType.toString() + " " +
                                this->expr_right->dataType.toString());
            }

            if (this->expr_left->dataType.type == DataType::array_
                || this->expr_left->dataType.type == DataType::class_) {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                "datatype " + this->expr_left->dataType.toString() +
                                " not supported comparison operation");
            }

            this->dataType = DataType(DataType::bool_);

            if (this->expr_left->isLiteral() && this->expr_right->isLiteral() && isConvertedToConst) {
                this->transformConst();
                this->transform();
            }

            break;

        case uminus:
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);
            //  this->expr_right->curMethodName = curMethodName;

            if (this->expr_left->dataType.type != DataType::float_
                && this->expr_left->dataType.type != DataType::int_) {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                "datatype " + this->expr_left->dataType.toString() +
                                " not supported uminus operation");
            }
            this->dataType = this->expr_left->dataType;

            if (this->expr_left->isLiteral()) {
                this->transformConst();
                this->transform();
            }

            break;

        case negotation:

            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);

            //   this->expr_right->curMethodName = curMethodName;

            if (this->expr_left->dataType.type != DataType::bool_) {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                "datatype " + this->expr_left->dataType.toString() +
                                " not supported uminus operation");
            }
            this->dataType = this->expr_left->dataType;

            if (this->expr_left->isLiteral()) {
                this->transformConst();
                this->transform();
            }

            break;

        case or_:
        case and_:
            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst && false);

            if (this->expr_left->isLiteral() && this->expr_right->isLiteral() && isConvertedToConst) {
                this->transformConst();
                this->transform();
            }

            if (!this->expr_left->dataType.isEquals(expr_right->dataType)) {
                throw Exception(Exception::NOT_EQUAL_DATA_TYPE,
                                "NOT EQUAL DATA_TYPE" + this->expr_left->dataType.toString() + " " +
                                this->expr_right->dataType.toString());
            }

            if (this->expr_left->dataType.type != DataType::bool_) {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                "datatype " + this->expr_left->dataType.toString() +
                                " not supported and/or operation");
            }

            this->dataType = this->expr_left->dataType;

            break;
        case asign:

            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);


            if (!this->expr_left->isVar()) {
                throw Exception(Exception::NOT_A_VAR, "left operand not a var");
            }

            if (!this->expr_left->dataType.isEquals(expr_right->dataType)) {
                throw Exception(Exception::NOT_EQUAL_DATA_TYPE,
                                "NOT EQUAL DATA_TYPE in asign: " + this->expr_left->dataType.toString() + " and " +
                                this->expr_right->dataType.toString());
            }

            //TODO добавить обработку констант
            if (this->expr_left->localVarNum != -1) { ///
                VarTableItem varTableItem = ClassTable::Instance()->getLocalVar(curClassName, curMethodName,
                                                                                this->expr_left->localVarNum);
                if (this->expr_left->isConst || this->expr_left->isMut == false) {
                    throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                    varTableItem.id + "is const and can`t supported asign operation");
                }
            } else if (!this->expr_left->fieldName.empty()) {
                FieldTableItem fieldTableItem = ClassTable::Instance()->getField(curClassName,
                                                                                 this->expr_left->fieldName);
                if (this->expr_left->isConst || this->expr_left->isMut == false) {
                    throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                    this->expr_left->fieldName + "is const and can`t supported asign operation");
                }
            }

            if (this->expr_left->isConst || this->expr_left->isMut == false) {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                *this->expr_left->Name + " is const and can`t supported asign operation");
            }

            this->dataType = DataType(DataType::void_);
            /// TODO добавить обработку для массива

            if (this->expr_left->type == index_expr) {
                this->type = arr_asign;
                this->expr_middle = this->expr_left->expr_right;
                this->expr_left->expr_right = NULL;
                this->expr_left = this->expr_left->expr_left;
            } else if (this->expr_left->type == field_access_expr) {
                this->type = point_assign;
                this->expr_middle = ExprNode::PathCallExpr(id_, this->expr_left->Name, NULL);
                this->expr_left->expr_right = NULL;
                this->expr_left = this->expr_left->expr_left;
            }


            break;
        case array_expr:

            if (this->expr_list != NULL) {
                for (auto elem: *expr_list->exprs) {
                    addMetaInfo(elem);
                    checkCancelExprNode(elem);
                    elem->transform(isConvertedToConst);
                }

                if (this->expr_list->exprs->size()) {

                    vector<DataType> arrTypes;
                    DataType firstElement = this->expr_list->exprs->front()->dataType;
                    if (firstElement.type != DataType::array_) {
                        for (auto elem: *this->expr_list->exprs) {
                            auto dataType = elem->dataType;

                            if (dataType.type != DataType::class_) {
                                if (!dataType.isEquals(firstElement)) {
                                    throw Exception(Exception::TYPE_ERROR,
                                                    "not correct types in array");
                                }
                            } else if (dataType.type == DataType::class_) {
                                if (!dataType.isEquals(firstElement)
                                    && (this->arrDataType.type != DataType::class_ ||
                                        !ClassTable::Instance()->isParent(this->dataType.id, this->arrDataType.id))) {
                                    throw Exception(Exception::TYPE_ERROR, "not correct types in array");
                                }
                            }


                        }


                        this->dataType = DataType();
                        this->dataType.type = DataType::array_;
                        this->dataType.arrDeep = 1;

                        if (firstElement.type != DataType::class_ || arrDataType.isUndefined()) {
                            this->dataType.addArrType(firstElement);
                        } else if (arrDataType.type != DataType::class_) {
                            throw Exception(Exception::TYPE_ERROR,
                                            "type error in array. Expected: " + arrDataType.toString() + "Result: " +
                                            firstElement.toString());
                        } else if (firstElement.isEquals(this->arrDataType)) {
                            this->dataType.addArrType(firstElement);
                        } else if (ClassTable::Instance()->isParent(firstElement.id, this->arrDataType.id)) {
                            this->dataType.addArrType(arrDataType);
                        } else {
                            throw Exception(Exception::TYPE_ERROR,
                                            "type error in array. Expected: " + arrDataType.toString() + "Result: " +
                                            firstElement.toString());
                        }

                    } else {

                        for (auto elem: *this->expr_list->exprs) {
                            if (!elem->dataType.isEquals(firstElement)) {
                                throw Exception(Exception::ARRAY_SIZE, "incorrect size inner arrays");
                            }
                            //TODO склеить два массива
                            arrTypes.insert(arrTypes.end(), all(elem->dataType.arrTypes));
                        }
                        this->dataType = firstElement;
                        this->dataType.arrDeep++;
                    }

                    this->dataType.arrLength.push_back(expr_list->exprs->size());
                    this->dataType.arrTypes = arrTypes;

                }
            }
            //TODO тут не забыть нафигачить провер очки
            break;

        case array_expr_auto_fill:

            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);

            if (this->expr_right->dataType.type != DataType::int_) {
                throw Exception(Exception::NOT_SUPPORT,
                                "array size expected i32, found " + this->expr_right->dataType.toString());
            }

            if (this->expr_left->type != int_lit) {
                if (this->expr_left->isConst == false) {
                    throw Exception(Exception::NOT_CONST, "array size must be constant");
                }

                if (this->expr_left->localVarNum != -1) {
                    VarTableItem varTableItem = ClassTable::Instance()->getLocalVar(curClassName, curMethodName,
                                                                                    this->expr_left->localVarNum);
                    this->expr_right = varTableItem.value;
                } else if (!this->expr_left->fieldName.empty()) {
                    FieldTableItem fieldTableItem = ClassTable::Instance()->getField(curClassName,
                                                                                     this->expr_left->fieldName);
                    this->expr_right = fieldTableItem.value;
                }

            }

            if (this->expr_right == NULL) {
                throw Exception(Exception::UNEXPECTED, "expr right is NULL. FUCK YEE");
            }

            {
                int array_size = this->expr_right->Int;

                for (int i = 0; i < array_size; i++) {
                    if (this->expr_list == NULL) {
                        this->expr_list = new ExprListNode(this->expr_left);
                    } else {
                        ExprListNode::Append(this->expr_list,
                                             this->expr_left); //TODO создание копии элемента а не сам элемент пихать
                    }
                }

                this->expr_left = NULL;
                this->expr_right = NULL;
                this->type = ExprNode::array_expr;
                this->transform(isConvertedToConst);
            }

            break;
        case index_expr:
            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);
            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);

            if (this->expr_right->dataType.type != DataType::int_) {
                throw Exception(Exception::TYPE_ERROR,
                                "index must be i32. Index type: " + this->expr_right->dataType.toString());
            }


            if (this->expr_left->dataType.type != DataType::array_) {
                throw Exception(Exception::TYPE_ERROR,
                                "type error: expected: array_ result: " + this->expr_left->dataType.toString());
            }

            {
                DataType newDataType = this->expr_left->dataType;
                newDataType.arrDeep--;
                newDataType.arrLength.pop_back();

                if (newDataType.arrDeep == 0) {
                    newDataType.type = this->expr_left->dataType.arrType;
                }

                this->dataType = newDataType;
                this->isConst = this->expr_left->isConst;
                this->isMut = this->expr_left->isMut;
            }

            this->localVarNum = expr_left->localVarNum;
            this->fieldName = expr_left->fieldName;


            break;
        case range_expr:
            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);
            if (!this->expr_left->dataType.isEquals(this->expr_right->dataType)
                || this->expr_left->dataType.type != DataType::int_) {
                throw Exception(Exception::TYPE_ERROR,
                                "range expression must be int_ and result: left=" + expr_left->dataType.toString() +
                                "right=" + expr_right->dataType.toString());
            }

            break;
        case field_access_expr: /// Expression.ID
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);

            if (this->expr_left->dataType.type != DataType::class_) {
                throw Exception(Exception::TYPE_ERROR, this->expr_left->dataType.toString() + " has not fields");
            }

            try {
                FieldTableItem fieldItem = ClassTable::Instance()->getField(this->expr_left->dataType.id, *this->Name);
                this->dataType = fieldItem.dataType;
                this->isConst = this->expr_left->isConst || fieldItem.isConst;
                this->isMut = this->expr_left->isMut && !fieldItem.isConst;
                if (fieldItem.isConst) {
                    throw Exception(Exception::STATIC_ERROR,
                                    this->expr_left->dataType.id + " " + *this->Name + "is static field");
                }

                if (!ClassTable::isHaveAccessToField(curClassName, this->expr_left->dataType.id, *this->Name)) {
                    throw Exception(Exception::ACCESS_ERROR, curClassName + " not has access to field " + *this->Name);
                }

                ClassTable::addFieldRefToConstTable(curClassName, this->expr_left->dataType.id, *this->Name,
                                                    ClassTable::Instance()->getField(this->expr_left->dataType.id,
                                                                                     *this->Name).dataType);
            }
            catch (Exception e) {
                throw e;
            }

            this->localVarNum = expr_left->localVarNum;
            this->fieldName = expr_left->fieldName;

            break;
        case method_expr:
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            if (this->expr_list != NULL) {
                addMetaInfo(this->expr_list);
            }
            this->expr_left->transform(isConvertedToConst);

            if (this->expr_left->dataType.type != DataType::class_) {
                throw Exception(Exception::TYPE_ERROR, this->expr_left->dataType.toString() + "has not methods");
            }

            try {

                MethodTableItem methodItem = ClassTable::Instance()->getMethodDeep(this->expr_left->dataType.id,
                                                                                   *this->Name);
                if (methodItem.isStatic) {
                    throw Exception(Exception::STATIC_ERROR,
                                    this->expr_left->dataType.id + " " + *this->Name + "is static method");
                }

                //VarTableItem selfVarItem = methodItem.localVarTable.getVar(0); ///TODO  пососи ебучая константа

                this->checkMethodParam(this->expr_left->dataType.id, *this->Name);
                this->dataType = methodItem.returnDataType;

                if (!ClassTable::isHaveAccessToMethtod(curClassName, this->expr_left->dataType.id, *this->Name)) {
                    throw Exception(Exception::ACCESS_ERROR, curClassName + " not has access to method " + *this->Name);
                }

                vector<DataType> params;

                for (auto elem: methodItem.paramTable.items) {
                    params.push_back(elem.dataType);
                }
                if (methodItem.isStatic == false) {
                    params.erase(params.begin());
                }
                ClassTable::addMethodRefToConstTable(curClassName, this->expr_left->dataType.id, *this->Name, params,
                                                     methodItem.returnDataType);
            }
            catch (Exception e) {
                throw e;
            }

            break;
        case break_with_val_expr:
            addMetaInfo(expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);
            breakTypes.push_back(this->expr_left->dataType);
            this->dataType = DataType(DataType::void_);
            if (loopCnt == 0) {
                throw Exception(Exception::LOOP_ERROR, "continue is loop outside");
            }

            break;
        case break_expr:
            //   addMetaInfo(expr_left);
            //  checkCancelExprNode(this->expr_left);
            breakTypes.push_back(DataType(DataType::void_));
            this->dataType = DataType(DataType::void_);
            if (loopCnt == 0) {
                throw Exception(Exception::LOOP_ERROR, "continue is loop outside");
            }
            break;
            break;
        case range_right:
            addMetaInfo(expr_left);
            this->expr_left->transform(isConvertedToConst);
            if (expr_left->dataType.type != DataType::int_) {
                throw Exception(Exception::TYPE_ERROR,
                                "range expr should be int_. Result: " + expr_left->dataType.toString());
            }

            this->expr_right = this->expr_left;
            this->expr_left = ExprNode::ExprFromIntLiteral(int_lit, 0);
            this->expr_left->dataType = DataType(DataType::int_);
            this->type = range_expr;
            break;
        case range_left:
            addMetaInfo(expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);
            if (expr_left->dataType.type != DataType::int_) {
                throw Exception(Exception::TYPE_ERROR,
                                "range expr should be int_. Result: " + expr_left->dataType.toString());
            }
            this->expr_right = ExprNode::ExprFromIntLiteral(int_lit, INT32_MAX);
            this->expr_right->dataType = DataType(DataType::int_);
            this->type = range_expr;
            break;
        case return_expr:
            addMetaInfo(expr_left);
            checkCancelExprNode(expr_left);
            this->expr_left->transform(isConvertedToConst);
            returnTypes.push_back(this->expr_left->dataType);
            this->dataType = DataType(DataType::void_);
            break;
        case if_expr_list: {
            vector<DataType> types;
            if (this->ifList != NULL) {
                for (auto elem: *this->ifList) {
                    addMetaInfo(elem);
                    // checkCancelExprNode(expr_left);
                    elem->transform(isConvertedToConst);
                    types.push_back(elem->dataType);
                }
            }

            if (this->else_body != NULL) {
                addMetaInfo(else_body);
                checkCancelExprNode(else_body);
                this->else_body->transform(isConvertedToConst);
                types.push_back(else_body->dataType);
            }

            if (!DataType::isEquals(types)) {
                throw Exception(Exception::TYPE_ERROR, "if has different types");
            }

            if (types.size())
                this->dataType = types.front();
            else
                this->dataType = DataType(DataType::void_);
        }
            break;
        case if_expr:
            addMetaInfo(expr_left);
            checkCancelExprNode(expr_left);
            this->expr_left->transform(isConvertedToConst);

            if (this->expr_left->dataType.type != DataType::bool_) {
                throw Exception(Exception::TYPE_ERROR,
                                "if condition expected: bool_, result: " + this->expr_left->dataType.toString());
            }

            addMetaInfo(body);
            checkCancelExprNode(body);
            this->body->transform(isConvertedToConst);
            this->dataType = this->body->dataType;
            break;
        case loop_expr:

            if (body->dataType.type == DataType::void_) {
                throw Exception(Exception::INCORRECT_TYPE, "loop_expr cannot has return_expr");
            }
            {
                addMetaInfo(body);
                vector<DataType> breaks = breakTypes;
                breakTypes.clear();
                loopCnt++;
                body->transform(isConvertedToConst);
                if (breakTypes.empty()) {
                    throw Exception(Exception::LOOP_ERROR, "loop should has break");
                }
                if (!DataType::isEquals(breakTypes)) {
                    throw Exception(Exception::TYPE_ERROR, "loop has different types");
                }
                loopCnt--;
                this->dataType = breakTypes.front();
                breakTypes = breaks;
            }


            break;
        case loop_while:

            addMetaInfo(expr_left);
            checkCancelExprNode(expr_left);
            this->expr_left->transform(isConvertedToConst);

            if (this->expr_left->dataType.type != DataType::bool_) {
                throw Exception(Exception::TYPE_ERROR,
                                "if condition expected: bool_, result: " + this->expr_left->dataType.toString());
            }


            {
                addMetaInfo(body);
                vector<DataType> breaks = breakTypes;
                breakTypes.clear();
                loopCnt++;
                body->transform(isConvertedToConst);
                breakTypes.push_back(DataType(DataType::void_));
                if (!DataType::isEquals(breakTypes)) {
                    throw Exception(Exception::TYPE_ERROR, "while should return void");
                }
                loopCnt--;
                breakTypes = breaks;
            }

            if (body->dataType.type != DataType::void_) {
                throw Exception(Exception::INCORRECT_TYPE, "while expr cannot has return_expr");
            }

            this->dataType = body->dataType;
            break;
        case loop_for:

            addMetaInfo(expr_left); // for ID IN Expr array 1.. {}
            //checkCancelExprNode(expr_left);
            this->expr_left->transform(isConvertedToConst);
            if (this->expr_left->type == break_expr || this->expr_left->type == return_expr
                || this->expr_left->type == break_with_val_expr) {
                throw Exception(Exception::TYPE_ERROR,
                                "Олег Александрович, ну че вы так  проверяете, не надо пожалуйста. У меня дети есть");
            }

            if (this->expr_left->dataType.type != DataType::array_ &&
                this->expr_left->type != ExprNode::range_expr) {
                throw Exception(Exception::TYPE_ERROR,
                                "for condition should be iterable: range_expr or DataType::array_");
            }

            {
                DataType dataType = DataType(DataType::int_);
                if (this->expr_left->dataType.type == DataType::array_) {
                    dataType = this->expr_left->dataType.getArrDataType();
                }

                VarTableItem varItem = VarTableItem(*this->Name, dataType, this->expr_left->isMut, false, true, false,
                                                    body);
                ClassTable::Instance()->addLocalParam(curClassName, curMethodName, varItem);
            }

            if (this->expr_left->isRefExpr() == false && this->isVar()) {
                ExprNode *delExpr = ExprNode::DelObjectExpr(this->expr_left);
                this->deleteExprList = new ExprListNode(delExpr);
            }

            {
                addMetaInfo(body);
                vector<DataType> breaks = breakTypes;
                breakTypes.clear();
                loopCnt++;
                this->body->transform(isConvertedToConst);

                if (this->body->dataType.type != DataType::void_) {
                    throw Exception(Exception::TYPE_ERROR,
                                    "for condition should be iterable: range_expr or DataType::array_");
                }

                breakTypes.push_back(DataType(DataType::void_));
                if (!DataType::isEquals(breakTypes)) {
                    throw Exception(Exception::TYPE_ERROR, "breaks should be void_ in for");
                }
                loopCnt--;
                breakTypes = breaks;
            }

            this->dataType = body->dataType;
            break;
        case block_expr:

            blockExprList.push_back(this);
            if (this->stmt_list != NULL) {
                for (auto elem: *this->stmt_list->stmts) {
                    elem->curClassName = curClassName;
                    elem->curMethodName = curMethodName;
                    elem->transform(isConvertedToConst);

                    if (elem->type == StmtNode::exprstmt) {
                        if ((elem->expr->type == loop_expr ||
                             elem->expr->type == ExprNode::if_expr_list) &&
                            elem->expr->dataType.type != DataType::void_) {

                            if (elem == this->stmt_list->stmts->back() && this->body != NULL) {
                                throw Exception(Exception::TYPE_ERROR,
                                                "if or loop without  semicolon should return  void_. Result:" +
                                                elem->expr->dataType.toString());
                            }

                            if (elem != this->stmt_list->stmts->back()) {
                                elem++;
                                if (elem->type != StmtNode::semicolon) {
                                    throw Exception(Exception::TYPE_ERROR,
                                                    "if or loop without  semicolon should return  void_. Result:" +
                                                    elem->expr->dataType.toString());
                                }
                                elem--;
                            }

                        }

                    }
                }
            }


            if (this->body == NULL && this->stmt_list != NULL && this->stmt_list->stmts->size()) {
                auto last_stmt = this->stmt_list->stmts->back();
                if (last_stmt->type == StmtNode::exprstmt &&
                    (last_stmt->expr->type == ExprNode::loop_expr ||
                     (last_stmt->expr->type == ExprNode::if_expr_list))) {
                    this->dataType = last_stmt->expr->dataType;
                    this->body = last_stmt->expr;
                    this->stmt_list->stmts->pop_back();
                } else {
                    this->dataType = DataType(DataType::void_);
                }
            }

            if (this->body != NULL) {
                addMetaInfo(body);
                this->body->transform(isConvertedToConst);
                this->dataType = this->body->dataType;
            } else {
                this->dataType = DataType(DataType::void_);
            }

            blockExprList.pop_back();
            break;

        case struct_expr:
            break;
        case struct_field_expr:
            /* empty */
            break;
        case static_method:
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transformPathCallExpr(curClassName, ExprNode::static_method, false);
            this->expr_middle = ExprNode::CallAccessExpr(ExprNode::id_, new string(expr_left->methodName), NULL, NULL);

            if (ClassTable::isMethodExistDeep(this->expr_left->className, *this->expr_middle->Name)) {
                this->dataType = ClassTable::getMethodDeep(this->expr_left->className,
                                                           *this->expr_middle->Name).returnDataType;
            } else if (ClassTable::Instance()->isMethodExist(ClassTable::RTLClassName, *this->expr_middle->Name)) {
                this->expr_left->className = ClassTable::RTLClassName;
                this->dataType = ClassTable::Instance()->getMethod(this->expr_left->className,
                                                                   *this->expr_middle->Name).returnDataType;
            } else {
                throw Exception(Exception::NOT_EXIST,
                                "call method " + this->expr_left->className + " " + *this->expr_left->Name +
                                " not exist");
            }

            checkMethodParam(this->expr_left->className, this->expr_left->methodName);
            if (!ClassTable::isHaveAccess(curClassName, this->expr_left->className)) {
                throw Exception(Exception::ACCESS_ERROR,
                                curClassName + " has not access to " + this->expr_left->className);
            }

            if (!ClassTable::isHaveAccessToMethtod(curClassName, this->expr_left->className,
                                                   *this->expr_middle->Name)) {
                throw Exception(Exception::ACCESS_ERROR,
                                curClassName + " has not access to " + *this->expr_middle->Name);
            }

            {
                vector<DataType> params;
                MethodTableItem methodTableItem = ClassTable::getMethodDeep(this->expr_left->className,
                                                                            *this->expr_middle->Name);
                for (auto elem: methodTableItem.paramTable.items) {
                    params.push_back(elem.dataType);
                }

                ClassTable::addMethodRefToConstTable(curClassName, this->expr_left->className, *this->expr_middle->Name,
                                                     params,
                                                     methodTableItem.returnDataType);
            }
            break;
        case path_call_expr:
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);

            this->transformPathCallExpr(curClassName, ExprNode::field_access_expr, false);
            this->expr_middle = ExprNode::CallAccessExpr(ExprNode::id_, new string(fieldName), NULL, NULL);

            if (ClassTable::isFieldExistDeep(this->className, *this->expr_middle->Name)) {
                this->dataType = ClassTable::getFieldDeep(this->className,
                                                          *this->expr_middle->Name).dataType;
            } else {
                throw Exception(Exception::NOT_EXIST,
                                "call field " + this->expr_left->className + " " + *this->expr_left->Name +
                                " not exist");
            }

            {
                ClassTable::addFieldRefToConstTable(curClassName, this->className, *this->expr_middle->Name,
                                                    ClassTable::Instance()->getFieldDeep(this->className,
                                                                                         *this->expr_middle->Name).dataType);

            }


            break;

        case struct_creation:
            this->checkStructExpr();
            break;
        case as:
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);
            if (DataType::isCanConvert(this->expr_left->dataType, this->typeNode->convertToDataType(curClassName))) {
                this->dataType = this->typeNode->convertToDataType(curClassName);
            } else {
                throw Exception(Exception::TYPE_ERROR,
                                "cannot convert type " + this->expr_left->dataType.toString() + " to " +
                                this->typeNode->convertToDataType(curClassName).toString());
            }


            break;

        case id_: {
            int tmp = Node::getVarNumber(blockExprList, curClassName, curMethodName, *this->Name);
            if (tmp != -1) {
                this->localVarNum = tmp;
                VarTableItem varItem = ClassTable::Instance()->getLocalVar(curClassName, curMethodName, tmp);
                this->isMut = varItem.isMut;
                this->isConst = varItem.isConst;
                this->dataType = varItem.dataType;
            } else if (ClassTable::Instance()->isFieldExist(curClassName, *this->Name)) {
                this->fieldName = *this->Name;
                FieldTableItem fieldItem = ClassTable::Instance()->getField(curClassName, *this->Name);
                this->isMut = !fieldItem.isConst;
                this->isConst = fieldItem.isConst;
                this->dataType = fieldItem.dataType;
            } else {
                throw Exception(Exception::NOT_EXIST, "var " + *this->Name + "not exist");
            }

        }
            break;
        case self_expr: {
            MethodTableItem methodItem = ClassTable::Instance()->getMethod(curClassName, curMethodName);

            if (methodItem.isStatic) {
                throw Exception(Exception::STATIC_ERROR, "static error: self used in static method ");
            }

            this->localVarNum = 0; //TODO бебебе
            this->dataType = methodItem.paramTable.getVar(0).dataType;
            this->isMut = methodItem.paramTable.getVar(0).isMut;
        }
            break;
        case super_expr:
            throw Exception(Exception::NOT_SUPPORT, "here are too many leading `super` keywords");
            break;


        case int_lit:
            this->dataType = DataType(DataType::int_);
            if (this->Int < INT16_MIN || this->Int > INT16_MAX) {
                ClassTable::addIntToConstTable(curClassName, this->Int);
            }
            this->isConst = true;
            break;
        case float_lit:
            this->dataType = DataType(DataType::float_);
            ClassTable::addFloatToConstTable(curClassName, this->Float);
            this->isConst = true;
            break;
        case char_lit:
            this->dataType = DataType(DataType::char_);
            this->isConst = true;
            break;
        case string_lit:
            this->dataType = DataType(DataType::string_);
            ClassTable::addStringToConstTable(curClassName, *this->String);
            this->isConst = true;
            break;
        case raw_string_lit:
            this->dataType = DataType(DataType::string_);
            ClassTable::addStringToConstTable(curClassName, *this->String);
            this->isConst = true;
            break;
        case bool_lit:
            this->dataType = DataType(DataType::bool_);
            this->isConst = true;
            break;

        case question:
        case ustar:
        case tuple_expr:
            throw Exception(Exception::NOT_SUPPORT, "this operation not supported");
            break;

        case link:
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);
            if (this->isVar() == false) {
                throw Exception(Exception::UNEXPECTED, "link operation with not var element");
            }

            this->dataType = this->expr_left->dataType;
            this->isMut = false;
            //  if(this->dataType.)

            break;
        case mut_link:

            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);

            if (this->isVar() == false) {
                throw Exception(Exception::UNEXPECTED, "link operation with not var element");
            }

            if (this->expr_left->isMut == false) {
                throw Exception(Exception::UNEXPECTED, "Cannot create mut link element because var is not mut");
            }

            this->dataType = this->expr_left->dataType;
            break;


        case call_expr:
        case continue_expr:
            if (loopCnt == 0) {
                throw Exception(Exception::LOOP_ERROR, "continue is loop outside");
            }
            break;
    }

}

void ExprNode::transformConst() {


    switch (this->type) {
        case plus:
        case minus:
        case mul_expr:
        case div_expr:
        case mod:
//        case or_:
//        case and_:
        case asign:
        case equal:
        case not_equal:
        case greater:
        case less:
        case greater_equal:
        case less_equal:
            this->expr_left->transformConst();
            this->expr_right->transformConst();
            if (!this->expr_left->isEqualDataType(this->expr_right)) {
                throw Exception(Exception::NOT_EQUAL_DATA_TYPE,
                                "NOT EQUAL DATATYPE " + this->expr_left->dataType.toString() + " and" +
                                this->expr_right->dataType.toString());
            }
            if (!this->expr_left->isLiteral() || !this->expr_right->isLiteral()) {
                throw Exception(Exception::NOT_CONST, "Excepted CONST but it NOT CONST");
            }
            break;
        case uminus:
        case negotation:
        case as:
            this->expr_left->transformConst();
            if (!this->expr_left->isLiteral()) {
                throw Exception(Exception::NOT_CONST, "Excepted CONST but it NOT CONST");
            }
            break;
    }

    switch (this->type) {

        case plus:
            if (this->expr_left->dataType.type == DataType::int_) {
                this->Int = this->expr_left->Int + this->expr_right->Int;
                this->type = int_lit;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Float = this->expr_left->Float + this->expr_right->Float;
                this->type = float_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }

            this->dataType.type = this->expr_left->dataType.type;
            break;
        case minus:
            if (this->expr_left->dataType.type == DataType::int_) {
                this->Int = this->expr_left->Int - this->expr_right->Int;
                this->type = int_lit;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Float = this->expr_left->Float - this->expr_right->Float;
                this->type = float_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }

            this->dataType.type = this->expr_left->dataType.type;
            break;
        case mul_expr:
            if (this->expr_left->dataType.type == DataType::int_) {
                this->Int = this->expr_left->Int * this->expr_right->Int;
                this->type = int_lit;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Float = this->expr_left->Float * this->expr_right->Float;
                this->type = float_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }

            this->dataType.type = this->expr_left->dataType.type;
            break;
        case div_expr:
            if (this->expr_left->dataType.type == DataType::int_) {
                if (this->expr_right->Int == 0) {
                    throw Exception(Exception::NULL_DIVIDE, "NULL DIVIDE");
                }
                this->Int = this->expr_left->Int / this->expr_right->Int;
                this->type = int_lit;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                if (this->expr_right->Float == 0) {
                    throw Exception(Exception::NULL_DIVIDE, "NULL DIVIDE");
                }
                this->Float = this->expr_left->Float / this->expr_right->Float;
                this->type = float_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }

            this->dataType.type = this->expr_left->dataType.type;
            break;
        case mod:
            if (this->expr_left->dataType.type == DataType::int_) {
                if (this->expr_right->Int == 0) {
                    throw Exception(Exception::NULL_DIVIDE, "NULL DIVIDE");
                }
                this->Int = this->expr_left->Int % this->expr_right->Int;
                this->type = int_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }

            this->dataType.type = this->expr_left->dataType.type;
            break;
        case or_:
            this->expr_left->transformConst();
            if (this->expr_left->dataType.type == DataType::bool_) {

                if (!this->expr_left->isLiteral()) {
                    throw Exception(Exception::NOT_CONST, "Excepted CONST but it NOT CONST");
                }

                if (this->expr_left->Bool == 1) {
                    this->Bool = 1;
                } else {
                    this->expr_right->transformConst();

                    if (!this->expr_right->isLiteral()) {
                        throw Exception(Exception::NOT_CONST, "Excepted CONST but it NOT CONST");
                    }

                    if (this->expr_right->dataType.type == DataType::bool_) {
                        this->Bool = this->expr_right->Bool;
                    } else {
                        throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                        "THIS LITERAL NOT SUPPORTED THIS OPERATION. RIGHT OPERAND ARE NOT BOOL");
                    }

                }
                //this->Bool = this->expr_left->Bool || this->expr_right->Bool;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION - OR");
            }

            this->type = bool_lit;
            this->dataType.type = this->expr_left->dataType.type;
            break;
        case and_:
            this->expr_left->transformConst();
            if (!this->expr_left->isLiteral()) {
                throw Exception(Exception::NOT_CONST, "Excepted CONST but it NOT CONST");
            }
            if (this->expr_left->dataType.type == DataType::bool_) {
                if (this->expr_left->Bool == 0) {
                    this->Bool = 0;
                } else {
                    this->expr_right->transformConst();

                    if (!this->expr_right->isLiteral()) {
                        throw Exception(Exception::NOT_CONST, "Excepted CONST but it NOT CONST");
                    }

                    if (this->expr_right->dataType.type == DataType::bool_) {
                        this->Bool = this->expr_right->Bool;
                    } else {
                        throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                        "THIS LITERAL NOT SUPPORTED THIS OPERATION. RIGHT OPERAND ARE NOT BOOL");
                    }
                }
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION - AND");
            }

            this->type = bool_lit;
            this->dataType.type = this->expr_left->dataType.type;
            break;
        case equal:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool == this->expr_right->Bool;
            } else if (this->expr_left->dataType.type == DataType::int_) {
                this->Bool = this->expr_left->Int == this->expr_right->Int;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Bool = this->expr_left->Float == this->expr_right->Float;
            } else if (this->expr_left->dataType.type == DataType::char_) {
                this->Bool = this->expr_left->Char == this->expr_right->Char;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }

            this->type = bool_lit;
            this->dataType.type = DataType::bool_;

            break;
        case not_equal:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool != this->expr_right->Bool;
            } else if (this->expr_left->dataType.type == DataType::int_) {
                this->Bool = this->expr_left->Int != this->expr_right->Int;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Bool = this->expr_left->Float != this->expr_right->Float;
            } else if (this->expr_left->dataType.type == DataType::char_) {
                this->Bool = this->expr_left->Char != this->expr_right->Char;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }
            this->type = bool_lit;
            this->dataType.type = DataType::bool_;
            break;
        case greater:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool > this->expr_right->Bool;
            } else if (this->expr_left->dataType.type == DataType::int_) {
                this->Bool = this->expr_left->Int > this->expr_right->Int;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Bool = this->expr_left->Float > this->expr_right->Float;
            } else if (this->expr_left->dataType.type == DataType::char_) {
                this->Bool = this->expr_left->Char > this->expr_right->Char;
                this->type = bool_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }

            this->type = bool_lit;
            this->dataType.type = DataType::bool_;
            break;
        case less:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool < this->expr_right->Bool;
            } else if (this->expr_left->dataType.type == DataType::int_) {
                this->Bool = this->expr_left->Int < this->expr_right->Int;
            } else if (this->expr_left->dataType.type == DataType::float_) { // 1 + 1 * 3 = 4
                this->Bool = this->expr_left->Float < this->expr_right->Float;
            } else if (this->expr_left->dataType.type == DataType::char_) {
                this->Bool = this->expr_left->Char < this->expr_right->Char;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }
            this->type = bool_lit;
            this->dataType.type = DataType::bool_;
            break;
        case greater_equal:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool >= this->expr_right->Bool;
            } else if (this->expr_left->dataType.type == DataType::int_) {
                this->Bool = this->expr_left->Int >= this->expr_right->Int;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Bool = this->expr_left->Float >= this->expr_right->Float;
            } else if (this->expr_left->dataType.type == DataType::char_) {
                this->Bool = this->expr_left->Char >= this->expr_right->Char;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }
            this->type = bool_lit;
            this->dataType.type = DataType::bool_;

            break;
        case less_equal:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool <= this->expr_right->Bool;
            } else if (this->expr_left->dataType.type == DataType::int_) {
                this->Bool = this->expr_left->Int <= this->expr_right->Int;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Bool = this->expr_left->Float <= this->expr_right->Float;
            } else if (this->expr_left->dataType.type == DataType::char_) {
                this->Bool = this->expr_left->Char <= this->expr_right->Char;

            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }

            this->type = bool_lit;
            this->dataType.type = DataType::bool_;
            break;
        case uminus:
            if (this->expr_left->dataType.type == DataType::int_) {
                this->Int = -this->expr_left->Int;
                this->type = int_lit;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Float = this->expr_left->Float <= this->expr_right->Float;
                this->type = float_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }
            this->dataType.type = this->expr_left->dataType.type;
            break;
        case negotation:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = !this->expr_left->Bool;
                this->type = bool_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }

            this->dataType.type = DataType::bool_;
            break;
        case as:
            if (this->expr_left->dataType.type == DataType::int_) {
                switch (this->typeNode->dataType.type) {

                    case DataType::float_:
                        this->Float = this->expr_left->Int;
                        this->dataType.type = DataType::float_;
                        this->type = float_lit;
                        break;
                    case DataType::char_:
                        if (this->expr_left->Int > 255 || this->expr_left->Int < 0) {
                            throw Exception(Exception::CANNOT_CONVERTED, "Too long for char");
                        }
                        this->Char = this->expr_left->Int;
                        this->dataType.type = DataType::char_;
                        this->type = char_lit;
                        break;

                    case DataType::bool_:
                    case DataType::string_: // пусть явно будет а то дефолт еще фиг вспомнишь что так
                    case DataType::class_:
                    case DataType::array_:
                    case DataType::void_:
                        throw Exception(Exception::CANNOT_CONVERTED, "Cannot convert one type to other");
                        break;
                    case DataType::int_:
                        break;
                }
            } else if (this->expr_left->dataType.type == DataType::float_) {
                switch (this->typeNode->dataType.type) {

                    case DataType::int_:
                        this->Int = this->expr_left->Float;
                        this->dataType.type = DataType::int_;
                        this->type = int_lit;
                        break;
                    case DataType::char_:
                    case DataType::bool_:
                    case DataType::string_: // пусть явно будет а то дефолт еще фиг вспомнишь что так
                    case DataType::class_:
                    case DataType::array_:
                    case DataType::void_:
                        throw Exception(Exception::CANNOT_CONVERTED, "Cannot convert one type to other");
                        break;
                    case DataType::float_:
                        break;
                }
            } else if (this->expr_left->dataType.type == DataType::char_) {
                switch (this->typeNode->dataType.type) {

                    case DataType::int_:
                        this->Int = this->expr_left->Char;
                        this->dataType.type = DataType::int_;
                        this->type = int_lit;
                        break;

                    case DataType::char_:
                    case DataType::bool_:
                    case DataType::string_: // пусть явно будет а то дефолт еще фиг вспомнишь что так
                    case DataType::class_:
                    case DataType::array_:
                    case DataType::void_:
                        throw Exception(Exception::CANNOT_CONVERTED, "Cannot convert one type to other");
                        break;
                    case DataType::float_:
                        break;
                }
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }

            break;

        case question:
        case ustar:
        case link:
        case mut_link:
        case array_expr:
        case array_expr_auto_fill:
        case index_expr:
        case field_access_expr:
        case call_expr:
        case method_expr:
        case continue_expr:
        case break_expr:
        case break_with_val_expr:
        case return_expr:
        case self_expr:
        case if_expr_list:
        case if_expr:
        case loop_expr:
        case loop_while:
        case loop_for:
        case block_expr:
        case struct_expr:
        case struct_field_expr:
        case static_method:
        case tuple_expr:
        case super_expr:
        case path_call_expr:
        case add_if_block:
        case struct_creation:
        case undefined:
        case range_right: // надеюсь это говно тестить не будут а то лень реализовывать
        case range_left:
        case id_:
        case range_expr:
        case asign:
            throw new Exception(Exception::NOT_LITERAL_OPERATION, "USED NOT LITERAL OPERATION");
            break;

        case int_lit:
            this->dataType.type = DataType::int_;
            break;
        case float_lit:
            this->dataType.type = DataType::float_;
            break;
        case char_lit:
            this->dataType.type = DataType::char_;
            break;
        case string_lit:
            this->dataType.type = DataType::string_;
            break;
        case raw_string_lit:
            this->dataType.type = DataType::string_;
            break;
        case bool_lit:
            this->dataType.type = DataType::bool_;
            break;

    }

    this->expr_left = NULL;
    this->expr_right = NULL;
}

void ExprNode::checkMethodParam(const string &className, const string &methodName) {

    try {
        MethodTableItem methodItem = ClassTable::Instance()->getMethodDeep(className,
                                                                           methodName);


        VarTable paramTable = methodItem.paramTable;

        if (!methodItem.isStatic) { //TODO это говно надо чекнуть
            paramTable.items.erase(paramTable.items.begin());
        }

        if (this->expr_list == NULL && paramTable.items.size() == 0) {
            return;
        }

        if (this->expr_list == NULL) {
            throw Exception(Exception::PARAM_ERROR,
                            "Param Error expected: " + to_string(paramTable.items.size())
                            + " param count result:" + to_string(0) + " param count");
        }

        if (this->expr_list->exprs->size() != paramTable.items.size()) {
            throw Exception(Exception::PARAM_ERROR,
                            "Param Error expected: " + to_string(this->methodTableItem.paramTable.items.size())
                            + " param count result:" + to_string(this->expr_list->exprs->size()) + " param count");
        }

        int i = 0;
        for (auto elem: *this->expr_list->exprs) {
            addMetaInfo(elem);
            elem->transform();
            if (elem->type == ExprNode::break_with_val_expr || elem->type == ExprNode::break_expr ||
                elem->type == ExprNode::return_expr || elem->type == ExprNode::continue_expr) {
                throw Exception(Exception::TYPE_ERROR,
                                "Олег Александрович вы че куда суете. Какие брейки в параметрах. Жесть. 1984");
            }
            VarTableItem varItem = paramTable.items[i];
            bool isElemRef = varItem.isRef == elem->isRefExpr();
            bool isElemMut = !varItem.isMut || varItem.isMut == elem->isMut || (elem->isSimpleType() && !isElemRef);
            bool isElemConst = !varItem.isConst || (!varItem.isMut && varItem.isConst == elem->isConst);
            bool checker = isElemMut && isElemRef && isElemConst;
            // bool checker = varItem.isRef == elem->isRefExpr() && varItem.isMut == elem->isMut && (varItem.isConst == elem->isConst || elem->isSimpleType());
            if (!varItem.dataType.isEquals(elem->dataType) &&
                !isParent(elem->dataType, varItem.dataType) || !checker) { //TODO проверить

                VarTableItem resultVarItem = VarTableItem(varItem.id, elem->dataType, elem->isMut, isRefExpr(), true,
                                                          elem->isConst);
                throw Exception(Exception::TYPE_ERROR,
                                varItem.id + " type expected: " + varItem.toString() + " result: " +
                                resultVarItem.toString() + " ");
            }
            i++;
        }
    }
    catch (Exception e) {
        throw e;
    }
}

void ExprNode::checkCancelExprNode(ExprNode *exprNode, bool isBreakCanceled) {

    if (exprNode->type == link) {
        throw Exception(Exception::TYPE_ERROR, "operation not supported by link");
    }

    if (exprNode->type == mut_link) {
        throw Exception(Exception::TYPE_ERROR, "operation not supported by mut_link");
    }

    if (exprNode->type == return_expr) {
        throw Exception(Exception::TYPE_ERROR, "operation not supported by return_expr");
    }

    if (exprNode->type == break_with_val_expr && isBreakCanceled) {
        throw Exception(Exception::TYPE_ERROR, "operation not supported by break with expr");
    }

    if (exprNode->type == break_expr) {
        throw Exception(Exception::TYPE_ERROR, "operation not supported by break");
    }

    if (exprNode->type == continue_expr) {
        throw Exception(Exception::TYPE_ERROR, "operation not supported by continue");
    }
}

ExprNode *ExprNode::DelObjectExpr(ExprNode *expr) {
    ExprNode *node = new ExprNode();
    node->id = ++globId;
    node->type = ExprNode::del_object;
    node->expr_left = expr;

    if (expr->isVar() == false) {
        throw Exception(Exception::UNEXPECTED, "it`s not a var");
    }

    if (expr->dataType.type != DataType::class_ && expr->dataType.type != DataType::array_) {
        throw Exception(Exception::UNEXPECTED, "type should be array_ or class_");
    }

    return node;
}

bool ExprNode::isRefExpr() {
    return this->type == link || this->type == mut_link || this->dataType.type == DataType::string_;
}

bool ExprNode::isVar() {
    return this->localVarNum != -1 || this->fieldName.empty() == false;
}

void ExprNode::checkStructExpr(bool isConvertedTransform) {

    try {
        if (this->expr_left->type != path_call_expr && this->expr_left->type != id_) {
            throw Exception(Exception::CONSTRUCTOR_ERROR, "expression should be paathCallExpr");
        }


        this->expr_left->transformPathCallExpr(curClassName, undefined, true);
        this->className = this->expr_left->className;

        if (ClassTable::Instance()->getClass(this->className).classType != ClassTableItem::struct_) {
            throw Exception(Exception::TYPE_ERROR, "constructor error: " + className + " is not struct");
        }

        int fieldSize = ClassTable::getStructFieldCount(className);

        if (fieldSize != this->field_list->exprs->size()) {
            throw Exception(Exception::CONSTRUCTOR_ERROR,
                            "fields count in constructor not equal field count in struct " + className +
                            ". Expected: " + to_string(fieldSize) + " result: " +
                            to_string(this->field_list->exprs->size()));
        }

        if (!ClassTable::isHaveAccess(curClassName, this->className)) {
            throw Exception(Exception::ACCESS_ERROR, curClassName + " has not access to " + this->expr_left->className);
        }


        vector<DataType> params;

        for (auto elem: *this->field_list->exprs) {
            addMetaInfo(elem->expr_left);
            checkCancelExprNode(elem->expr_left);
            elem->expr_left->transform(isConvertedTransform);
            if (ClassTable::Instance()->isFieldExist(className, *elem->Name)) {
                FieldTableItem fieldItem = ClassTable::Instance()->getField(className, *elem->Name);
                if (!ClassTable::isHaveAccessToField(curClassName, this->expr_left->className, *elem->Name)) {
                    throw Exception(Exception::ACCESS_ERROR,
                                    curClassName + " has not access to private " + *elem->Name);
                }

                params.push_back(fieldItem.dataType);

                if (fieldItem.dataType.isEquals(elem->expr_left->dataType) &&
                    isParent(elem->expr_left->dataType, fieldItem.dataType)) {
                    throw Exception(Exception::TYPE_ERROR,
                                    *this->Name + "field type should be " + fieldItem.toString() + " " +
                                    elem->expr_left->dataType.toString());
                }
            } else {
                throw Exception(Exception::CONSTRUCTOR_ERROR, *this->Name + " field not exist in struct " + className);
            }
        }


        ClassTable::addMethodRefToConstTable(curClassName, this->expr_left->className, "<init>", vector<DataType>(),
                                             DataType(DataType::void_));

        this->dataType = DataType::StructDataType(this->className);

    }
    catch (Exception e) {
        throw e;
    }
}


bool Node::isEqualDataType(Node *node) {
    return this->dataType.type == node->dataType.type;
}

void Node::transform(bool isConvertedToConst) {

}

void Node::addMetaInfo(Node *node) {
    node->curClassName = this->curClassName;
    node->curMethodName = this->curMethodName;
}

bool Node::isParent(const DataType &child, DataType parent) {
    if (child.type != DataType::class_) {
        return false;
    }
    if (parent.type != DataType::class_) {
        return false;
    }

    return ClassTable::Instance()->isParent(child.id, parent.id);
}

int Node::getVarNumber(vector<ExprNode *> &blockExprList, const string &className, const string &methodName,
                       const string &varName) {
    int res = -1;
    int cur = blockExprList.size() - 1;
    while (res == -1 & cur >= 0) {
        if (ClassTable::Instance()->isLocalVarExist(className, methodName, varName, blockExprList[cur])) {
            res = ClassTable::Instance()->getMethod(className, methodName).localVarTable.getVarNumber(varName,
                                                                                                      blockExprList[cur]);
            break;
        }
        cur--;
    }
    return res;
}


