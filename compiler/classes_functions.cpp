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
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = left;
    new_node->expr_right = right;
    return new_node;
}

ExprNode *ExprNode::PathCallExpr(Type type, string *name, ExprNode *expr) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Name = name;
    new_node->expr_left = expr;
    return new_node;
}

ExprNode *ExprNode::ExprFromBoolLiteral(Type type, bool value) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Bool = value;
    return new_node;
}

ExprNode *ExprNode::ExprFromIntLiteral(Type type, int value) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Int = value;
    return new_node;
}

ExprNode *ExprNode::ExprFromFloatLiteral(Type type, float value) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Float = value;
    return new_node;
}

ExprNode *ExprNode::ExprFromCharLiteral(Type type, char value) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Char = value;
    return new_node;
}

ExprNode *ExprNode::ExprFromStringLiteral(Type type, string *value) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->String = value;
    return new_node;
}

ExprNode *ExprNode::StaticMethod(Type type, ExprNode *expr, ExprListNode *expr_list) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->expr_list = expr_list;
    return new_node;
}

ExprNode *ExprNode::FieldListAccess(Type type, ExprNode *expr, ExprListNode *field_list) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->field_list = field_list;
    return new_node;
}

ExprNode *ExprNode::CallAccessExpr(Type type, string *name, ExprNode *expr, ExprListNode *expr_list) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Name = name;
    new_node->expr_left = expr;
    new_node->expr_list = expr_list;
    return new_node;
}

// StaticMethodExpr
ExprNode *ExprNode::StaticMethodExpr(Type type, string *name, string *parent_id, ExprListNode *expr_list) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->Name = name;
    new_node->ParentID = parent_id;
    new_node->expr_list = expr_list;
    return new_node;
}

ExprNode *ExprNode::BlockExpr(Type type, ExprNode *body, StmtListNode *stmt_list) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->body = body;
    new_node->stmt_list = stmt_list;
    return new_node;
}

ExprNode *ExprNode::ArrExprFromList(Type type, ExprListNode *expr_list) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_list = expr_list;
    return new_node;
}

ExprNode *ExprNode::ArrExprAutoFill(Type type, ExprNode *first, ExprNode *second) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = first;
    new_node->expr_right = second;
    return new_node;
}

ExprNode *ExprNode::TupleExpr(Type type, ExprNode *expr, int value) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->Int = value;
    return new_node;
}

ExprNode *ExprNode::CycleExpr(Type type, ExprNode *condition, ExprNode *body, string *id) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->body = body;
    new_node->expr_left = condition;
    new_node->Name = id;
    return new_node;
}

ExprNode *ExprNode::RangeExpr(Type type, ExprNode *left, ExprNode *right) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = left;
    new_node->expr_right = right;
    return new_node;
}

ExprNode *ExprNode::IfExpr(Type type, ExprNode *condition, ExprNode *body) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = condition;
    new_node->body = body;


    return new_node;
}

