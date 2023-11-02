//
// Created by arsen on 27.10.2023.
//
#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;

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
class AssociatedItemNode; // associated_item_node
class AssociatedItemListNode; // associated_items_node
class TraitNode; //trait_node
class ImplStmtNode; // impl_node
class TypeNode; // type_node
class ModuleStmtNode; // -----

enum Visibility {
    emptyVisibility, pub, crate, self, super
};

class ProgramNode{
public:
    int id;
    ItemListNode* item_list = NULL;
};

class TypeNode{
public:
    enum Type{
        emptyType, int_, char_, string_, float_, bool_, id_, array_
    };

    int id;
    enum Type type;
    TypeNode* typeArr = NULL;
    ExprNode* exprArr = NULL;

    //ф-ии

};

class ExprNode{
public:
    // мб не нужны arrayexpr, array_expr_auto_fill
    enum Type{
        int_lit, float_lit, char_lit, string_lit, raw_string_lit,  bool_lit,
        plus, minus, mul_expr, div_expr, mod, or_, and_, asign, equal, not_equal, greater, less, greater_equal,
        less_equal, uminus, negotation, question, ustar, link, array_expr, array_expr_auto_fill, index_expr,
        field_access_expr, call_expr, method_expr,
        continue_expr, break_expr, range_right, range_left, range_expr, return_expr,

        id_, self_expr, if_expr, loop_expr, loop_while, loop_for, block_expr,
        struct_expr, struct_field_expr, static_method
    };

    int id;
    Type type;
    char Char = 0;
    string* String = NULL;
    string* RawString = NULL;
    int Int = 0;
    float Float = 0;
    bool Bool;
    string* ParentID = NULL;
    string* Name = NULL;

    ExprNode* expr_left = NULL;
    ExprNode* expr_right = NULL;
    ExprListNode* expr_list = NULL;
    ExprNode* body = NULL;
    ExprNode* else_body = NULL;
    StmtListNode* stmt_list = NULL;

    //ф-ии

};

class ExprListNode
{
public:
    int id;
    list<ExprNode*>* exprs = NULL;

    ExprListNode(ExprNode* expr);
    static void Append(ExprListNode* list, ExprNode* expr);
};

class StmtNode
{
public:
    enum Type
    {
        semicolon, expression, exprstmt, let
    };

    int id;
    Type type;
    ExprNode* expr = NULL;
    StmtNode* decl_stmt = NULL; //ExprStmt (Expr ';')
    LetStmtNode* let_stmt = NULL;

    StmtNode(Type type);
    StmtNode(Type type, LetStmtNode* letStmt);
    StmtNode(Type type, StmtNode* stmt);
    StmtNode(Type type, ExprNode* exprstmt); // Делаем ExprStmt
};

class StmtListNode
{
public:
    int id;
    list<StmtNode*>* stmts = NULL;

    StmtListNode(StmtNode* stmt);
    static void Append(StmtListNode* list, StmtNode* stmt);
};

class LetStmtNode{
public:
    enum Type
    {
        noMut, mut
    };
    int id;
    Type let_type;
    string* name = NULL;
    TypeNode* type = NULL;
    ExprNode* expr = NULL;
};

class ItemNode{
public:
    enum Type
    {
        enum_, function_, constStmt_, struct_, trait_, impl_, module_
    };
    int id;
    Type decl_type;
    Visibility visibility;

    FuncStmtNode* function_item;
    StructStructNode* struct_item;
    EnumStmtNode* enum_item;
    ImplStmtNode* impl_item;
    TraitNode* trait_item;
    ConstStmtNode* const_stmt_item;
    ModuleStmtNode* module_item;
};

class ItemListNode
{
public:
    int id;
    list<ItemNode*>* items = NULL;

    ItemListNode(ItemNode* item);
    static void Append(ItemListNode* list, ItemNode* item);
};

class ModuleStmtNode{
public:
    enum Type{
        semicolon, block
    };

    int id;
    Type type;
    string* name;
    EnumItemListNode* items = NULL;
};

class StructStructNode{
public:
    int id;
    string* name = NULL;
    StructFieldListNode* items = NULL;
};

class StructFieldNode{
public:
    int id;
    string* name = NULL;
    Visibility visibility;
    TypeNode* type = NULL;
};

class StructFieldListNode{
public:
    int id;
    list<StructFieldNode*>* items = NULL;

    StructFieldListNode(StmtNode* item);
    static void Append(StructFieldListNode* list, StructFieldNode* item);
};

class EnumStmtNode{
public:
    int id;
    string* name = NULL;
    EnumItemListNode* items = NULL;
};

class EnumItemNode{
public:
    int id;
    Visibility visibility;
    string* name = NULL;
    ExprNode* expr = NULL;
    StructFieldListNode* struct_list = NULL;
};

class EnumItemListNode{
public:
    int id;
    list<EnumItemNode*>* items = NULL;

    EnumItemListNode(EnumItemNode* item);
    static void Append(EnumItemListNode* list, EnumItemNode* item);
};

class FuncStmtNode{
public:
    int id;
    string* name = NULL;
    TypeNode* retutnType = NULL;
    FuncParamListNode* params = NULL;
    ExprNode* body = NULL;
};

class FuncParamNode{
public:
    enum Type{
        noMut, mut
    };
    int id;
    Type param_type;
    string* name = NULL;
    TypeNode* type = NULL;
};

class FuncParamListNode{
public:
    enum Type{
        self, self_ref, mut_self_ref, associated
    };
    int id;
    list<FuncParamNode*>* items = NULL;

    FuncParamListNode(FuncParamNode* item);
    static void Append(FuncParamListNode* list, FuncParamNode* item);
};

class ConstStmtNode{
public:
    int id;
    string* name = NULL;
    TypeNode* type = NULL;
    ExprNode* expr = NULL;
};

class AssociatedItemNode{
public:
    int id;
    Visibility visibility;
    FuncStmtNode* fn = NULL;
    ConstStmtNode* const_stmt = NULL;
};

class TraitNode{
public:
    int id;
    string* name = NULL;
    AssociatedItemListNode* items = NULL;
};

class AssociatedItemListNode{
public:
    int id;
    list<AssociatedItemNode*>* items = NULL;

    AssociatedItemListNode(AssociatedItemNode* item);
    static void Append(AssociatedItemListNode* list, AssociatedItemNode* item);
};

class ImplStmtNode{
public:
    enum Type{
        inherent, trait
    };
    int id;
    Type impl_type;
    string* name;
    TypeNode* type = NULL;
    AssociatedItemListNode* items = NULL;
};

