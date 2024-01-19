//
// Created by T0mmy on 12.01.2024.
//

#include "classesnodes.h"
#include "command.h"
#include "tools/byte_convert.h"
#include "tools/utils.h"

vector<int> breakVec;
vector<int> continueVec;

vector<char> Node::generate() {
    throw Exception(Exception::UNEXPECTED, "generate not realized method for id" + to_string(this->id));
}

vector<char> StmtNode::generate() {
    vector<char> bytes;
    vector<char> buffer;

    switch (this->type) {

        case exprstmt:
            merge(bytes, this->expr->generate());
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
                        buffer = commandToBytes(Command::fstore);
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

            // добаление номера перемнной
            buffer = IntToBytes(this->localVarNum);
            bytes.push_back(buffer.back());
            break;
        case semicolon:
        case expression:
            break;
    }


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
                merge(bytes, commandToBytes(Command::fadd));
            }
            break;
        case minus:
            merge(bytes, this->expr_left->generate());
            merge(bytes, this->expr_right->generate());

            if (this->dataType.isInt()) {
                merge(bytes, commandToBytes(Command::isub));
            } else {
                merge(bytes, commandToBytes(Command::fsub));
            }
            break;
        case mul_expr:
            merge(bytes, this->expr_left->generate());
            merge(bytes, this->expr_right->generate());

            if (this->dataType.isInt()) {
                merge(bytes, commandToBytes(Command::imul));
            } else {
                merge(bytes, commandToBytes(Command::fmul));
            }

            break;
        case div_expr:
            merge(bytes, this->expr_left->generate());
            merge(bytes, this->expr_right->generate());

            if (this->dataType.isInt()) {
                merge(bytes, commandToBytes(Command::idiv));
            } else {
                merge(bytes, commandToBytes(Command::fdiv));
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
                merge(bytes, commandToBytes(Command::fneg));
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
            merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize + unaryCommandSize));

            merge(bytes, commandToBytes(Command::iconst_1)); // 12
            merge(bytes, commandToBytes(Command::goto_)); // 13

            merge(bytes, Int16ToBytes(unaryCommandSize + gotoCommandSize));

            merge(bytes, commandToBytes(Command::iconst_0)); // 16

        }
            break;

        case and_: {
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
            merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize + unaryCommandSize));

            merge(bytes, commandToBytes(Command::iconst_0)); // 12
            merge(bytes, commandToBytes(Command::goto_)); // 13

            merge(bytes, Int16ToBytes(unaryCommandSize + gotoCommandSize));

            merge(bytes, commandToBytes(Command::iconst_1)); // 16
        }
            break;


        case asign: {
            bytes = this->expr_right->generate();
            switch (expr_left->dataType.type) {

                case DataType::int_:
                case DataType::char_:
                case DataType::bool_:
                    merge(bytes, commandToBytes(Command::istore));
                    break;
                case DataType::float_:
                    merge(bytes, commandToBytes(Command::fstore));
                    break;

                case DataType::string_:
                case DataType::class_:
                case DataType::array_:
                    merge(bytes, commandToBytes(Command::astore));
                    break;

                case DataType::void_:
                case DataType::undefined_:
                    throw Exception(Exception::UNEXPECTED, "Ты как в генерацию проскачила гадина???", this->line);
                    break;
            }

            bytes.push_back(Int16ToBytes(this->expr_left->localVarNum).back());
        }
            break;
        case arr_asign: {
            vector<char> left = this->expr_left->generate();
            vector<char> right = this->expr_right->generate();
            vector<char> index = this->expr_middle->generate();

            merge(bytes, left);
            merge(bytes, index);
            merge(bytes, right);

            switch (this->expr_left->dataType.type) {


                case DataType::int_:
                case DataType::bool_:
                    merge(bytes, commandToBytes(Command::iastore));
                    break;
                case DataType::char_:
                    merge(bytes, commandToBytes(Command::castore));
                    break;
                case DataType::float_:
                    merge(bytes, commandToBytes(Command::fastore));
                    break;

                case DataType::string_:
                case DataType::class_:
                case DataType::array_:
                    merge(bytes, commandToBytes(Command::aastore));
                    break;
                case DataType::void_:
                case DataType::undefined_:
                    break;
            }

        }
            break;
        case point_assign: {

            vector<char> left = this->expr_left->generate();
            vector<char> right = this->expr_right->generate();
            string field = *this->expr_middle->Name;
            DataType fieldDatatype = ClassTable::Instance()->getField(this->expr_left->dataType.id, field).dataType;
            int fieldPosition = ClassTable::addFieldRefToConstTable(curClassName, this->expr_left->dataType.id, field,
                                                                    dataType);

            merge(bytes, left);
            merge(bytes, right);
            merge(bytes, commandToBytes(Command::putfield));
            merge(bytes, Int16ToBytes(fieldPosition));
            break;
        }

        case link:
        case mut_link:
            bytes = this->expr_left->generate();
            break;

        case equal: {
            vector<char> left = this->expr_left->generate();
            vector<char> right = this->expr_right->generate();
            merge(bytes, left);
            merge(bytes, right);

            switch (this->expr_left->dataType.type) {

                case DataType::int_:
                case DataType::char_:
                case DataType::bool_:

                    merge(bytes, commandToBytes(Command::if_icmpne)); // 1
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_1)); // 4
                    merge(bytes, commandToBytes(Command::goto_)); // 5
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_0)); // 8
                    break;

                case DataType::float_: ///TODO получше присмотреться к этой ерунде
                    merge(bytes, commandToBytes(Command::fcmpg)); // 1
                    merge(bytes, commandToBytes(Command::ifne)); // 2
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_1)); // 5
                    merge(bytes, commandToBytes(Command::goto_)); // 6
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_0)); // 9
                    break;

                case DataType::string_:
                case DataType::class_:
                case DataType::array_:
                    break;

                case DataType::undefined_:
                case DataType::void_:
                    break;
            }

            break;
        }
        case not_equal: {

            vector<char> left = this->expr_left->generate();
            vector<char> right = this->expr_right->generate();

            merge(bytes, left);
            merge(bytes, right);

            switch (this->expr_left->dataType.type) {

                case DataType::int_:
                case DataType::char_:
                case DataType::bool_:

                    merge(bytes, commandToBytes(Command::if_icmpeq)); // 1
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_1)); // 4
                    merge(bytes, commandToBytes(Command::goto_)); // 5
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_0)); // 8
                    break;

                case DataType::float_: ///TODO получше присмотреться к этой ерунде
                    merge(bytes, commandToBytes(Command::fcmpg)); // 1
                    merge(bytes, commandToBytes(Command::ifeq)); // 2
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_1)); // 5
                    merge(bytes, commandToBytes(Command::goto_)); // 6
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_0)); // 9
                    break;

                case DataType::string_:
                case DataType::class_:
                case DataType::array_:
                    break;

                case DataType::undefined_:
                case DataType::void_:
                    break;
            }
            break;
        }
        case greater: {

            vector<char> left = this->expr_left->generate();
            vector<char> right = this->expr_right->generate();

            merge(bytes, left);
            merge(bytes, right);

            switch (this->expr_left->dataType.type) {

                case DataType::int_:
                case DataType::char_:
                case DataType::bool_:

                    merge(bytes, commandToBytes(Command::if_icmple)); // 1
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_1)); // 4
                    merge(bytes, commandToBytes(Command::goto_)); // 5
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_0)); // 8
                    break;

                case DataType::float_: ///TODO получше присмотреться к этой ерунде
                    merge(bytes, commandToBytes(Command::fcmpg)); // 1
                    merge(bytes, commandToBytes(Command::ifle)); // 2
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_1)); // 5
                    merge(bytes, commandToBytes(Command::goto_)); // 6
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_0)); // 9
                    break;

                case DataType::string_:
                case DataType::class_:
                case DataType::array_:
                    break;

                case DataType::undefined_:
                case DataType::void_:
                    break;
            }
            break;
        }

        case less: {

            vector<char> left = this->expr_left->generate();
            vector<char> right = this->expr_right->generate();

            merge(bytes, left);
            merge(bytes, right);

            switch (this->expr_left->dataType.type) {

                case DataType::int_:
                case DataType::char_:
                case DataType::bool_:

                    merge(bytes, commandToBytes(Command::if_icmpge)); // 1
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_1)); // 4
                    merge(bytes, commandToBytes(Command::goto_)); // 5
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_0)); // 8
                    break;

                case DataType::float_: ///TODO получше присмотреться к этой ерунде
                    merge(bytes, commandToBytes(Command::fcmpg)); // 1
                    merge(bytes, commandToBytes(Command::ifge)); // 2
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_1)); // 5
                    merge(bytes, commandToBytes(Command::goto_)); // 6
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_0)); // 9
                    break;

                case DataType::string_:
                case DataType::class_:
                case DataType::array_:
                    break;

                case DataType::undefined_:
                case DataType::void_:
                    break;
            }
            break;
        }

        case greater_equal: {

            vector<char> left = this->expr_left->generate();
            vector<char> right = this->expr_right->generate();

            merge(bytes, left);
            merge(bytes, right);

            switch (this->expr_left->dataType.type) {

                case DataType::int_:
                case DataType::char_:
                case DataType::bool_:

                    merge(bytes, commandToBytes(Command::if_icmple)); // 1
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_1)); // 4
                    merge(bytes, commandToBytes(Command::goto_)); // 5
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_0)); // 8
                    break;

                case DataType::float_: ///TODO получше присмотреться к этой ерунде
                    merge(bytes, commandToBytes(Command::fcmpg)); // 1
                    merge(bytes, commandToBytes(Command::iflt)); // 2
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_1)); // 5
                    merge(bytes, commandToBytes(Command::goto_)); // 6
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_0)); // 9
                    break;

                case DataType::string_:
                case DataType::class_:
                case DataType::array_:
                    break;

                case DataType::undefined_:
                case DataType::void_:
                    break;
            }
            break;
        }
        case less_equal: {

            vector<char> left = this->expr_left->generate();
            vector<char> right = this->expr_right->generate();

            merge(bytes, left);
            merge(bytes, right);

            switch (this->expr_left->dataType.type) {

                case DataType::int_:
                case DataType::char_:
                case DataType::bool_:

                    merge(bytes, commandToBytes(Command::if_icmpgt)); // 1
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_1)); // 4
                    merge(bytes, commandToBytes(Command::goto_)); // 5
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_0)); // 8
                    break;

                case DataType::float_: ///TODO получше присмотреться к этой ерунде
                    merge(bytes, commandToBytes(Command::fcmpg)); // 1
                    merge(bytes, commandToBytes(Command::ifgt)); // 2
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize + gotoCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_1)); // 5
                    merge(bytes, commandToBytes(Command::goto_)); // 6
                    merge(bytes, Int16ToBytes(gotoCommandSize + unaryCommandSize));
                    merge(bytes, commandToBytes(Command::iconst_0)); // 9
                    break;

                case DataType::string_:
                case DataType::class_:
                case DataType::array_:
                    break;

                case DataType::undefined_:
                case DataType::void_:
                    break;
            }
            break;
        }


        case return_expr:
            bytes = generateReturn(this->expr_left);
            break;


        case continue_expr:
            merge(bytes, commandToBytes(Command::goto_));
            continueVec.push_back(bytes.size() - 1);
            merge(bytes, Int16ToBytes(3));
            break;
        case break_expr:
            merge(bytes, commandToBytes(Command::goto_));
            breakVec.push_back(bytes.size() - 1);
            merge(bytes, Int16ToBytes(3));
            break;
        case break_with_val_expr:
            merge(bytes, this->expr_left->generate());
            merge(bytes, commandToBytes(Command::goto_));
            breakVec.push_back(bytes.size() - 1);
            merge(bytes, Int16ToBytes(3)); // заглушка;
            break;


        case block_expr: {

            if (this->stmt_list != NULL && this->stmt_list->stmts != NULL) {
                for (auto stmt: *this->stmt_list->stmts) {
                    merge(bytes, stmt->generate());
                }
            }


            if (ClassTable::Instance()->getMethod(curClassName, curMethodName).body == this) {
                merge(bytes, generateReturn(this->body)); ///TODO изменил, походу ошибка. Если что Арсений откатывай)
            }
            else  if (this->body != NULL) {
                merge(bytes, this->body->generate());
            }

            break;
        }

        case id_:
        case self_expr:
            switch (this->dataType.type) {

                case DataType::int_:
                case DataType::char_:
                case DataType::bool_:
                    merge(bytes, commandToBytes(Command::iload));
                    break;

                case DataType::float_:
                    merge(bytes, commandToBytes(Command::fload));
                    break;

                case DataType::string_:
                case DataType::class_:
                case DataType::array_:
                    merge(bytes, commandToBytes(Command::aload));
                    break;
                case DataType::undefined_:
                case DataType::void_:
                    break;
            }

            bytes.push_back(IntToBytes(this->localVarNum).back());
            break;

        case index_expr: {
            vector<char> array = this->expr_left->generate();
            vector<char> index = this->expr_right->generate();

            merge(bytes, array);
            merge(bytes, index);

            switch (this->dataType.type) {

                case DataType::int_:
                case DataType::char_:
                case DataType::bool_:
                    merge(bytes, commandToBytes(Command::iaload));
                    break;
                case DataType::float_:
                    merge(bytes, commandToBytes(Command::faload));
                    break;
                case DataType::string_:
                case DataType::class_:
                case DataType::array_:
                    merge(bytes, commandToBytes(Command::aaload));
                    break;
                case DataType::undefined_:
                case DataType::void_:
                    break;
            }
            break;
        }

        case field_access_expr: {
            vector<char> object = this->expr_left->generate();
            string fieldName = *this->Name;
            int fieldPosition = ClassTable::addFieldRefToConstTable(curClassName, this->expr_left->dataType.id,
                                                                    fieldName,
                                                                    dataType);
            merge(bytes, object);
            merge(bytes, commandToBytes(Command::getfield));
            merge(bytes, Int16ToBytes(fieldPosition));
            break;
        }
        case method_expr: {
            merge(bytes, this->expr_left->generate());
            string methodName = *this->Name;
            vector<DataType> params;
            string className = this->expr_left->dataType.id;
            DataType returnDataType = ClassTable::getMethodDeep(className, methodName).returnDataType;
            if (this->expr_list != NULL) {
                for (auto &elem: *this->expr_list->exprs) {
                    params.push_back(elem->dataType);
                    merge(bytes, elem->generate());
                }
            }

            int methodPosition = ClassTable::addMethodRefToConstTable(curClassName, className, methodName, params,
                                                                      returnDataType);
            merge(bytes, commandToBytes(Command::invokevirtual));
            merge(bytes, Int16ToBytes(methodPosition));
            break;
        }

        case static_method: {
            string className = this->expr_left->className;
            string methodName = *this->expr_middle->Name;

            vector<DataType> params;
            DataType returnDataType = ClassTable::getMethodDeep(className, methodName).returnDataType;

            if (this->expr_list != NULL) {
                for (auto &elem: *this->expr_list->exprs) {
                    params.push_back(elem->dataType);
                    merge(bytes, elem->generate());
                }
            }

            int methodPosition = ClassTable::addMethodRefToConstTable(curClassName, className, methodName, params,
                                                                      returnDataType);
            merge(bytes, commandToBytes(Command::invokestatic));
            merge(bytes, Int16ToBytes(methodPosition));
            break;
        }

        case path_call_expr: {
            string className = this->expr_left->className;
            string fieldName = *this->expr_middle->Name;
            DataType dataType = this->dataType;

            int fieldPosition = ClassTable::addFieldRefToConstTable(curClassName, this->expr_left->dataType.id,
                                                                    fieldName,
                                                                    dataType);
            merge(bytes, commandToBytes(Command::getstatic));
            merge(bytes, Int16ToBytes(fieldPosition));
            break;
        }
        case as: {
            merge(bytes, this->expr_left->generate());
            if (!this->expr_left->dataType.isEquals(this->dataType)) {
                switch (this->expr_left->dataType.type) {

                    case DataType::int_:
                        if (this->dataType.isChar()) {
                            merge(bytes, commandToBytes(Command::i2c));
                        }
                        if (this->dataType.isFloat()) {
                            merge(bytes, commandToBytes(Command::i2f));
                        }
                        break;
                    case DataType::float_:
                        if (this->dataType.isInt()) {
                            merge(bytes, commandToBytes(Command::f2i));
                        }
                        break;

                    case DataType::char_:
                    case DataType::bool_:
                    case DataType::string_:
                    case DataType::class_:
                    case DataType::array_:
                    case DataType::undefined_:
                    case DataType::void_:
                        break;
                }
            }
        }
            break;

        case struct_creation: {
            string className = this->expr_left->className;
            int classPosition = ClassTable::addClassToConstTable(curClassName, className);

            merge(bytes, commandToBytes(Command::new_));
            merge(bytes, Int16ToBytes(classPosition));
            merge(bytes, commandToBytes(Command::dup));

            int initPosition = ClassTable::addMethodRefToConstTable(curClassName, className,
                                                                    ConstTable::init,
                                                                    vector<DataType>(),
                                                                    DataType(DataType::void_));
            merge(bytes, commandToBytes(Command::invokespecial));
            merge(bytes, Int16ToBytes(initPosition));

            for (auto elem: *this->field_list->exprs) {
                elem->className = className;
                merge(bytes, elem->generate());
            }

            merge(bytes, commandToBytes(Command::pop));
            break;
        }
        case struct_field_expr: {
            string fieldName = *this->Name;
            int fieldPosition = ClassTable::addFieldRefToConstTable(curClassName, this->className, fieldName,
                                                                    this->expr_left->dataType);

            merge(bytes, commandToBytes(Command::dup));
            merge(bytes, this->expr_left->generate());
            merge(bytes, commandToBytes(Command::putfield));
            merge(bytes, Int16ToBytes(fieldPosition));
            break;
        }

        case array_expr: {

            DataType arrDataType = this->dataType.getArrDataType();

            //вывод всего размера массива
            for (int i = this->dataType.arrLength.size() - 1; i >= 0; i--) {
                int length = this->dataType.arrLength[i];
                merge(bytes, this->generateInt(length));
            }

            switch (arrDataType.type) {

                case DataType::int_:
                case DataType::bool_:
                    merge(bytes, commandToBytes(Command::newarray));
                    bytes.push_back((char) ArrayType::Int);
                    break;
                case DataType::float_:
                    merge(bytes, commandToBytes(Command::newarray));
                    bytes.push_back((char) ArrayType::Float);
                    break;

                case DataType::char_:
                    merge(bytes, commandToBytes(Command::newarray));
                    bytes.push_back((char) ArrayType::Char);
                    break;

                case DataType::string_: {
                    merge(bytes, commandToBytes(Command::anewarray));
                    int position = ClassTable::addClassToConstTable(curClassName, ConstTable::stringClassName);
                    merge(bytes, Int16ToBytes(position));
                    break;
                }

                case DataType::class_: {
                    merge(bytes, commandToBytes(Command::anewarray));
                    int position = ClassTable::addClassToConstTable(curClassName, arrDataType.id);
                    merge(bytes, Int16ToBytes(position));
                    break;
                }
                case DataType::array_: {
                    merge(bytes, commandToBytes(Command::multianewarray));
                    int position = ClassTable::addClassToConstTable(curClassName, this->dataType.toConstTableFormat());
                    merge(bytes, Int16ToBytes(position));
                    bytes.push_back(IntToBytes(this->arrDataType.arrDeep).back());
                    break;
                }
                case DataType::undefined_:
                case DataType::void_:
                    break;
            }


            int cur = 0;
            for (auto elem: *this->expr_list->exprs) {
                merge(bytes, commandToBytes(Command::dup));
                merge(bytes, generateInt(cur));
                merge(bytes, elem->generate());
                switch (elem->dataType.type) {
                    case DataType::int_:
                    case DataType::bool_:
                        merge(bytes, commandToBytes(Command::iastore));
                        break;

                    case DataType::char_:
                        merge(bytes, commandToBytes(Command::castore));
                        break;

                    case DataType::float_:
                        merge(bytes, commandToBytes(Command::fastore));
                        break;

                    case DataType::string_:
                    case DataType::class_:
                    case DataType::array_:
                        merge(bytes, commandToBytes(Command::aastore));
                        break;
                }
                cur++;
            }

            break;
        }

        case del_object:
            if (!this->expr_left->dataType.isSimple() && this->expr_left->isVar()) {
                merge(bytes, commandToBytes(Command::aconst_null));
                merge(bytes, commandToBytes(Command::astore));
                bytes.push_back(Int16ToBytes(this->expr_left->localVarNum).back());
            }
            break;

        case if_expr_list: {

            if (this->else_body != NULL) {
                buffer = else_body->generate();
            }

            vector<char> secondBuffer;
            for (auto it = ifList->rbegin(); it != ifList->rend(); it++) {
                auto elem = *it;
                vector<char> condition = elem->expr_left->generate();
                vector<char> body = elem->body->generate();

                if (buffer.size()) {
                    merge(body, commandToBytes(Command::goto_));
                    int sz = buffer.size() + gotoCommandSize;
                    merge(body, Int16ToBytes(sz));
                }

                merge(secondBuffer, condition);// 1
                merge(secondBuffer, commandToBytes(Command::ifeq));// 1
                int sz = body.size() + gotoCommandSize;
                merge(secondBuffer, Int16ToBytes(sz));
                merge(secondBuffer, body);
                merge(secondBuffer, buffer);
                buffer = secondBuffer;
                secondBuffer.clear();
            }

            bytes = buffer;
            break;
        }
        case loop_expr: {
            auto tempBreakVec = breakVec;
            auto tempContinueVec = continueVec;
            breakVec.clear();
            continueVec.clear();
            vector<char> body = this->body->generate();
            merge(body, commandToBytes(Command::goto_));
            vector<char> position = IntToBytes(-body.size());
            body.insert(body.end(), u2(position)); ///TODO если не получится то придумать другую функцию

            fillBreaks(body, breakVec);
            fillContinues(body, breakVec);

            breakVec = tempBreakVec;
            continueVec = tempContinueVec;

            bytes = body;
            break;
        }
        case loop_while: {
            auto tempBreakVec = breakVec;
            auto tempContinueVec = continueVec;
            breakVec.clear();
            continueVec.clear();
            vector<char> condition = this->expr_left->generate();
            vector<char> body = this->body->generate();

            merge(condition, commandToBytes(Command::ifeq));
            int sz = gotoCommandSize + body.size() + gotoCommandSize;
            merge(condition, Int16ToBytes(sz));

            merge(body, commandToBytes(Command::goto_));
            sz = condition.size() + body.size() - 1;
            vector<char> position = IntToBytes(-sz);
            body.insert(body.end(), u2(position)); ///TODO если не получится то придумать другую функцию

            merge(bytes, condition);
            merge(bytes, body);

            fillBreaks(body, breakVec);
            fillContinues(body, breakVec);

            breakVec = tempBreakVec;
            continueVec = tempContinueVec;
        }
        case loop_for: {
            auto tempBreakVec = breakVec;
            auto tempContinueVec = continueVec;
            breakVec.clear();
            continueVec.clear();

            if (this->expr_left->type == range_expr) {
                bytes = generateFor();
            } else {
                bytes = generateForEach();
            }

            breakVec = tempBreakVec;
            continueVec = tempContinueVec;
            break;
        }


        case crate_expr:
        case range_right:
        case range_left:
        case range_expr:
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


