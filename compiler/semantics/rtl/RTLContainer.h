//
// Created by T0mmy on 04.01.2024.
//

#ifndef COMPILER_RTLCONTAINER_H
#define COMPILER_RTLCONTAINER_H


#include "semantics/tables/classtable.h"

class RTLContainer {
public:
    RTLContainer();
    ClassTableItem rtlClass;
    void addReadFunctions();
    void addPrintFunctions();
    void addStringFunctions();
    void addCharAt();
};


#endif //COMPILER_RTLCONTAINER_H
