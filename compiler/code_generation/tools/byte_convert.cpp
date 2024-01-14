//
// Created by T0mmy on 10.01.2024.
//

#include "byte_convert.h"
#include <vector>

std::vector<char> IntToBytes(int value) {
    std::vector<char> arrayOfByte(4);
    for (int i = 0; i < 4; ++i) {
        arrayOfByte[3 - i] = (value >> (i * 8));
    }
    return arrayOfByte;
}


std::vector<char> DoubleToBytes(double value) {
    int  doubleSize = 8;
    std::vector<char> arrayOfByte(doubleSize);

    for (int i = 0; i < sizeof(double); ++i)
        arrayOfByte[doubleSize - 1 - i] = ((char*)&value)[i];
    return arrayOfByte;
}

std::vector<char> Int16ToBytes(uint16_t value) {
    std::vector<char> bytes = IntToBytes(value);
    bytes = std::vector<char>(u2(bytes));
    return bytes;
}

std::vector<char> FloatToBytes(float value) {
    std::vector<char> arrayOfByte(4);

    for (int i = 0; i < sizeof(float); ++i)
        arrayOfByte[3 - i] = ((char*)&value)[i];
    return arrayOfByte;
}