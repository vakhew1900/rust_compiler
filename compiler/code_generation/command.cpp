//
// Created by T0mmy on 13.01.2024.
//

#include "command.h"

std::vector<char> commandToBytes(Command command){
    return Int16ToBytes(uint16_t(command));
}