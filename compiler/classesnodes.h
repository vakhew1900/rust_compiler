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
   void toDot(string &dot);
   void toXml(string &xml);
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
    void toDot(string &dot);
    void toXml(string &xml);
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
    ExprListNode* field_list = NULL;
    StmtListNode* stmt_list = NULL;

    list<ExprNode*>* ifList = NULL;
    ExprNode* else_body = NULL;

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
    static ExprNode* BlockExpr(Type type, ExprNode* body, StmtListNode* stmt_list);
    static ExprNode* StructExpr(Type type, string* name, ExprListNode* expr_list);

    static ExprNode* ExprFromStructField(Type type, string* name, ExprNode* expr);
    static ExprNode* TupleExpr(Type type, ExprNode* expr, int value); // tuple_expr
    static ExprNode* PathCallExpr(Type type, string* name, ExprNode* expr);
    static ExprNode* StaticMethod(Type type, ExprNode* expr, ExprListNode* expr_list);
    static ExprNode* FieldListAccess(Type type, ExprNode* expr, ExprListNode* field_list);

    static ExprNode* IfExpr(Type type, ExprNode* condition, ExprNode* body);
    static ExprNode* AddIfBlock(ExprNode* ifExpr, ExprNode* someIfExpr);
    static ExprNode* AddElseBlock(ExprNode* ifExpr, ExprNode* else_body);

    void toDot(string &dot, const string &type = "");
    void toXml(string &xml);

};

class ExprListNode
{
public:
    int id;
    list<ExprNode*>* exprs = NULL;

    ExprListNode(ExprNode* expr);
    ExprListNode(ExprListNode* exprs);
    static ExprListNode* Append(ExprListNode* list, ExprNode* expr);

   void toDot(string &dot, const string &type="expr_list");
   void toXml(string &xml);
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
    StmtNode* stmt = NULL;
    ItemNode* decl_stmt = NULL;
    LetStmtNode* let_stmt = NULL;

    StmtNode(Type type, ExprNode* expr_node, ItemNode* decl_node, LetStmtNode* let_node);
    StmtNode(Type type, StmtNode* stmt);

   void toDot(string &dot);
   void toXml(string &xml);
};

class StmtListNode
{
public:
    int id;
    list<StmtNode*>* stmts = NULL;

    StmtListNode(StmtNode* stmt);
    static StmtListNode* Append(StmtListNode* list, StmtNode* stmt);

   void toDot(string &dot, const string &type = "stmt_list");
   void toXml(string &xml);
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

    LetStmtNode(string* name, TypeNode* type, Type let_type, ExprNode* expr);

   void toDot(string &dot);
   void toXml(string &xml);
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
    ItemNode* item_node;

    static ItemNode* DeclarationEnum(Visibility visibility, EnumStmtNode* node);
    static ItemNode* DeclarationFunction(Visibility visibility, FuncStmtNode* node);
    static ItemNode* DeclarationConst(Visibility visibility, ConstStmtNode* node);
    static ItemNode* DeclarationStruct(Visibility visibility, StructStructNode* node);
    static ItemNode* DeclarationImpl(Visibility visibility, ImplStmtNode* node);
    static ItemNode* DeclarationModule(Visibility visibility, ModuleStmtNode* node);
    static ItemNode* DeclarationTrait(Visibility visibility, TraitNode* node);
    ItemNode(Visibility visibility, ItemNode* node);
    ItemNode();

   void toDot(string &dot);
   void toXml(string &xml);
};


class ItemListNode
{
public:
    int id;
    list<ItemNode*>* items = NULL;

    ItemListNode(ItemNode* item);
    ItemListNode(ItemListNode* list);
    static ItemListNode* Append(ItemListNode* list, ItemNode* item);


   void toDot(string &dot);
   void toXml(string &xml);
};

class ModuleStmtNode{
public:
    enum Type{
        semicolon, block, empty
    };

    int id;
    Type type;
    string* name;
    ItemListNode* items = NULL;

    ModuleStmtNode(Type type, string* name, ItemListNode* items);

