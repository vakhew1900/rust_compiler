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
class VisibilityNode; // enum visibility vis;

class ProgramNode{

};

class VisibilityNode{
    enum Type {
        emptyVisibility, pub, crate, self, super, big_self
    };

    int id;
    Type type;

    VisibilityNode(Type type);
};

class TypeNode{
public:
    enum Type{
        emptyType, int_, char_, string_, float_, bool_, id_, array_
    };

    int id;
    enum Type type;
    TypeNode* typeArr;
    ExprNode* exprArr;
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
    ExprNode* next = NULL;
    ExprListNode* expr_list = NULL;
    ExprNode* body = NULL;
    ExprNode* else_body = NULL;
    StmtListNode* stmt_list = NULL;
};

class ExprListNode
{
public:
    int id;
    list<ExprNode*>* exprs = NULL;

    ExprListNode(ExprNode* expr);
    static void Append(ExprListNode* list, ExprNode* expr);
};

//!---до этой отметки сделано по черновому---!//


