//
// Created by T0mmy on 12.01.2024.
//

#include "classesnodes.h"
#include "command.h"
#include "tools/byte_convert.h"
#include "tools/utils.h"

vector<char> Node::generate() {
    throw Exception(Exception::UNEXPECTED,"generate not realized method for id" + to_string(this->id));
}

vector<char> StmtNode::generate() {
    vector<char> bytes;
    vector<char> buffer;

    switch(this->type){

        case exprstmt:

            break;

        case let:
        case const_:

            if(this->expr != NULL){
                buffer = this->expr->generate();
                merge(bytes, buffer);

                switch(expr->dataType.type){

                    case DataType::int_:
                    case DataType::bool_:
                    case DataType::char_:
                        buffer = commandToBytes(Command::istore);
                        merge(bytes, buffer);
                        break;
                    case DataType::float_:
                        buffer = commandToBytes(Command::dstore);
                        merge(bytes, buffer);
                        break;
                    case DataType::string_:
                    case DataType::class_:
                    case DataType::array_:
                        buffer = commandToBytes(Command::astore);
                        merge(bytes, buffer);
                        break;

                    case DataType::undefined_:
                    case DataType::void_:
                        break;
                }
            }

            break;
        case semicolon:
        case expression:
            break;
    }

    // добаление номера перемнной
    buffer = IntToBytes(this->localVarNum);
    buffer.push_back(buffer.back());
    return bytes;
}

vector<char> ExprNode::generate() {

    vector<char> bytes;
    vector<char> buffer;

    switch(this->type){

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
        case path_call_expr:
            break;
        case struct_creation:
            break;

        case as:
            break;



        case arr_asign:
            break;
        case point_assign:
            break;

        case del_object:
            break;

        case crate_expr:
            break;

        default:
            break;
    }

    return bytes;
}

