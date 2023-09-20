#include <stdio.h>
#include "lex.yy.c"

int main()
{
    const char* filename = "E:\\4 course\\tl\\rust_compiler\\compiler\\test.txt";
    FILE *file = fopen(filename, "r");
    yyin = file;

    while (yylex() != 0);
    fclose(file);

    return 0;
}