    void toDot(string &dot);
    void toXml(string &xml);
};

class StructStructNode{
public:
    int id;
    string* name = NULL;
    StructFieldListNode* items = NULL;

    StructStructNode(string* name, StructFieldListNode* items);
    void toDot(string &dot);
    void toXml(string &xml);
};

class StructFieldNode{
public:
    int id;
    string* name = NULL;
    Visibility visibility;
    TypeNode* type = NULL;

    StructFieldNode(string* name, TypeNode* type, Visibility visibility);
    void toDot(string &dot);
    void toXml(string &xml);
};

class StructFieldListNode{
public:
    int id;
    list<StructFieldNode*>* items = NULL;

    StructFieldListNode(StructFieldNode* item);
    StructFieldListNode(StructFieldListNode* list);
    static StructFieldListNode* Append(StructFieldListNode* list, StructFieldNode* item);

   void toDot(string &dot);
   void toXml(string &xml);
};

class EnumStmtNode{
public:
    int id;
    string* name = NULL;
    EnumItemListNode* items = NULL;

    EnumStmtNode(string* name, EnumItemListNode* items);
    void toDot(string &dot);
    void toXml(string &xml);
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
   void toDot(string &dot);
   void toXml(string &xml);
};

class EnumItemListNode{
public:
    int id;
    list<EnumItemNode*>* items = NULL;

    EnumItemListNode(EnumItemNode* item);
    EnumItemListNode(EnumItemListNode* list);
    static EnumItemListNode* Append(EnumItemListNode* list, EnumItemNode* item);

   void toDot(string &dot);
   void toXml(string &xml);
};

class FuncStmtNode{
public:
    int id;
    string* name = NULL;
    TypeNode* returnType = NULL;
    FuncParamListNode* params = NULL;
    ExprNode* body = NULL;

    FuncStmtNode(string* name, TypeNode* returnType, FuncParamListNode* params, ExprNode* body);
   void toDot(string &dot);
   void toXml(string &xml);
};

class FuncParamNode{
public:
    enum Type{
        noMut, mut, mut_ref, link
    };
    int id;
    Type param_type;
    string* name = NULL;
    TypeNode* type = NULL;

    FuncParamNode(string* name, TypeNode* type, Type param_type);

   void toDot(string &dot);
   void toXml(string &xml);
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
    static FuncParamListNode* Append(FuncParamListNode* list, FuncParamNode* item);


   void toDot(string &dot);
   void toXml(string &xml);
};

class ConstStmtNode{
public:
    int id;
    string* name = NULL;
    TypeNode* type = NULL;
    ExprNode* expr = NULL;

    static ConstStmtNode* ConstStmt(string* name, TypeNode* type, ExprNode* expr);

   void toDot(string &dot);
   void toXml(string &xml);
};

class AssociatedItemNode{
public:
    int id;
    Visibility visibility;
    FuncStmtNode* fn = NULL;
    ConstStmtNode* const_stmt = NULL;

    AssociatedItemNode(Visibility vis, FuncStmtNode* fn, ConstStmtNode* const_stmt);

   void toDot(string &dot);
   void toXml(string &xml);
};

class TraitNode{
public:
    int id;
    string* name = NULL;
    AssociatedItemListNode* items = NULL;

    TraitNode(string* name, AssociatedItemListNode* items);

   void toDot(string &dot);
  void toXml(string &xml);
};

class AssociatedItemListNode{
public:
    int id;
    list<AssociatedItemNode*>* items = NULL;

    AssociatedItemListNode(AssociatedItemNode* item);
    AssociatedItemListNode(AssociatedItemListNode* list);
    static AssociatedItemListNode* Append(AssociatedItemListNode* list, AssociatedItemNode* item);


   void toDot(string &dot);
   void toXml(string &xml);
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

   void toDot(string &dot);
   void toXml(string &xml);
};

void connectVerticesDots(string &s, int parentId, int childId);
void createVertexDot(string &s, int id, string name="", string type="", string value = "", string visibility = "");