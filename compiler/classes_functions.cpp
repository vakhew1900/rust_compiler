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
            //  cout << this->name << "\n";
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
    //  cout << this->id << "\n";
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
                 " [label=\"name=" + name + " " + type + value + visibility + pos + "id=" + to_string(id) + "\"];\n";

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
                if (elem->item_type == ItemNode::function_ || elem->item_type == ItemNode::constStmt_)
                    elem->getAllItems(className + "/" + ClassTable::moduleClassName);
                else
                    elem->getAllItems(className);
            }
        }

        this->addImpl(className, false);
    }
    catch (Exception e) {
        cout << e.getMessage() << "\n";
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
                     || this->params->func_type == FuncParamListNode::self) &&
                    ClassTable::Instance()->getClass(className).classType == ClassTableItem::mod_) {
                    throw Exception(Exception::NOT_A_METHOD, "function " + *this->name + " NOT_A_METHOD");
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
                        elem->getAllItems(className + "/" + *this->name);
                    }
                }

                break;
            case module_:
                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::mod_;
                if (this->visibility == pub) this->classTableItem.isPub = true;
                ClassTable::Instance()->addClass(className + "/" + *this->name, classTableItem);

                if (this->items != NULL) {
                    for (auto elem: *this->items->items) {
                        string str = (elem->item_type == function_ || elem->item_type == constStmt_)
                                     ? ClassTable::moduleClassName : "";
                        elem->getAllItems(className + "/" + *this->name);
                    }
                }
                break;
            case enum_:
                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::enum_;
                if (this->visibility == pub) this->classTableItem.isPub = true;
                ClassTable::Instance()->addClass(className + "/" + *this->name, classTableItem);

                if (this->enumItems != NULL) {
                    for (auto elem: *this->enumItems->items) {
                        elem->getAllItems(className + "/" + *this->name);
                    }
                }

                break;
            case struct_:
                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::struct_;
                if (this->visibility == pub) this->classTableItem.isPub = true;
                ClassTable::Instance()->addClass(className + "/" + *this->name, classTableItem);

                if (this->structItems->items != NULL) {
                    for (auto elem: *this->structItems->items) {
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
    this->fieldTableItem.isConst = true;
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
                    throw Exception(Exception::NOT_EXIST, "Impl struct" + implClassName + "Not Exist");
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
                        elem->addImpl(implClassName, this->impl_type == trait);
                    }
                }

                if (this->impl_type == trait) {
                    ClassTable::isCorrectChild(implClassName, traitClassName);
                }

                break;
            case function_:
                this->methodTableItem = MethodTableItem();
                if (this->body != NULL) this->methodTableItem.isHasBody = true;
                if (this->visibility == pub) this->methodTableItem.isPub = true;

                if (ClassTable::Instance()->getClass(className).classType != ClassTableItem::trait_ &&
                    this->methodTableItem.isHasBody == false) {
                    throw Exception(Exception::NOT_IMPLEMICATION, *this->name + " NOT_IMPLEMICATION");
                }

                if (isTrait && ClassTable::Instance()->
                        isMethodExist(ClassTable::Instance()->getClass(className).parentName, *this->name) == false) {
                    throw Exception(Exception::NOT_EXIST, "Impl Error: method" + *this->name + "in parent trait");
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

                if (isTrait && !ClassTable::Instance()->
                        isFieldExist(ClassTable::Instance()->getClass(className).parentName, *this->name)) {
                    throw Exception(Exception::NOT_EXIST, "Impl Error: method" + *this->name + "in parent trait");
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

            if (this->typeArr->type == array_) {
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
                }
            }

            break;
        case path_call_expr_:
            this->pathCallExpr->transformPathCallExpr(className, ExprNode::undefined, true);
            dataType.id = this->pathCallExpr->className;
            break;
    }

    return dataType;
}

void ExprNode::transformPathCallExpr(string className, ExprNode::Type type, bool isType) {
    ExprNode *cur = this;
    vector<string> namePath;

    while (cur->type == ExprNode::path_call_expr) {
        namePath.push_back(*cur->Name);
        cur = cur->expr_left;
    }

    reverse(all(namePath));
    ///TODO доделать

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
            }
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

    // cout << res << "\n";
    this->className = res;

}

