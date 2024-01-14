//
// Created by T0mmy on 12.01.2024.
//

#include "classesnodes.h"
#include "command.h"
#include "tools/byte_convert.h"
#include "tools/utils.h"

vector<char> Node::generate() {
    throw Exception(Exception::UNEXPECTED, "generate not realized method for id" + to_string(this->id));
}

vector<char> StmtNode::generate() {
    vector<char> bytes;
    vector<char> buffer;

    switch (this->type) {

        case exprstmt:

            break;

        case let:
        case const_:

            if (this->expr != NULL) {
                buffer = this->expr->generate();
                merge(bytes, buffer);

                switch (expr->dataType.type) {

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
    int index = -1;

    const int gotoCommandSize = 3;
    const int binaryCommandSize = 2;
    const int unaryCommandSize = 1;

    switch (this->type) {

        case int_lit:
            bytes = generateInt(this->Int);
            break;
        case float_lit:
            buffer = commandToBytes(Command::ldc_w);
            merge(bytes, buffer);
            index = ClassTable::addFloatToConstTable(curClassName, this->Float);
            buffer = Int16ToBytes(index);
            merge(bytes, buffer);
            break;
        case char_lit:
            buffer = commandToBytes(Command::bipush);
            merge(bytes, buffer);
            buffer = IntToBytes(this->Char);
            bytes.push_back(buffer.back()); // нужен как раз последний байт
            break;
        case string_lit:
        case raw_string_lit:
            buffer = commandToBytes(Command::ldc_w);
            merge(bytes, buffer);
            index = ClassTable::addStringToConstTable(curClassName, *this->String);
            buffer = Int16ToBytes(index);
            merge(bytes, buffer);
            break;
        case bool_lit:
            if (this->Bool) {
                bytes = commandToBytes(Command::iconst_1);
            } else {
                bytes = commandToBytes(Command::iconst_0);
            }
            break;

        case plus:
            merge(bytes, this->expr_left->generate());
            merge(bytes, this->expr_right->generate());

            if (this->dataType.isInt()) {
                merge(bytes, commandToBytes(Command::iadd));
            } else {
                merge(bytes, commandToBytes(Command::dadd));
            }
            break;
        case minus:
            merge(bytes, this->expr_left->generate());
            merge(bytes, this->expr_right->generate());

            if (this->dataType.isInt()) {
                merge(bytes, commandToBytes(Command::isub));
            } else {
                merge(bytes, commandToBytes(Command::dsub));
            }
            break;
        case mul_expr:
            merge(bytes, this->expr_left->generate());
            merge(bytes, this->expr_right->generate());

            if (this->dataType.isInt()) {
                merge(bytes, commandToBytes(Command::imul));
            } else {
                merge(bytes, commandToBytes(Command::dmul));
            }

            break;
        case div_expr:
            merge(bytes, this->expr_left->generate());
            merge(bytes, this->expr_right->generate());

            if (this->dataType.isInt()) {
                merge(bytes, commandToBytes(Command::idiv));
            } else {
                merge(bytes, commandToBytes(Command::ddiv));
            }
            break;
        case mod:
            merge(bytes, this->expr_left->generate());
            merge(bytes, this->expr_right->generate());
            merge(bytes, commandToBytes(Command::irem));
            break;
        case uminus:
            merge(bytes, this->expr_left->generate());
            if (this->dataType.isInt()) {
                merge(bytes, commandToBytes(Command::ineg));
            } else {
                merge(bytes, commandToBytes(Command::dneg));
            }
            break;

        case negotation:
            merge(bytes, this->expr_left->generate());
            merge(bytes, commandToBytes(Command::iconst_0));
            merge(bytes, commandToBytes(Command::iand));
            break;

        case or_: {
            vector<char> left = this->expr_left->generate();
            vector<char> right = this->expr_left->generate();

            merge(bytes, left);
            merge(bytes, commandToBytes(Command::iconst_1));
            merge(bytes, commandToBytes(Command::ifne)); // 1
            int sz = gotoCommandSize + gotoCommandSize; // размер
            merge(bytes, Int16ToBytes(sz)); //

            sz = gotoCommandSize + right.size() + unaryCommandSize + gotoCommandSize; // = 8;
            merge(bytes, commandToBytes(Command::goto_)); // 4
            merge(bytes, Int16ToBytes(sz));

            merge(bytes, right); // 7
            merge(bytes, commandToBytes(Command::iconst_1)); // 8
            merge(bytes, commandToBytes(Command::ifne)); //  9
            merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize  + unaryCommandSize));

            merge(bytes, commandToBytes(Command::iconst_1)); // 12
            merge(bytes, commandToBytes(Command::goto_)); // 13

            merge(bytes, Int16ToBytes(unaryCommandSize + gotoCommandSize));

            merge(bytes, commandToBytes(Command::iconst_0)); // 16
            merge(bytes, commandToBytes(Command::dup)); // сделал, чтобы был переход на следующую команду 17
            merge(bytes, commandToBytes(Command::pop));

        }
            break;

        case and_:  {
            vector<char> left = this->expr_left->generate();
            vector<char> right = this->expr_left->generate();

            merge(bytes, left);
            merge(bytes, commandToBytes(Command::iconst_0));
            merge(bytes, commandToBytes(Command::ifne)); // 1
            int sz = gotoCommandSize + gotoCommandSize; // размер
            merge(bytes, Int16ToBytes(sz)); //

            sz = gotoCommandSize + right.size() + unaryCommandSize + gotoCommandSize; // = 8;
            merge(bytes, commandToBytes(Command::goto_)); // 4
            merge(bytes, Int16ToBytes(sz));

            merge(bytes, right); // 7
            merge(bytes, commandToBytes(Command::iconst_0)); // 8
            merge(bytes, commandToBytes(Command::ifne)); //  9
            merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize  + unaryCommandSize));

            merge(bytes, commandToBytes(Command::iconst_0)); // 12
            merge(bytes, commandToBytes(Command::goto_)); // 13

            merge(bytes, Int16ToBytes(unaryCommandSize + gotoCommandSize));

            merge(bytes, commandToBytes(Command::iconst_1)); // 16
            merge(bytes, commandToBytes(Command::dup)); // сделал, чтобы был переход на следующую команду 17
            merge(bytes, commandToBytes(Command::pop));

        }
            break;


        case asign:
        {
            buffer = expr_left->generate();

            switch (expr_left->dataType.type) {

                case DataType::int_:
                    break;
                case DataType::float_:
                    break;
                case DataType::char_:
                    break;
                case DataType::bool_:
                    break;
                case DataType::string_:
                    break;
                case DataType::class_:
                    break;
                case DataType::array_:
                    break;
                case DataType::void_:
                    break;
            }
        }
            break;
        case arr_asign:
            break;
        case point_assign:
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

        case link:
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
        case range_left:
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

        case del_object:
            break;

        case crate_expr:
            break;

        default:
            break;
    }

    return bytes;
}


vector<char> ExprNode::generateInt(int value) {
    vector<char> bytes;
    vector<char> buffer;

    if (value <= INT16_MAX && value >= INT16_MIN) {
        buffer = commandToBytes(Command::sipush);
        merge(bytes, buffer);
        buffer = Int16ToBytes(value);
        merge(bytes, buffer);
    } else {
        buffer = commandToBytes(Command::ldc_w);
        merge(bytes, buffer);
        int index = ClassTable::addIntToConstTable(curClassName, value);
        buffer = Int16ToBytes(index);
        merge(bytes, buffer);
    }

    return bytes;
}