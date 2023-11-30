//
// Created by arsen on 27.10.2023.
//
#pragma once

#include <iostream>
#include <string>
#include <list>
#include "semantics/tools/datatype.h"
#include "semantics/tables/fieldtable.h"
#include "semantics/tools/tools.h"
#include "semantics/tables/methodtable.h"
#include "semantics/tables/classtable.h"

using namespace std;

class Node;

class ProgramNode; // ProgramNode
class ExprNode; // ExprNode
class ExprListNode; // expr_list_node
class StmtNode; // stmt_node
class StmtListNode; // stmt_list_node
class LetStmtNode; // let_stmt_node
class ItemNode; // decl_stmt_node
class ItemListNode; // -----
class StructFieldNode; // StructItemNode
class StructFieldListNode; // StructListNode
class StructStructNode; // StructNode
class EnumStmtNode; // EnumNode
class EnumItemNode; // enum_item_node
class EnumItemListNode; // enum_list_node
class FuncStmtNode; // function_node
class FuncParamNode; // function_param_node
class FuncParamListNode; // function_params_node
class ConstStmtNode; // const_stmt_node
class TraitNode; //trait_node
class ImplStmtNode; // impl_node
class TypeNode; // type_node
class ModuleStmtNode; // -----

enum Visibility {
    emptyVisibility, pub, crate, self, super
};


class Node {
public:
    int id;
    DataType dataType;
    MethodTableItem methodTableItem;
    FieldTableItem fieldTableItem;
    ClassTableItem classTableItem;
    virtual void getAllItems(string className);

};


class ProgramNode : public Node {
public:
    ItemListNode *item_list = NULL;

    ProgramNode(ItemListNode *item_list);

    void toDot(string &dot);

    void getAllItems(std::string className) override;
};

class TypeNode : public Node {
public:
    enum Type {
        emptyType_, int_, char_, string_, float_, bool_, id_, array_, path_call_expr_
    };
    Type type;
    string *name;
    TypeNode *typeArr = NULL;
    ExprNode *exprArr = NULL;

    ExprNode *pathCallExpr = NULL;

    //ф-ии
    TypeNode(Type type);

    TypeNode(Type type, TypeNode *type_node, ExprNode *expr);

    TypeNode(Type type, string *name);

    TypeNode(Type type, ExprNode *pathCallExpr);

    void toDot(string &dot);

};

class ExprNode : public Node {
public:
    enum Type {
        int_lit, float_lit, char_lit, string_lit, raw_string_lit, bool_lit,
        plus, minus, mul_expr, div_expr, mod, or_, and_, asign, equal, not_equal, greater, less, greater_equal,
        less_equal, uminus, negotation, question, ustar, link, mut_link, array_expr, array_expr_auto_fill, index_expr,
        field_access_expr, call_expr, method_expr,
        continue_expr, break_expr, break_with_val_expr, range_right, range_left, range_expr, return_expr,

        id_, self_expr, if_expr_list, if_expr, loop_expr, loop_while, loop_for, block_expr,
        struct_expr, struct_field_expr, static_method, tuple_expr, super_expr,
        path_call_expr, add_if_block, struct_creation, as
    };
    Type type;
    char Char = 0;
    string *String = NULL;
    string *RawString = NULL;
    int Int = 0;
    float Float = 0;
    bool Bool = false;
    string *ParentID = NULL;
    string *Name = NULL;

    ExprNode *expr_left = NULL;
    ExprNode *expr_right = NULL;
    ExprListNode *expr_list = NULL;
    ExprNode *body = NULL;
    ExprListNode *field_list = NULL;
    StmtListNode *stmt_list = NULL;

    list<ExprNode *> *ifList = NULL;
    ExprNode *else_body = NULL;

    TypeNode *typeNode = NULL;

    //ф-ии
    static ExprNode *OperatorExpr(Type type, ExprNode *left, ExprNode *right);

    static ExprNode *ExprFromBoolLiteral(Type type, bool value);

    static ExprNode *ExprFromIntLiteral(Type type, int value);

    static ExprNode *ExprFromFloatLiteral(Type type, float value);

    static ExprNode *ExprFromCharLiteral(Type type, char value);

    static ExprNode *ExprFromStringLiteral(Type type, string *value);

    static ExprNode *CallAccessExpr(Type type, string *name, ExprNode *expr, ExprListNode *expr_list);

    static ExprNode *StaticMethodExpr(Type type, string *name, string *parent_id, ExprListNode *expr_list);

    static ExprNode *ArrExprFromList(Type type, ExprListNode *expr_list);

