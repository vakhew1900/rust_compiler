//
// Created by T0mmy on 28.01.2024.
//

#include "classesnodes.h"

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
            value = *(this->String);
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
        case undefined:
            type = varName(undefined);
            break;
        case field_call:
            type = varName(field_call);
            break;
        case method_call:
            type = varName(method_call);
            break;
        case arr_asign:
            type = varName(arr_asign);
            break;
        case point_assign:
            type = varName(point_assign);
            break;
        case del_object:
            type = varName(del_object);
            break;
        case crate_expr:
            type = varName(crate_expr);
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

    if (this->expr_middle != NULL) {
        connectVerticesDots(dot, this->id, this->expr_middle->id);
        this->expr_middle->toDot(dot, "expr_middle");
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

        for (auto elem: *this->ifList) {
            connectVerticesDots(dot, this->id, elem->id);
            elem->toDot(dot, "condition" + to_string(ifCount++));
        }
    }

    if (this->else_body != NULL) {
        connectVerticesDots(dot, this->id, this->else_body->id);
        this->else_body->toDot(dot, "else_body");
    }

    if (this->deleteExprList != NULL && this->deleteExprList->exprs != NULL) {
        for (auto elem: *this->deleteExprList->exprs) {
            elem->toDot(dot, "delete_elem");
        }
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

            if (this->isHaveParent()) {
                type += " parent=" + *this->parentName;
            }
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
                 " [label=\"name=" + name + " " + type + value + visibility + pos + "id=" + to_string(id) + " dtype=" +
                 this->dataType.toString() + "\"];\n";

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