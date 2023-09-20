%option noyywrap
%option never-interactive

/* templates */
DIGIT [0-9]

/* start condition */
%x STRING
%x COMMENT
%x ML_COMMENT

%{
	#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
%}

%%

/* ==================== KEYWORDS ==================== */

%%

int main()
{
    const char* filename = "test.txt";
    FILE *file = fopen(filename, "r");
    yyin = file;

    while (yylex() != 0);
    fclose(file);

    return 0;
}