ExprNode *ExprNode::IfExprList(ExprNode *ifExpr) {
    ExprNode *new_node = new ExprNode();
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
            cout << this->name << "\n";
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
    }

    if (this->id == 3) {
        int x;
    }
    createVertexDot(dot, this->id, "expr", type, value, "", pos);

    if (this->expr_left != NULL) {
        connectVerticesDots(dot, this->id, this->expr_left->id);
        this->expr_left->toDot(dot, "expr_left");
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
        //    cout << "adfkshfadgdjaf\n";
        for (auto elem: *this->ifList) {
            connectVerticesDots(dot, this->id, elem->id);
            elem->toDot(dot, "condition" + to_string(ifCount++));
        }
    }

    if (this->else_body != NULL) {
        connectVerticesDots(dot, this->id, this->else_body->id);
        this->else_body->toDot(dot, "else_body");
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

    if (this->type == semicolon) {
        return;
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
    cout << this->id << "\n";
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

void connectVerticesDots(string &s, int parentId, int childId) {
    string tmp = "id" + to_string(parentId) + " -> " + "id" + to_string(childId) + ";\n";
    s += tmp;
}

void createVertexDot(string &s, int id, string name, string type, string value, string visibility, string pos) {
    if (!type.empty()) {
        type = "type=" + type + " ";
    }

    if (!value.empty()) {
        value = "value=" + value + " ";
    }

    if (!visibility.empty()) {
        visibility = "visibility=" + visibility + " ";
    }
    if (!pos.empty()) {
        pos = "position=" + pos + " ";
    }

    string tmp = "id" + to_string(id) +
                 " [label=\"" + name + " " + type + value + visibility + pos + "id=" + to_string(id) + "\"];\n";

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
    ClassTable::Instance()->addClass(className, classTableItem);
    try {
        for (auto elem: *item_list->items) {
            elem->getAllItems(className);

//        switch (elem->item_type) {
//
//
//            case ItemNode::function_:
//                ClassTable:: Instance()->addMethod(className, *elem->name, elem->methodTableItem);
//            case ItemNode::constStmt_:
//                ClassTable:: Instance()->addField(className, *elem->name, elem->fieldTableItem);
//                break;
//            case ItemNode::struct_:
//            case ItemNode::trait_:
//            case ItemNode::impl_:
//            case ItemNode::module_:
//            case ItemNode::enum_:
//                break;
//        }
        }

    }
    catch (Exception e) {
        cout << e.getMessage() << "\n";
    }
}

void ItemNode::getAllItems(std::string className) {

    if (this->item_type == impl_) {
        return;
    }

    try {
        switch (item_type) {
            case enum_:

                if (ClassTable::Instance()->isClassExist(className + "/" + *this->name)) {
                    throw Exception(Exception::DEFINED_MULTIPLE, *this->name + "DEFINED_MULTIPLE in namespace");
                }

                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::enum_;
                ClassTable::Instance()->addClass(className + "/" + *this->name, classTableItem);
                break;
            case function_:

                if (ClassTable::Instance()->isMethodExist(className, *this->name)) {
                    throw Exception(Exception::DEFINED_MULTIPLE, *this->name + "DEFINED_MULTIPLE in namespace");
                }

                this->methodTableItem = MethodTableItem();
                if(this->body != NULL) this->methodTableItem.isHasBody = true;
                if( ClassTable::Instance()->getClass(className).classType != trait_ && this->methodTableItem.isHasBody == false);
                {
                    throw Exception(Exception::NOT_IMPLEMICATION, *this->name + "NOT_IMPLEMICATION");
                }

                ClassTable::Instance()->addMethod(className, *this->name, this->methodTableItem);
                break;
            case constStmt_:


                if (ClassTable::Instance()->isFieldExist(className, *this->name)) {
                    throw Exception(Exception::DEFINED_MULTIPLE, *this->name + " DEFINED_MULTIPLE in namespace");
                }
                this->fieldTableItem = FieldTableItem();
                if(this->expr != NULL) this->fieldTableItem.isInit = true;
                if(this->fieldTableItem.isInit == false && ClassTable::Instance()->getClass(className).classType != trait)
                {
                    throw Exception(Exception::NOT_IMPLEMICATION, *this->name + " NOT_DEFINED");
                }

                ClassTable::Instance()->addField(className, *this->name, this->fieldTableItem);
                break;
            case trait_:

                if (ClassTable::Instance()->isClassExist(className + "/" + *this->name)) {
                    throw Exception(Exception::DEFINED_MULTIPLE, *this->name + "DEFINED_MULTIPLE in namespace");
                }
                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::struct_;
                ClassTable::Instance()->addClass(className + "/" + *this->name, classTableItem);
                break;
            case module_:
                break;
            case struct_:

                if (ClassTable::Instance()->isClassExist(className + "/" + *this->name)) {
                    throw Exception(Exception::DEFINED_MULTIPLE, *this->name + "DEFINED_MULTIPLE in namespace");
                }
                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::struct_;
                ClassTable::Instance()->addClass(className + "/" + *this->name, classTableItem);
                break;

            case impl_:
                break;
        }
    }
    catch (Exception e) {
        throw e;
    }
}