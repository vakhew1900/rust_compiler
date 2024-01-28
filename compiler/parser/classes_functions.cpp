//
// Created by arsen on 27.10.2023.
//
#include "classesnodes.h"
#include "semantics/rtl/RTLContainer.h"

int globId = 0;

ProgramNode::ProgramNode(ItemListNode *item_list) {
    this->id = ++globId;
    this->line = 1;
    this->item_list = item_list;
}

TypeNode::TypeNode(Type type) {
    this->id = ++globId;
    this->line = LineNum::getLineNum();
    this->type = type;
}

TypeNode::TypeNode(Type type, TypeNode *type_node, ExprNode *expr) {
    this->id = ++globId;
    this->line = LineNum::getLineNum();
    this->type = type;
    this->typeArr = type_node;

    this->exprArr = expr;
}

TypeNode::TypeNode(Type type, string *name) {
    this->id = ++globId;
    this->line = LineNum::getLineNum();
    this->type = type;
    this->name = name;
}

TypeNode::TypeNode(Type type, ExprNode *pathCallExpr) {
    this->id = ++globId;
    this->line = LineNum::getLineNum();
    this->type = type;
    this->pathCallExpr = pathCallExpr;
}

// Expr from + - * / и тд
ExprNode *ExprNode::OperatorExpr(Type type, ExprNode *left, ExprNode *right) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->setLine(left);
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
    new_node->setLine(expr);

    return new_node;
}

ExprNode *ExprNode::ExprFromBoolLiteral(Type type, bool value) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->line = LineNum::getLineNum();
    new_node->type = type;
    new_node->Bool = value;
    return new_node;
}

ExprNode *ExprNode::ExprFromIntLiteral(Type type, int value) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->line = LineNum::getLineNum();
    new_node->type = type;
    new_node->Int = value;
    return new_node;
}

ExprNode *ExprNode::ExprFromFloatLiteral(Type type, float value) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->line = LineNum::getLineNum();
    new_node->type = type;
    new_node->Float = value;
    return new_node;
}

ExprNode *ExprNode::ExprFromCharLiteral(Type type, char value) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->line = LineNum::getLineNum();
    new_node->type = type;
    new_node->Char = value;
    return new_node;
}

ExprNode *ExprNode::ExprFromStringLiteral(Type type, string *value) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->line = LineNum::getLineNum();
    new_node->type = type;
    new_node->String = value;
    return new_node;
}

ExprNode *ExprNode::StaticMethod(Type type, ExprNode *expr, ExprListNode *expr_list) {
    auto *new_node = new ExprNode();
    new_node->setLine(expr);
    new_node->setLine(expr_list);
    new_node->id = ++globId;
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->expr_list = expr_list;
    return new_node;
}

ExprNode *ExprNode::FieldListAccess(Type type, ExprNode *expr, ExprListNode *field_list) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->setLine(expr);
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->field_list = field_list;
    return new_node;
}

ExprNode *ExprNode::CallAccessExpr(Type type, string *name, ExprNode *expr, ExprListNode *expr_list) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->setLine(expr);
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
    new_node->setLine(expr_list);
    new_node->type = type;
    new_node->Name = name;
    new_node->ParentID = parent_id;
    new_node->expr_list = expr_list;
    return new_node;
}

ExprNode *ExprNode::BlockExpr(Type type, ExprNode *body, StmtListNode *stmt_list) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->setLine(stmt_list);
    new_node->type = type;
    new_node->body = body;
    new_node->stmt_list = stmt_list;
    return new_node;
}

ExprNode *ExprNode::ArrExprFromList(Type type, ExprListNode *expr_list) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->setLine(expr_list);
    new_node->type = type;
    new_node->expr_list = expr_list;
    return new_node;
}

ExprNode *ExprNode::ArrExprAutoFill(Type type, ExprNode *first, ExprNode *second) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->setLine(first);
    new_node->type = type;
    new_node->expr_left = first;
    new_node->expr_right = second;
    return new_node;
}

ExprNode *ExprNode::TupleExpr(Type type, ExprNode *expr, int value) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->setLine(expr);
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->Int = value;
    return new_node;
}

ExprNode *ExprNode::CycleExpr(Type type, ExprNode *condition, ExprNode *body, string *id) {
    auto *new_node = new ExprNode();
    new_node->setLine(condition);
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
    new_node->setLine(left);
    new_node->type = type;
    new_node->expr_left = left;
    new_node->expr_right = right;
    return new_node;
}

ExprNode *ExprNode::IfExpr(Type type, ExprNode *condition, ExprNode *body) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->setLine(condition);
    new_node->type = type;
    new_node->expr_left = condition;
    new_node->body = body;


    return new_node;
}

ExprNode *ExprNode::IfExprList(ExprNode *ifExpr) {
    auto *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->setLine(ifExpr);
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
    new_node->setLine(expr);
    new_node->type = as;
    new_node->expr_left = expr;
    new_node->typeNode = typeNode;
    return new_node;
}

ExprNode *ExprNode::StructExpr(Type type, string *name, ExprListNode *expr_list) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->setLine(expr_list);
    new_node->type = type;
    new_node->expr_list = expr_list;
    new_node->Name = name;
    return new_node;
}

ExprNode *ExprNode::ExprFromStructField(Type type, string *name, ExprNode *expr) {
    ExprNode *new_node = new ExprNode();
    new_node->id = ++globId;
    new_node->setLine(expr);
    new_node->type = type;
    new_node->expr_left = expr;
    new_node->Name = name;
    return new_node;
}

// expr list
ExprListNode::ExprListNode(ExprNode *expr) {
    this->id = ++globId;
    this->setLine(expr);
    this->exprs = new list<ExprNode *>{expr};
}

