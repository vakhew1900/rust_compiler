%option noyywrap
%option never-interactive

DIGIT [0-9]

%x CHAR
%x STRING
%x ML_COMMENT

%{
	#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    char str[1024];
    int lineNumber = 1;
%}

%%

%{
    void removeUnderline();
    void removeType(char *typeName);
	void convertCharacterCodeToString(char characterCode[], int startPosition, char *string);
%}

\n { lineNumber++; }
" " { }

as { printf("Found KW_AS: %s\n", yytext); }
break { printf("Found KW_BREAK: %s\n", yytext); }
const { printf("Found KW_CONST: %s\n", yytext); }
continue { printf("Found KW_CONTINUE: %s\n", yytext); }
crate { printf("Found KW_CRATE: %s\n", yytext); }
else { printf("Found KW_ELSE: %s\n", yytext); }
enum { printf("Found KW_ENUM: %s\n", yytext); }
extern { printf("Found KW_EXTERN: %s\n", yytext); }
false { printf("Found KW_FALSE: %s\n", yytext); }
fn { printf("Found KW_FN: %s\n", yytext); }
for { printf("Found KW_FOR: %s\n", yytext); }
if { printf("Found KW_IF: %s\n", yytext); }
impl { printf("Found KW_IMPL: %s\n", yytext); }
in { printf("Found KW_IN: %s\n", yytext); }
let { printf("Found KW_LET: %s\n", yytext); }
loop { printf("Found KW_LOOP: %s\n", yytext); }
match { printf("Found KW_MATCH: %s\n", yytext); }
mod { printf("Found KW_MOD: %s\n", yytext); }
move { printf("Found KW_MOVE: %s\n", yytext); }
mut { printf("Found KW_MUT: %s\n", yytext); }
pub { printf("Found KW_PUB: %s\n", yytext); }
ref { printf("Found KW_REF: %s\n", yytext); }
return { printf("Found KW_RETURN: %s\n", yytext); }
self { printf("Found KW_SELFVALUE: %s\n", yytext); }
Self { printf("Found KW_SELFTYPE: %s\n", yytext); }
static { printf("Found KW_STATIC: %s\n", yytext); }
struct { printf("Found KW_STRUCT: %s\n", yytext); }
super { printf("Found KW_SUPER: %s\n", yytext); }
trait { printf("Found KW_TRAIT: %s\n", yytext); }
true  { printf("Found KW_TRUE: %s\n", yytext); }
type { printf("Found KW_TYPE: %s\n", yytext); }
unsafe { printf("Found KW_UNSAFE: %s\n", yytext); }
use { printf("Found KW_USE: %s\n", yytext); }
where { printf("Found KW_WHERE: %s\n", yytext); }
while { printf("Found KW_WHILE: %s\n", yytext); }


bool { printf("Found TYPE_BOOL: %s\n", yytext); }
i32 { printf("Found TYPE_I32: %s\n", yytext); }
i64 { printf("Found TYPE_I64: %s\n", yytext); }
f32 { printf("Found TYPE_F32: %s\n", yytext); }
f64 { printf("Found TYPE_F64: %s\n", yytext); }
String { printf("Found TYPE_STRING: %s\n", yytext); }
char { printf("Found TYPE_CHAR: %s\n", yytext); }


"+" { printf("Found OPERATOR_PLUS: %s\n", yytext); }
"-" { printf("Found OPERATOR_MINUS: %s\n", yytext); }
"*" { printf("Found OPERATOR_MUL: %s\n", yytext); }
"/" { printf("Found OPERATOR_DIV: %s\n", yytext); }
"%" { printf("Found OPERATOR_MOD: %s\n", yytext); }

"=" { printf("Found OPERATOR_ASSIGNMENT: %s\n", yytext); }
"==" { printf("Found OPERATOR_EQUAL: %s\n", yytext); }
"!=" { printf("Found OPERATOR_NOT_EQUAL: %s\n", yytext); }
"<" { printf("Found OPERATOR_LESS: %s\n", yytext); }
">" { printf("Found OPERATOR_MORE: %s\n", yytext); }
"<=" { printf("Found OPERATOR_LESS_OR_EQUAL: %s\n", yytext); }
">=" { printf("Found OPERATOR_MORE_OR_EQUAL: %s\n", yytext); }

