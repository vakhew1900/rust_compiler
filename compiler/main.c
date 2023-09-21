#include <stdio.h>
#include <locale.h>
#include "lex.yy.c"

int main()
{

    setlocale(LC_ALL, "Rus");
    const char* filename = "E:\\4 course\\tl\\rust_compiler\\compiler\\testRustProgramm.rs";
    FILE *file = fopen(filename, "r");
    yyin = file;

    while (yylex() != 0);
    fclose(file);

    return 0;
}

