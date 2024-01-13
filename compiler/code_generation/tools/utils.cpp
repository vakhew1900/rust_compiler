//
// Created by T0mmy on 13.01.2024.
//
#include "utils.h"
#include "semantics/tools/tools.h"
void merge(std::vector<char> &bytes, const std::vector<char> &buffer){
    bytes.insert(bytes.end(), all(buffer));
}