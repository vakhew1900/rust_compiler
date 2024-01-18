//
// Created by T0mmy on 10.01.2024.
//

#ifndef COMPILER_BYTE_CONVERTATION_H
#define COMPILER_BYTE_CONVERTATION_H

#include <vector>
#include <cstdint>
#define u2(x)  x.begin() + 2, x.end()

std::vector<char> IntToBytes(int value);

std::vector<char> DoubleToBytes(double value);

std::vector<char> Int16ToBytes(uint16_t value);

std::vector<char> FloatToBytes(float value);

#endif //COMPILER_BYTE_CONVERTATION_H