"&" { printf("Found OPERATOR_AMPERSAND: %s\n", yytext); }
"|" { printf("Found OPERATOR_BIT_OR: %s\n", yytext); }
"!" { printf("Found OPERATOR_BIT_NOT: %s\n", yytext); }
"^" { printf("Found OPERATOR_BIT_XOR: %s\n", yytext); }
"<<" { printf("Found OPERATOR_BIT_LEFT_SHIFT: %s\n", yytext); }
">>" { printf("Found OPERATOR_BIT_RIGHT_SHIFT: %s\n", yytext); }

"&&" { printf("Found OPERATOR_AND: %s\n", yytext); }
"||" { printf("Found OPERATOR_OR: %s\n", yytext); }

"+=" { printf("Found OPERATOR_PLUS_ASSIGNMENT: %s\n", yytext); }
"-=" { printf("Found OPERATOR_MINUS_ASSIGNMENT: %s\n", yytext); }
"*=" { printf("Found OPERATOR_MUL_ASSIGNMENT: %s\n", yytext); }
"/=" { printf("Found OPERATOR_DIV_ASSIGNMENT: %s\n", yytext); }
"%=" { printf("Found OPERATOR_MOD_ASSIGNMENT: %s\n", yytext); }
"&=" { printf("Found OPERATOR_BIT_AND_ASSIGNMENT: %s\n", yytext); }
"|=" { printf("Found OPERATOR_BIT_OR_ASSIGNMENT: %s\n", yytext); }
"^=" { printf("Found OPERATOR_BIT_XOR_ASSIGNMENT: %s\n", yytext); }
"<<=" { printf("Found OPERATOR_BIT_LEFT_SHIFT_ASSIGNMENT: %s\n", yytext); }
">>=" { printf("Found OPERATOR_BIT_RIGHT_SHIFT_ASSIGNMENT: %s\n", yytext); }

"." { printf("Found OPERATOR_POINT: %s\n", yytext); }
".." { printf("Found OPERATOR_RANGE: %s\n", yytext); }
"..=" { printf("Found OPERATOR_RANGE_ASSIGMENT: %s\n", yytext); }
"->" { printf("Found OPERATOR_ARROW: %s\n", yytext); }

"(" { printf("Found LEFT_ROUND_BRACKET: %s\n", yytext); }
")" { printf("Found RIGHT_ROUND_BRACKET: %s\n", yytext); }
"[" { printf("Found LEFT_SQUARE_BRACKET: %s\n", yytext); }
"]" { printf("Found RIGHT_SQUARE_BRACKET: %s\n", yytext); }
"{" { printf("Found LEFT_FIGURE_BRACKET: %s\n", yytext); }
"}" { printf("Found RIGHT_FIGURE_BRACKET: %s\n", yytext); }

"," { printf("Found COMMA: %s\n", yytext); }
";" { printf("Found SEMICOLON: %s\n", yytext); }
":" { printf("Found COLON: %s\n", yytext); }
"::" { printf("Found TWO_COLON: %s\n", yytext); }


"/*" { strcpy(str,""); BEGIN(ML_COMMENT); }
 <ML_COMMENT>[^*\n]* { strcat(str,yytext); }
 <ML_COMMENT>\n { lineNumber++; }
 <ML_COMMENT>"*"+[^/]* { strcat(str,yytext); }
 <ML_COMMENT>"*"+"/" { printf("Found ML_COMMENT: %s\n", str);  BEGIN(INITIAL); }
 <ML_COMMENT><<EOF>> { printf("ML_COMMENT Error in line %d: comments are not closed\n", lineNumber); BEGIN(INITIAL);}

 \/\/[^\n]* { printf("Found COMMENT: %s\n", yytext); }

\" { strcpy(str,""); BEGIN(STRING); }
<STRING>[^\\\"\n]+ { strcat(str,yytext); }
<STRING>\n  { lineNumber++; }
<STRING>\\n  { strcat(str,"\n"); }
<STRING>\\r  { strcat(str,"\r"); }
<STRING>\\t  { strcat(str,"\t"); }
<STRING>\\0  { strcat(str,"\0"); }
<STRING>\\\\ { strcat(str,"\\"); }
<STRING>\\\" { strcat(str,"\""); }
<STRING>\\x[0-7][a-zA-Z0-9] {
    char string[2];
    convertCharacterCodeToString(yytext, 2, string);
    strcat(str, string);
}
<STRING>\" { printf("Found STRING: %s\n", str); BEGIN(INITIAL);}
<STRING><<EOF>> { printf("STRING Error in line %d: there is no closing quotation mark\n", lineNumber); BEGIN(INITIAL);}
<STRING>\\ { printf("STRING Error in line %d: slash", lineNumber); }