ExprListNode::ExprListNode(ExprListNode *exprs_list) {
    this->id = ++globId;
    this->setLine(exprs_list);
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
    new_node->setLine(expr);
    new_node->setLine(type);
    new_node->id = ++globId;
    new_node->type = type;
    new_node->name = name;
    new_node->expr = expr;
    return new_node;
}

// Trait
TraitNode::TraitNode(string *name, ItemListNode *items) {
    this->id = ++globId;
    this->setLine(items);
    this->name = name;
    this->items = items;
}

TraitNode::TraitNode(string *name, ItemListNode *items, string *parentName) {
    this->id = ++globId;
    this->name = name;
    this->setLine(items);
    this->items = items;
    this->parentName = parentName;
}

//ImplNode
ImplStmtNode::ImplStmtNode(Type impl_type, TypeNode *type, ExprNode *exprNode, ItemListNode *list) {
    this->id = ++globId;
    this->setLine(exprNode);
    this->setLine(type);
    this->impl_type = impl_type;
    this->type = type;
    this->pathCallExpr = exprNode;
    this->items = list;
}

//Struct
StructStructNode::StructStructNode(string *name, StructFieldListNode *items) {
    this->id = ++globId;
    this->setLine(items);
    this->name = name;
    this->items = items;
}

StructFieldNode::StructFieldNode(string *name, TypeNode *type, Visibility visibility) {
    this->id = ++globId;
    this->name = name;
    this->line = LineNum::getLineNum();
    this->type = type;
    this->visibility = visibility;
}

StructFieldListNode::StructFieldListNode(StructFieldNode *item) {
    this->id = ++globId;
    this->line = LineNum::getLineNum();
    this->items = new list<StructFieldNode *>{item};
}

StructFieldListNode::StructFieldListNode(StructFieldListNode *list) {
    this->id = ++globId;
    this->setLine(list);
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
    this->setLine(body);
    this->setLine(params);
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
    this->setLine(type);
    this->name = name;
    this->type = type;
    this->param_type = param_type;
}

FuncParamListNode::FuncParamListNode(FuncParamNode *item) {
    this->id = ++globId;
    this->setLine(item);
    this->items = new list<FuncParamNode *>{item};
}

FuncParamListNode::FuncParamListNode(Type func_type, FuncParamNode *item) {
    this->id = ++globId;
    this->setLine(item);
    this->items = new list<FuncParamNode *>{item};
    this->func_type = func_type;
}

FuncParamListNode::FuncParamListNode(FuncParamListNode *list) {
    this->id = ++globId;
    this->setLine(list);
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
        new_node->setLine(list);
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
    this->setLine(items);
    this->name = name;
    this->items = items;
}

EnumItemNode::EnumItemNode(string *name, Visibility visibility, StructFieldListNode *struct_list, ExprNode *expr) {
    this->id = ++globId;
    this->setLine(expr);
    this->name = name;
    this->expr = expr;
    this->struct_list = struct_list;
    this->visibility = visibility;
}

EnumItemListNode::EnumItemListNode(EnumItemNode *item) {
    this->id = ++globId;
    this->setLine(item);
    this->items = new list<EnumItemNode *>{item};
}

EnumItemListNode::EnumItemListNode(EnumItemListNode *list) {
    this->id = ++globId;
    this->setLine(list);
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
    this->setLine(items);
    this->name = name;
    this->items = items;
}

// Items (declarations)
ItemNode *ItemNode::DeclarationEnum(Visibility visibility, EnumStmtNode *node) {
    ItemNode *new_node = new ItemNode();
    new_node->id = ++globId;
    new_node->item_type = enum_;
    new_node->setLine(node);
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
    new_node->setLine(node);

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
    new_node->setLine(node);

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
    new_node->setLine(node);

    new_node->item_type = struct_;
    new_node->visibility = visibility;

    new_node->name = node->name;
    new_node->structItems = node->items;

    return new_node;
}

ItemNode *ItemNode::DeclarationTrait(Visibility visibility, TraitNode *node) {
    ItemNode *new_node = new ItemNode();
    new_node->id = ++globId;
    new_node->setLine(node);
    new_node->item_type = trait_;
    new_node->visibility = visibility;

    new_node->name = node->name;
    new_node->items = node->items;
    new_node->parentName = node->parentName;

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
    new_node->setLine(node);

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
    new_node->setLine(node);

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
    this->setLine(item);
    this->items = new list<ItemNode *>{item};
}

ItemListNode::ItemListNode(ItemListNode *list) {
    this->id = ++globId;
    this->setLine(list);

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
    this->setLine(expr);
    this->setLine(type);
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
    this->setLine(item);
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
    this->setLine(expr_node);
    this->setLine(decl_node);
    this->setLine(let_node);

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
    this->setLine(stmt);
    this->type = type;
    this->stmt = stmt;
}

StmtNode *StmtNode::ConstStmtToStmt(ConstStmtNode *node) {
    StmtNode *new_node = new StmtNode();
    new_node->id = ++globId;
    new_node->setLine(node);
    new_node->type = const_;
    new_node->typeChild = node->type;
    new_node->expr = node->expr;
    new_node->name = node->name;
    return new_node;
}

ItemNode::ItemNode() {

}

ExprNode *ExprNode::DelObjectExpr(ExprNode *expr) {
    ExprNode *node = new ExprNode();
    node->id = ++globId;
    node->type = ExprNode::del_object;
    node->expr_left = expr;

    if (expr->isVar() == false) {
        throw Exception(Exception::UNEXPECTED, "it`s not a var", expr->line);
    }

    if (expr->dataType.type != DataType::class_ && expr->dataType.type != DataType::array_) {
        throw Exception(Exception::UNEXPECTED, "type should be array_ or class_", expr->line);
    }

    return node;
}
