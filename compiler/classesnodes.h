//
// Created by arsen on 01.11.2023.
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
class ImplStmtNode; // impl_node
class TypeNode; // type_node
class VisibilityNode; // enum visibility vis;

class ProgramNode{

};

class StmtListNode{
public:

    int id;
    StmtListNode(Type type);
    static void Append(string* identifier, Expression* expression = NULL);
};

class StmtNode
{
public:
    enum Type
    {
        type_Empty,
        type_LetStmt,
        type_ExprStmt
    };

    int id;
    Type type;
    LetStmtNode* stmtNode = NULL;

    StmtNode(Type type, LetStmtNode* letStmt);
    StmtNode(Type type, ExprStmtNode* exprStmt);
};