vector<char> ExprNode::generateReturn(ExprNode *exprNode) {

    vector<char> bytes;

    if (exprNode == NULL) {
        bytes = commandToBytes(Command::return_);
    } else {
        merge(bytes, exprNode->generate());
        switch (exprNode->dataType.type) {

            case DataType::int_:
            case DataType::char_:
            case DataType::bool_:
                merge(bytes, commandToBytes(Command::ireturn));
                break;

            case DataType::float_:
                merge(bytes, commandToBytes(Command::freturn));
                break;

            case DataType::string_:
            case DataType::class_:
            case DataType::array_:
                merge(bytes, commandToBytes(Command::areturn));
                break;

            case DataType::void_:
                merge(bytes, commandToBytes(Command::return_));
                break;
            case DataType::undefined_:
                break;
        }
    }

    return bytes;
}


void ExprNode::fillBreaks(vector<char> &body, vector<int> breakVec, int shift) {

    for (auto elem: breakVec) {
        int exitPosition = body.size() - elem + shift;
        vector<char> position = Int16ToBytes(exitPosition);
        body[elem + 1] = position[0];
        body[elem + 2] = position[2];
    }
}

void ExprNode::fillContinues(vector<char> &body, vector<int> continueVec, int shift) {

    for (auto elem: continueVec) {
        int exitPosition = body.size() - 3 - elem + shift; //TODO проверить на то ли значение сдвигается
        vector<char> position = Int16ToBytes(exitPosition);
        body[elem + 1] = position[0];
        body[elem + 2] = position[2];
    }
}

