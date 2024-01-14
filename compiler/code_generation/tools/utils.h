//
// Created by T0mmy on 10.01.2024.
//

#ifndef COMPILER_UTILS_H
#define COMPILER_UTILS_H
#include <cstdint>
#include "byte_convert.h"

enum class AccessFlags : uint16_t
{
    Public = 0x0001,
    Protected = 0x0004,
    Private = 0x0002,
    Static = 0x0008,
    Final = 0x0010,
    Super = 0x0020
};


enum class ArrayType : uint8_t
{
    Boolean = 4,
    Char = 5,
    Float = 6,
    Double = 7,
    Byte = 8,
    Short = 9,
    Int = 10,
    Long = 11
};

void merge(std::vector<char> &bytes, const std::vector<char> &buffer);
void merge(std::vector<bool> &bytes, const std::vector<bool> &buffer);
#endif //COMPILER_UTILS_H
