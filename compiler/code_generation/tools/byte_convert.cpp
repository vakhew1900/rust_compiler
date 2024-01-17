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


union Double {
    double num;
    char bytes[8];
};

std::vector<char> DoubleToBytes(double value) {
    Double d;
    d.num = value;
    std::vector<char> bytes(8);
    for(int i = 0; i < 8; i++){
        bytes[i] = d.bytes[i];
    }
    std::reverse(bytes.begin(), bytes.end());
    return bytes;
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