\' { strcpy(str,""); BEGIN(CHAR); }
<CHAR>[^\\\']+ { strcat(str,yytext); }
<CHAR>\\n { strcat(str,"\n"); }
<CHAR>\\r { strcat(str,"\r"); }
<CHAR>\\t { strcat(str,"\t"); }
<CHAR>\\0 { strcat(str,"\0"); }
<CHAR>\\\\ { strcat(str,"\\"); }
<CHAR>\\\' { strcat(str,"\'"); }
<CHAR>\\x[0-7][a-zA-Z0-9] {
    char string[2];
    convertCharacterCodeToString(yytext, 2, string);
    strcat(str, string);
}
<CHAR>\' {
    if(strlen(str) == 1) {
        printf("Found CHAR:  %c\n", str[0]);
    }
    else if(strlen(str) == 0)
    {
        printf("CHAR Error in line %d: empty char literal\n", lineNumber);
    }
    else {
        printf("CHAR Error in line %d: more than one char in quote", lineNumber);
    }
    BEGIN(INITIAL);
}
<CHAR><<EOF>> { printf("CHAR Error in line %d: there is no closing quotation mark", lineNumber); BEGIN(INITIAL);}
<CHAR>\\ { printf("CHAR Error in line %d: slash", lineNumber); }


[0-9][_0-9]*(i32)? {

    removeType("i32");
    removeUnderline();
    printf("Found DECIMAL_NUMBER: %d\n", atoi(str));
}

0b([_0-1])+(i32)? {

    removeType("i32");
    removeUnderline();
    if(strlen(str) > 2)
    {
         printf("Found BIN_NUMBER: %d\n", strtol(str + 2, NULL, 2));
    }
    else
    {
        printf("NUMBER Error in line %d: incorrect format\n", lineNumber);
    }
}

0o([_0-7])+(i32)? {

    removeType("i32");
    removeUnderline();
    if(strlen(str) > 2)
    {
         printf("Found OCTAL_NUMBER: %d\n", strtol(str + 2, NULL, 8));
    }
    else
    {
        printf("NUMBER Error in line %d: incorrect format\n", lineNumber);
    }
}

0x([_0-9a-fA-F])+(i32)? {

    removeType("i32");
    removeUnderline();
    if(strlen(str) > 2)
    {
         printf("Found HEXADECIMAL_NUMBER: %d\n", strtol(str + 2, NULL, 16));
    }
    else
    {
        printf("NUMBER Error in line %d: incorrect format\n", lineNumber);
    }
}

[0-9][_0-9]*\.([0-9][_0-9]*([eE][+-]?[0-9][_0-9]*)?)?(f64)? {
    removeType("f64");
    removeUnderline();
    printf("Found DOUBLE: %lf\n", atof(str), str);
}

[0-9][_0-9]*([eE][+-]?[0-9][_0-9]*)?(f64)? {
    removeType("f64");
    removeUnderline();
    printf("Found DOUBLE: %lf\n", atof(str));
}

[a-zA-Z_][a-zA-Z0-9_]* { printf("Found IDENTIFIER: %s\n", yytext);}
[a-zA-Z_][a-zA-Z0-9_]*! { printf("Found MACROS: %s\n", yytext);}

%%

void convertCharacterCodeToString(char characterCode[], int startPosition, char *string)
{
    string[0] = strtol(characterCode + startPosition,NULL, 16);
    string[1] = '\0';
}

void removeUnderline()
{
  int pos = 0;
  for(int i = 0; i < strlen(yytext); i++)
  {
        if(yytext[i] != '_')
        {
            str[pos++] = yytext[i];
        }
  }

  str[pos] = '\0';
  strcpy(yytext, str);
}

void removeType(char *typeName)
{
    strcpy(str, yytext);
    char* p = strstr(str, typeName);
    if(p != NULL)
    {
        int pos = strlen(str)  - strlen(typeName);
        str[pos] = 0;
    }
}

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Filename is not found");
        return 1;
    }

    const char *filename= argv[1];
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File opening error");
        return 1;
    }

    yyin = file;
    yylex();
    fclose(file);

    return 0;
}