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

    ProgramNode(ItemListNode* item_list);
    string* toDot();
    string* toXml();
};

class TypeNode{
public:
    enum Type{
        emptyType_, int_, char_, string_, float_, bool_, id_, array_
    };

    int id;
    Type type;
    TypeNode* typeArr = NULL;
    ExprNode* exprArr = NULL;

    //ф-ии
    TypeNode(Type type);
    TypeNode(Type type, TypeNode* type_node, ExprNode* expr);
    string* toDot();
    string* toXml();
};

class ExprNode{
public:
    enum Type{
        int_lit, float_lit, char_lit, string_lit, raw_string_lit,  bool_lit,
        plus, minus, mul_expr, div_expr, mod, or_, and_, asign, equal, not_equal, greater, less, greater_equal,
        less_equal, uminus, negotation, question, ustar, link, array_expr, array_expr_auto_fill, index_expr,
        field_access_expr, call_expr, method_expr,
        continue_expr, break_expr, range_right, range_left, range_expr, return_expr,

        id_, self_expr, if_expr, loop_expr, loop_while, loop_for, block_expr,
        struct_expr, struct_field_expr, static_method, tuple_expr, super_expr,
        path_call_expr, add_if_block
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
    StructFieldListNode* field_list = NULL;
    StmtListNode* stmt_list = NULL;

    //ф-ии
    static ExprNode* OperatorExpr(Type type, ExprNode* left, ExprNode* right);
    static ExprNode* ExprFromBoolLiteral(Type type, bool value);
    static ExprNode* ExprFromIntLiteral(Type type, int value);
    static ExprNode* ExprFromFloatLiteral(Type type, float value);
    static ExprNode* ExprFromCharLiteral(Type type, char value);
    static ExprNode* ExprFromStringLiteral(Type type, string* value);
    static ExprNode* CallAccessExpr(Type type, string* name, ExprNode* expr, ExprListNode* expr_list);
    static ExprNode* StaticMethodExpr(Type type, string* name, string* parent_id, ExprListNode* expr_list);
    static ExprNode* ArrExprFromList(Type type, ExprListNode* expr_list);
    static ExprNode* ArrExprAutoFill(Type type, ExprNode* first, ExprNode* second);
    static ExprNode* RangeExpr(Type type, ExprNode* left, ExprNode* right);
    static ExprNode* IfExpr(Type type, ExprNode* condition, ExprNode* body, ExprNode* else_body);
    static ExprNode* CycleExpr(Type type, ExprNode* condition, ExprNode* body, string* id);
    static ExprNode* BlockExpr(Type type, ExprListNode* expr_list);
    static ExprNode* StructExpr(Type type, string* name, ExprListNode* expr_list);

    static ExprNode* ExprFromStructField(Type type, string* name, ExprNode* expr);
    static ExprNode* TupleExpr(Type type, ExprNode* expr, int value); // tuple_expr
    static ExprNode* PathCallExpr(Type type, string* name, ExprNode* expr);
    static ExprNode* StaticMethod(Type type, ExprNode* expr, ExprListNode* expr_list);
    static ExprNode* FieldListAccess(Type type, ExprNode* expr, StructFieldListNode* field_list);
    static ExprNode* AddIfBlock(Type type, ExprNode* expr, ExprNode* condition, ExprNode* body);
    string* toDot();
    string* toXml();

};

class ExprListNode
{
public:
    int id;
    list<ExprNode*>* exprs = NULL;

    ExprListNode(ExprNode* expr);
    ExprListNode(ExprListNode* exprs);
    static void Append(ExprListNode* list, ExprNode* expr);

    string* toDot();
    string* toXml();
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

    string* toDot();
    string* toXml();
};

class StmtListNode
{
public:
    int id;
    list<StmtNode*>* stmts = NULL;

    StmtListNode(StmtNode* stmt);
    static void Append(StmtListNode* list, StmtNode* stmt);

    string* toDot();
    string* toXml();
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


    string* toDot();
    string* toXml();
};

class ItemNode{
public:
    enum Type
    {
        enum_, function_, constStmt_, struct_, trait_, impl_, module_
    };
    int id;
    Type type;
    Visibility visibility;

    FuncStmtNode* function_item;
    StructStructNode* struct_item;
    EnumStmtNode* enum_item;
    ImplStmtNode* impl_item;
    TraitNode* trait_item;
    ConstStmtNode* const_stmt_item;
    ModuleStmtNode* module_item;

    static ItemNode* DeclarationEnum(Visibility visibility, EnumStmtNode* node);
    static ItemNode* DeclarationFunction(Visibility visibility, FuncStmtNode* node);
    static ItemNode* DeclarationConst(Visibility visibility, ConstStmtNode* node);
    static ItemNode* DeclarationStruct(Visibility visibility, StructStructNode* node);
    static ItemNode* DeclarationImpl(Visibility visibility, ImplStmtNode* node);
    static ItemNode* DeclarationModule(Visibility visibility, ModuleStmtNode* node);