    static ExprNode *ArrExprAutoFill(Type type, ExprNode *first, ExprNode *second);

    static ExprNode *RangeExpr(Type type, ExprNode *left, ExprNode *right);

    static ExprNode *IfExpr(Type type, ExprNode *condition, ExprNode *body, ExprNode *else_body);

    static ExprNode *CycleExpr(Type type, ExprNode *condition, ExprNode *body, string *id);

    static ExprNode *BlockExpr(Type type, ExprNode *body, StmtListNode *stmt_list);

    static ExprNode *StructExpr(Type type, string *name, ExprListNode *expr_list);

    static ExprNode *ExprFromStructField(Type type, string *name, ExprNode *expr);

    static ExprNode *TupleExpr(Type type, ExprNode *expr, int value); // tuple_expr
    static ExprNode *PathCallExpr(Type type, string *name, ExprNode *expr);

    static ExprNode *StaticMethod(Type type, ExprNode *expr, ExprListNode *expr_list);

    static ExprNode *FieldListAccess(Type type, ExprNode *expr, ExprListNode *field_list);

    static ExprNode *IfExpr(Type type, ExprNode *condition, ExprNode *body);

    static ExprNode *IfExprList(ExprNode *ifExpr);

    static ExprNode *AddIfBlock(ExprNode *ifExpr, ExprNode *someIfExpr);

    static ExprNode *AddElseBlock(ExprNode *ifExpr, ExprNode *else_body);

    static ExprNode *AsExpr(ExprNode *expr, TypeNode *typeNode);

    void toDot(string &dot, const string &pos = "");


};

class ExprListNode : public Node {
public:
    list<ExprNode *> *exprs = NULL;

    ExprListNode(ExprNode *expr);

    ExprListNode(ExprListNode *exprs);

    static ExprListNode *Append(ExprListNode *list, ExprNode *expr);

    void toDot(string &dot, const string &type = "expr_list");
};

class StmtNode : public Node {
public:
    enum Type {
        semicolon, expression, exprstmt, let, const_
    };
    Type type;
    ExprNode *expr = NULL;
    StmtNode *stmt = NULL;
    ItemNode *decl_stmt = NULL;
    LetStmtNode *let_stmt = NULL;

    /** LetStmt */
    enum LetType {
        noMut, mut
    };

    LetType let_type;
    string *name = NULL;
    TypeNode *typeChild = NULL;


    StmtNode();
    StmtNode(Type type, ExprNode *expr_node, ItemNode *decl_node, LetStmtNode *let_node);
    StmtNode(Type type, StmtNode *stmt);
    static StmtNode* ConstStmtToStmt(ConstStmtNode *node);

    void toDot(string &dot);
};

class StmtListNode : public Node {
public:
    list<StmtNode *> *stmts = NULL;

    StmtListNode(StmtNode *stmt);

    static StmtListNode *Append(StmtListNode *list, StmtNode *stmt);

    void toDot(string &dot, const string &type = "stmt_list");
};

class LetStmtNode : public Node {
public:
    enum Type {
        noMut, mut
    };
    Type let_type;
    string *name = NULL;
    TypeNode *type = NULL;
    ExprNode *expr = NULL;

    LetStmtNode(string *name, TypeNode *type, Type let_type, ExprNode *expr);

    void toDot(string &dot);
};

class ItemNode : public Node {
public:
    enum ItemType {
        enum_, function_, constStmt_, struct_, trait_, impl_, module_
    };

    enum ImplType {
        inherent, trait
    };
    ItemType item_type;
    Visibility visibility;


    string *name = NULL;
    TypeNode *returnType = NULL;
    FuncParamListNode *params = NULL;
    ExprNode *body = NULL;


    ImplType impl_type;
    TypeNode *type = NULL;


    StructFieldListNode *structItems = NULL;
    EnumItemListNode *enumItems = NULL;
    ItemListNode *items = NULL;

    ExprNode *expr = NULL;

    static ItemNode *DeclarationEnum(Visibility visibility, EnumStmtNode *node);

    static ItemNode *DeclarationFunction(Visibility visibility, FuncStmtNode *node);

    static ItemNode *DeclarationConst(Visibility visibility, ConstStmtNode *node);

    static ItemNode *DeclarationStruct(Visibility visibility, StructStructNode *node);

    static ItemNode *DeclarationImpl(Visibility visibility, ImplStmtNode *node);

    static ItemNode *DeclarationModule(Visibility visibility, ModuleStmtNode *node);

    static ItemNode *DeclarationTrait(Visibility visibility, TraitNode *node);