bool ExprNode::isLiteral() {
    return this->type == ExprNode::int_lit || this->type == ExprNode::bool_lit ||
           this->type == ExprNode::char_lit || this->type == ExprNode::float_lit ||
           this->type == ExprNode::string_lit || this->type == ExprNode::raw_string_lit;
}


void ExprNode::transform() {

    switch (this->type) {

        case int_lit:
            break;
        case float_lit:
            break;
        case char_lit:
            break;
        case string_lit:
            break;
        case raw_string_lit:
            break;
        case bool_lit:
            break;
        case plus:
            break;
        case minus:
            break;
        case mul_expr:
            break;
        case div_expr:
            break;
        case mod:
            break;
        case or_:
            break;
        case and_:
            break;
        case asign:
            break;
        case equal:
            break;
        case not_equal:
            break;
        case greater:
            break;
        case less:
            break;
        case greater_equal:
            break;
        case less_equal:
            break;
        case uminus:
            break;
        case negotation:
            break;
        case question:
            break;
        case ustar:
            break;
        case link:
            break;
        case mut_link:
            break;
        case array_expr:
            break;
        case array_expr_auto_fill:
            break;
        case index_expr:
            break;
        case field_access_expr:
            break;
        case call_expr:
            break;
        case method_expr:
            break;
        case continue_expr:
            break;
        case break_expr:
            break;
        case break_with_val_expr:
            break;
        case range_right:
            break;
        case range_left:
            break;
        case range_expr:
            break;
        case return_expr:
            break;
        case id_:
            break;
        case self_expr:
            break;
        case if_expr_list:
            break;
        case if_expr:
            break;
        case loop_expr:
            break;
        case loop_while:
            break;
        case loop_for:
            break;
        case block_expr:
            break;
        case struct_expr:
            break;
        case struct_field_expr:
            break;
        case static_method:
            break;
        case tuple_expr:
            break;
        case super_expr:
            break;
        case path_call_expr:
            break;
        case add_if_block:
            break;
        case struct_creation:
            break;
        case as:
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
        case or_:
        case and_:
        case asign:
        case equal:
        case not_equal:
        case greater:
        case less:
        case greater_equal:
        case less_equal:

            if (this->expr_left->isEqualDataType(expr_list)) {
                throw Exception(Exception::NOT_EQUAL_DATA_TYPE, "NOT EQUAL DATATYPE");
            }

            if (!this->expr_left->isLiteral() || !this->expr_right->isLiteral()) {
                throw Exception(Exception::NOT_CONST, "Excepted CONST but it NOT CONST");
            }
            break;
        case uminus:
        case negotation:
        case as:
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
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool || this->expr_right->Bool;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }

            this->type = bool_lit;
            this->dataType.type = this->expr_left->dataType.type;
            break;
        case and_:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool && this->expr_right->Bool;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
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
            this->dataType.type = this->expr_left->dataType.type;

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
            this->dataType.type = this->expr_left->dataType.type;
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
            this->dataType.type = this->expr_left->dataType.type;
            break;
        case less:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool < this->expr_right->Bool;
            } else if (this->expr_left->dataType.type == DataType::int_) {
                this->Bool = this->expr_left->Int < this->expr_right->Int;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Bool = this->expr_left->Float < this->expr_right->Float;
            } else if (this->expr_left->dataType.type == DataType::char_) {
                this->Bool = this->expr_left->Char < this->expr_right->Char;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION");
            }
            this->type = bool_lit;
            this->dataType.type = this->expr_left->dataType.type;
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
            this->dataType.type = this->expr_left->dataType.type;

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
            this->dataType.type = this->expr_left->dataType.type;
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

            this->dataType.type = this->expr_left->dataType.type;
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
        case id_:
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
}


bool Node::isEqualDataType(Node *node) {
    return this->dataType.type == node->dataType.type;
}