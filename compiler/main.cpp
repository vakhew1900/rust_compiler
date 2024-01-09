//
// Created by arsen on 09.01.2024.
//
#include "parser_tab.h"
#include "classesnodes.h"
#include <iostream>
#include <fstream>

extern int yyparse();

int main(int argc, char** argv) {


#ifdef release
    if (argc != 2) {
        printf("Filename is not found");
        return 1;
    }

    const char *filename = argv[1];
#else
    const char *filename = "../tests/trait_error.rs";
//    const char *filename = "../tests/bubble_sort_rust.rs";
//    const char *filename = "../tests/check_cycle_break_continue_rust.rs";
//    const char *filename = "../tests/polymorphysm.rs";
#endif

//    FILE *file = fopen(filename, "r");
//    if (file == NULL) {
//        printf("File opening error");
//        return 1;
//    }
//
//    yyin = file;
    setFile(filename);
    yyparse();
//    fclose(file);

    string dot;
    global_program->toDot(dot);
    std::cout << dot << "\n";
    std::ofstream out("dot-tree.txt");

    global_program->makeAllConversions();
    string updatedDot;
    global_program->toDot(updatedDot);

    string res = ClassTable::Instance()->toString();
    out << updatedDot << "\n";
    cout << ClassTable::Instance()->toString() << "\n";

    ClassTable::createConstTableCSV();
    return 0;
}