    static ItemNode *AddVisibility(Visibility visibility, ItemNode *itemNode);

    ItemNode(Visibility visibility, ItemNode *node);

    ItemNode();

    void toDot(string &dot);
};


class ItemListNode : public Node {
public:
    list<ItemNode *> *items = NULL;

    ItemListNode(ItemNode *item);

    ItemListNode(ItemListNode *list);

    static ItemListNode *Append(ItemListNode *list, ItemNode *item);


    void toDot(string &dot);
};

class ModuleStmtNode : public Node {
public:
    string *name = NULL;
    ItemListNode *items = NULL;

    ModuleStmtNode(string *name, ItemListNode *items);

    void toDot(string &dot);

};

class StructStructNode : public Node {
public:
    string *name = NULL;
    StructFieldListNode *items = NULL;

    StructStructNode(string *name, StructFieldListNode *items);

    void toDot(string &dot);

};

class StructFieldNode : public Node {
public:
    string *name = NULL;
    Visibility visibility;
    TypeNode *type = NULL;

    StructFieldNode(string *name, TypeNode *type, Visibility visibility);

    void toDot(string &dot);

};

class StructFieldListNode : public Node {
public:
    list<StructFieldNode *> *items = NULL;

    StructFieldListNode(StructFieldNode *item);

    StructFieldListNode(StructFieldListNode *list);

    static StructFieldListNode *Append(StructFieldListNode *list, StructFieldNode *item);

    void toDot(string &dot);
};

class EnumStmtNode : public Node {
public:
    string *name = NULL;
    EnumItemListNode *items = NULL;

    EnumStmtNode(string *name, EnumItemListNode *items);

    void toDot(string &dot);

};

class EnumItemNode : public Node {
public:
    Visibility visibility;
    string *name = NULL;
    ExprNode *expr = NULL;
    StructFieldListNode *struct_list = NULL;

    EnumItemNode(string *name, Visibility visibility, StructFieldListNode *struct_list, ExprNode *expr);

    EnumItemNode();

    void toDot(string &dot);

};

class EnumItemListNode : public Node {
public:
    list<EnumItemNode *> *items = NULL;

    EnumItemListNode(EnumItemNode *item);

    EnumItemListNode(EnumItemListNode *list);

    static EnumItemListNode *Append(EnumItemListNode *list, EnumItemNode *item);

    void toDot(string &dot);
};

class FuncStmtNode : public Node {
public:
    string *name = NULL;
    TypeNode *returnType = NULL;
    FuncParamListNode *params = NULL;
    ExprNode *body = NULL;

    FuncStmtNode(string *name, TypeNode *returnType, FuncParamListNode *params, ExprNode *body);

    void toDot(string &dot);
};

class FuncParamNode : public Node {
public:
    enum Type {
        noMut, mut, mut_ref, link
    };
    Type param_type;
    string *name = NULL;
    TypeNode *type = NULL;

    FuncParamNode(string *name, TypeNode *type, Type param_type);

    void toDot(string &dot);
};

class FuncParamListNode : public Node {
public:
    enum Type {
        self, self_ref, mut_self_ref, associated, static_
    };
    Type func_type;
    list<FuncParamNode *> *items = NULL;

    FuncParamListNode(FuncParamNode *item);

    FuncParamListNode(Type func_type, FuncParamNode *item);

    FuncParamListNode(FuncParamListNode *list);

    static FuncParamListNode *FunctionParamsFinal(Type func_type, FuncParamListNode *list);

    static FuncParamListNode *Append(FuncParamListNode *list, FuncParamNode *item);


    void toDot(string &dot);
};

class ConstStmtNode : public Node {
public:
    string *name = NULL;
    TypeNode *type = NULL;
    ExprNode *expr = NULL;

    static ConstStmtNode *ConstStmt(string *name, TypeNode *type, ExprNode *expr);

    void toDot(string &dot);
};

class TraitNode : public Node {
public:
    string *name = NULL;
    ItemListNode *items = NULL;

    TraitNode(string *name, ItemListNode *items);

    void toDot(string &dot);
};

class ImplStmtNode : public Node {
public:
    enum Type {
        inherent, trait
    };
    Type impl_type;
    string *name;
    TypeNode *type = NULL;
    ItemListNode *items = NULL;

    ImplStmtNode(Type impl_type, TypeNode *type, string *name, ItemListNode *list);

    void toDot(string &dot);
};

void connectVerticesDots(string &s, int parentId, int childId);

void createVertexDot(string &s, int id, string name = "", string type = "", string value = "", string visibility = "",
                     string pos = "");

string getVisibility(Visibility visibility);