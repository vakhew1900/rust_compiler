//
// Created by arsen on 01.11.2023.
//
#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;

class ProgramNode;
class StmtListNode;
class StmtNode;
class ItemListEmptyNode;
class ItemListNode;
class ItemNode;
class SimpleItemNode;
class FuncStmtNode;
class DecFuncStmtNode;
class ImplFuncStmtNode;
class FuncParamNode;
class StructStmtNode;
class StructStructNode;
class StructFieldListEmptyNode;
class StructFieldListNode;
class StructFieldNode;
class TupleStructNode;
class TupleFieldListNode;
class EnumStmtNode;
class EnumItemListEmptyNode;
class EnumItemListNode;
class EnumItemNode;
class ImplStmtNode;
class AssociatedItemListEmptyNode;
class AssociatedItemListNode;
class AssociatedItemNode;
class TraitStmtNode;
class ConstStmtNode;
class ModuleStmtNode;
class LetStmtNode;
class ExprListEmptyNode;
class ExprListNode;
class ExprWithoutBlockNode;
class PathCallExprNode;
class StructExprFieldListEmptyNode;
class StructExprFieldListNode;
class StructExprFieldNode;
class ExprWithBlockNode;
class BlockExprNode;
class LoopExprNode;
class InfiniteLoopExprNode;
class PredicateLoopExprNode;
class IteratorLoopExprNode;
class IfExprNode;
class SimpleIfElseExprNode;
class SimpleIfExprNode;
class TypeNode;
class VisibilityNode;

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