    string* toDot();
    string* toXml();
};

class ItemListNode
{
public:
    int id;
    list<ItemNode*>* items = NULL;

    ItemListNode(ItemNode* item);
    static void Append(ItemListNode* list, ItemNode* item);


    string* toDot();
    string* toXml();
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

    ModuleStmtNode(Type type, string* name, EnumItemListNode* items);

    string* toDot();
    string* toXml();
};

class StructStructNode{
public:
    int id;
    string* name = NULL;
    StructFieldListNode* items = NULL;

    StructStructNode(string* name, StructFieldListNode* items);
    string* toDot();
    string* toXml();
};

class StructFieldNode{
public:
    int id;
    string* name = NULL;
    Visibility visibility;
    TypeNode* type = NULL;

    StructFieldNode(string* name, TypeNode* type, Visibility visibility);
    string* toDot();
    string* toXml();
};

class StructFieldListNode{
public:
    int id;
    list<StructFieldNode*>* items = NULL;

    StructFieldListNode(StructFieldNode* item);
    StructFieldListNode(StructFieldListNode* list);
    static void Append(StructFieldListNode* list, StructFieldNode* item);

    string* toDot();
    string* toXml();
};

class EnumStmtNode{
public:
    int id;
    string* name = NULL;
    EnumItemListNode* items = NULL;

    EnumStmtNode(string* name, EnumItemListNode* items);
    string* toDot();
    string* toXml();
};

class EnumItemNode{
public:
    int id;
    Visibility visibility;
    string* name = NULL;
    ExprNode* expr = NULL;
    StructFieldListNode* struct_list = NULL;

    EnumItemNode(string* name, Visibility visibility, StructFieldListNode* struct_list, ExprNode* expr);
    EnumItemNode();
    string* toDot();
    string* toXml();
};

class EnumItemListNode{
public:
    int id;
    list<EnumItemNode*>* items = NULL;

    EnumItemListNode(EnumItemNode* item);
    EnumItemListNode(EnumItemListNode* list);
    static void Append(EnumItemListNode* list, EnumItemNode* item);

    string* toDot();
    string* toXml();
};

class FuncStmtNode{
public:
    int id;
    string* name = NULL;
    TypeNode* returnType = NULL;
    FuncParamListNode* params = NULL;
    ExprNode* body = NULL;

    FuncStmtNode(string* name, TypeNode* returnType, FuncParamListNode* params, ExprNode* body);
    string* toDot();
    string* toXml();
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

    FuncParamNode(string* name, TypeNode* type, Type param_type);

    string* toDot();
    string* toXml();
};

class FuncParamListNode{
public:
    enum Type{
        self, self_ref, mut_self_ref, associated
    };
    int id;
    Type func_type;
    list<FuncParamNode*>* items = NULL;

    FuncParamListNode(FuncParamNode* item);
    FuncParamListNode(FuncParamListNode* list);
    static FuncParamListNode* FunctionParamsFinal(Type func_type, FuncParamListNode* list);
    static void Append(FuncParamListNode* list, FuncParamNode* item);


    string* toDot();
    string* toXml();
};

class ConstStmtNode{
public:
    int id;
    string* name = NULL;
    TypeNode* type = NULL;
    ExprNode* expr = NULL;

    static ConstStmtNode* ConstStmt(string* name, TypeNode* type, ExprNode* expr);

    string* toDot();
    string* toXml();
};

class AssociatedItemNode{
public:
    int id;
    Visibility visibility;
    FuncStmtNode* fn = NULL;
    ConstStmtNode* const_stmt = NULL;

    AssociatedItemNode(Visibility vis, FuncStmtNode* fn, ConstStmtNode* const_stmt);

    string* toDot();
    string* toXml();
};

class TraitNode{
public:
    int id;
    string* name = NULL;
    AssociatedItemListNode* items = NULL;

    TraitNode(string* name, AssociatedItemListNode* items);

    string* toDot();
    string* toXml();
};

class AssociatedItemListNode{
public:
    int id;
    list<AssociatedItemNode*>* items = NULL;

    AssociatedItemListNode(AssociatedItemNode* item);
    AssociatedItemListNode(AssociatedItemListNode* list);
    static void Append(AssociatedItemListNode* list, AssociatedItemNode* item);


    string* toDot();
    string* toXml();
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

    ImplStmtNode(Type impl_type, TypeNode* type, string* name, AssociatedItemListNode* list);

    string* toDot();
    string* toXml();
};