vector<char> ExprNode::generateFor() {

    vector<char> bytes;

    vector<char> initValue = this->expr_left->expr_left->generate();
    vector<char> endValue = this->expr_left->expr_right->generate();
    int valueNum = Node::getVarNumber(this->body, curClassName, curMethodName, *this->Name);

    // Первая инициализация
    merge(bytes, initValue);
    merge(bytes, commandToBytes(Command::istore));
    bytes.push_back(IntToBytes(valueNum).back());

    // body
    vector<char> body = this->body->generate();
    merge(body, commandToBytes(Command::iinc));
    body.push_back(IntToBytes(valueNum).back());
    body.push_back(IntToBytes(1).back());

    // условие
    vector<char> condition = commandToBytes(Command::iload);
    bytes.push_back(IntToBytes(valueNum).back());
    merge(condition, endValue);
    merge(condition, commandToBytes(Command::if_icmpne));
    int sz = body.size() + 3;
    merge(condition, Int16ToBytes(sz));

    merge(body, commandToBytes(Command:: goto_));
    sz =  condition.size() + body.size() - 1;
    vector<char> position = IntToBytes(- sz);
    body.insert(body.end(), u2(position));

    fillBreaks(body, breakVec);
    fillContinues(body, continueVec, -3);

    merge(bytes, condition);
    merge(bytes, body);

    return bytes;
}

