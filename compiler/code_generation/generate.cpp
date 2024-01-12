//
// Created by T0mmy on 12.01.2024.
//

#include "classesnodes.h"

vector<char> Node::generate() {
    throw Exception(Exception::UNEXPECTED,"generate not realized method for id" + to_string(this->id));
}