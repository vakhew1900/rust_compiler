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