vector<char> ExprNode::generateForEach() {

    vector<char> bytes;

    vector<char> initValue = Int16ToBytes(0);
    vector<char> endValue = this->expr_left->generate();
    merge(endValue, commandToBytes(Command::arraylength));

    int valueNum = Node::getVarNumber(this->body, curClassName, curMethodName, *this->Name);

    // Первая инициализация
    merge(bytes, initValue);
    merge(bytes, commandToBytes(Command::istore));



    // body
    /// первоначальная инициализация переменной
    DataType arrDataType = this->expr_left->dataType.getArrDataType();
    vector<char> body;
    merge(body, this->expr_left->generate());
    merge(body, commandToBytes(Command::iload));
    bytes.push_back(IntToBytes(loopCounterVar).back());

    switch (arrDataType.type) {

        case DataType::int_:
        case DataType::char_:
        case DataType::bool_:
            merge(bytes, commandToBytes(Command::iaload));
            break;
        case DataType::float_:
            merge(bytes, commandToBytes(Command::faload));
            break;
        case DataType::string_:
        case DataType::class_:
        case DataType::array_:
            merge(bytes, commandToBytes(Command::aaload));
            break;
        case DataType::undefined_:
        case DataType::void_:
            break;
    }

    merge(body, this->body->generate());
    merge(body, commandToBytes(Command::iinc));
    body.push_back(IntToBytes(valueNum).back());
    body.push_back(IntToBytes(1).back());

    // условие
    vector<char> condition = commandToBytes(Command::iload);
    bytes.push_back(IntToBytes(localVarNum).back());
    merge(condition, endValue);
    merge(condition, commandToBytes(Command::if_icmpne));
    int sz = body.size() + 3;
    merge(condition, Int16ToBytes(sz));

    merge(body, commandToBytes(Command:: goto_));
    sz =  condition.size() + body.size() - 1;
    vector<char> position = IntToBytes(- sz);
    body.insert(body.end(), u2(position));

    fillBreaks(body, breakVec);
    fillContinues(body, continueVec, -3);

    merge(bytes, condition);
    merge(bytes, body);

    return bytes;
}