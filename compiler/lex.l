%option noyywrap
%option never-interactive

DIGIT [0-9]

%x CHAR
%x STRING
%x ML_COMMENT
%x SHIELD_STRING

%{
	#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <iostream>
    #include <string>
    #include <ctype.h>
    using namespace std;

    void removeUnderline(char str[]);
    void removeType(char str[], char *typeName);
    void convertCharacterCodeToString(char characterCode[], int startPosition, char *string);
    int translateNumberByBase(char *input_string);
    void removeSpacesAndUnderlines(char* input);
    int findRightNumberPos(const char *input_string);
    int findSecondDot(const char *input_string);
%}

%%

%{
    char str[1024];
    string stdstr = "";
    int lineNumber = 1;
    int octothorpeCount = 0;
%}

\n { lineNumber++; }
[[:space:]] { }

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
&mut { printf("Found KW_MUT_REF: %s\n", yytext); }
&self { printf("Found KW_SELF_REF: %s\n", yytext); }
&mut[[:space:]]+self { printf("Found KW_MUT_SELF_REF: %s\n", yytext); }

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
 <ML_COMMENT><<EOF>> { printf("ML_COMMENT Error in line %d: comment are not closed\n", lineNumber); BEGIN(INITIAL);}

 \/\/[^\n]* { printf("Found COMMENT: %s\n", yytext); }

\" { stdstr = ""; BEGIN(STRING); }
<STRING>[^\\\"\n]+ { stdstr += yytext; }
<STRING>\n  { lineNumber++; }
<STRING>\\n  { stdstr += "\n"; }
<STRING>\\r  { stdstr += "\r"; }
<STRING>\\t  { stdstr += "\t"; }
<STRING>\\0  { stdstr.push_back('\0'); }
<STRING>\\\\ { stdstr += "\\"; }
<STRING>\\\" { stdstr += "\""; }
<STRING>\\u\{(([0-9A-Fa-f]){1}_*){4}\} {
    int x = strtol(yytext + 3,NULL, 16); 
    if(x <= 127)
    {
        char tmp[2];
        tmp[0] = x;
        tmp[1] = 0;
        stdstr += tmp;
    }
    else
    {
     printf("CHAR Error in line %d: Unicode is not support\n", lineNumber);
    }
}
<STRING>\\x[0-7][a-zA-Z0-9] {
    char string[2];
    convertCharacterCodeToString(yytext, 2, string);
    stdstr += string;
}
<STRING>\" { cout << "Found STRING: " << stdstr << endl; BEGIN(INITIAL);}
<STRING><<EOF>> { printf("STRING Error in line %d: there is no closing quotation mark\n", lineNumber); BEGIN(INITIAL);}
<STRING>\\ { printf("STRING Error in line %d: slash\n", lineNumber); }

r(#*)\" {stdstr = ""; octothorpeCount = strlen(yytext) - 2; BEGIN(SHIELD_STRING);}
<SHIELD_STRING>[^\"\n]+ { stdstr += yytext; }
<SHIELD_STRING>\n { stdstr += "\n"; lineNumber++; }
<SHIELD_STRING>\"#* {
    int tmp  = strlen(yytext) - 1;
    if(tmp == octothorpeCount)
    {
        cout << "Found STRING: " << stdstr << endl; BEGIN(INITIAL);
    }
    else
    {
         stdstr += yytext;
    }

}
<SHIELD_STRING><<EOF>> { printf("SHIELD_STRING Error in line %d: there is no closing quotation mark\n", lineNumber); BEGIN(INITIAL);}


\' { stdstr = ""; BEGIN(CHAR); }
<CHAR>[^\\\']+ { stdstr += yytext; }
<CHAR>\\n { stdstr += "\n"; }
<CHAR>\\r { stdstr += "\r"; }
<CHAR>\\t { stdstr += "\t"; }
<CHAR>\\0 { stdstr.push_back('\0'); }
<CHAR>\\\\ { stdstr += "\\"; }
<CHAR>\\\' { stdstr += "\'"; }
<CHAR>\\\" { stdstr += "\""; }
<CHAR>\\u\{(([0-9A-Fa-f]){1}_*){4}\} {
    int x = strtol(yytext + 3,NULL, 16);
    if(x <= 127)
    {
        char tmp[2];
        tmp[0] = x;
        tmp[1] = 0;
        stdstr += tmp;
    }
    else
    {
     printf("CHAR Error in line %d: Unicode is not support\n", lineNumber);
    }
}
<CHAR>\\x[0-7][a-zA-Z0-9] {
    char string[2];
    convertCharacterCodeToString(yytext, 2, string);
    stdstr += string;
}
<CHAR>\' {
    if(stdstr.size() == 1) {
        cout << "Found CHAR:  " << stdstr << endl;
    }
    else if(stdstr.size() == 0)
    {
        printf("CHAR Error in line %d: empty char literal\n", lineNumber);
    }
    else
    {
        printf("CHAR Error in line %d: more than one char in quote\n", lineNumber);
    }
    BEGIN(INITIAL);
}
<CHAR><<EOF>> { printf("CHAR Error in line %d: there is no closing quotation mark\n", lineNumber); BEGIN(INITIAL);}
<CHAR>\\ { printf("CHAR Error in line %d: slash\n", lineNumber); }

(([0-9][_0-9]*)|(0b([_0-1])+)|(0o([_0-7])+)|(0x([_0-9a-fA-F])+))[[:space:]]*\.\.[[:space:]]*(([0-9][_0-9]*)|(0b([_0-1])+)|(0o([_0-7])+)|(0x([_0-9a-fA-F])+)) {

    strcpy(str, yytext);
    int second_dot_index = findSecondDot(str);
    int first_dot_index = second_dot_index - 1;
    int right_number_index = findRightNumberPos(&str[second_dot_index]) + second_dot_index;

    char left_number[50];
    char right_number[50];

    strncpy(left_number, str + 0, first_dot_index);
    left_number[first_dot_index] = '\0';

    int length = strlen(str) - right_number_index;
    strncpy(right_number, str + right_number_index, length);
    right_number[length] = '\0';

    translateNumberByBase(left_number);
    translateNumberByBase(right_number);
}

[0-9][_0-9]*(i32)? {

    removeType(str, "i32");
    removeUnderline(str);
    printf("Found DECIMAL_NUMBER: %d\n", atoi(str));
}

0b([_0-1])+(i32)? {

    removeType(str, "i32");
    removeUnderline(str);
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

    removeType(str, "i32");
    removeUnderline(str);
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

    removeType(str, "i32");
    removeUnderline(str);
    if(strlen(str) > 2)
    {
         printf("Found HEXADECIMAL_NUMBER: %d\n", strtol(str + 2, NULL, 16));
    }
    else
    {
        printf("NUMBER Error in line %d: incorrect format\n", lineNumber);
    }
}

\.[0-9][_0-9]*([eE][+-]?[0-9][_0-9]*)?(f64)? {
    printf("INCORRECT DOUBLE Error in line %d: float literals must have an integer part", lineNumber);
}

[0-9][_0-9]*\.([0-9][_0-9]*([eE][+-]?[0-9][_0-9]*)?)?(f64)? {
    removeType(str, "f64");
    removeUnderline(str);
    printf("Found DOUBLE: %lf\n", atof(str), str);
}

[0-9][_0-9]*([eE][+-]?[0-9][_0-9]*)?(f64)? {
    removeType(str, "f64");
    removeUnderline(str);
    printf("Found DOUBLE: %lf\n", atof(str));
}

[a-zA-Z_][a-zA-Z0-9_]* { printf("Found IDENTIFIER: %s\n", yytext);}
[a-zA-Z_][a-zA-Z0-9_]*! { printf("Found MACROS: %s\n", yytext);}
[0-9]+[a-zA-Z_][a-zA-Z0-9_]* { printf("Error in line %d: incorrect IDENTIFIER\n", lineNumber); }
. { printf("Error in line %d: incorrect character in code\n", lineNumber); }
%%

void convertCharacterCodeToString(char characterCode[], int startPosition, char *string)
{
    string[0] = strtol(characterCode + startPosition,NULL, 16);
    string[1] = '\0';
}

void removeUnderline(char str[])
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

void removeType(char str[], char *typeName)
{
    strcpy(str, yytext);
    char* p = strstr(str, typeName);
    if(p != NULL)
    {
        int pos = strlen(str)  - strlen(typeName);
        str[pos] = 0;
    }
}

int findSecondDot(const char *input_string) {
    int first_dot = -1;  // Переменная для индекса первой точки

    for (int i = 0; input_string[i] != '\0'; i++) {
        if (input_string[i] == '.') {
            if (first_dot == -1) {
                first_dot = i;  // Нашли первую точку
            } else {
                printf("Found TWO_DOTS: %.*s\n", i - first_dot + 1, input_string + first_dot);
                return i;  // Нашли вторую точку, возвращаем её индекс
            }
        }
    }

    return -1;  // Второй символ точки не найден
}

int findRightNumberPos(const char *input_string) {

    for (int i = 0; input_string[i] != '\0'; i++) {
        if (input_string[i] >= '0' && input_string[i] <= '9') {
            return i;  // Нашли индекс начала второго числа
        }
    }

    return -1;  // второе число не нашлось
}

void removeSpacesAndUnderlines(char* input) {
    int len = strlen(input);
    int i, j = 0;

    for (i = 0; i < len; i++) {
        if (input[i] != ' ' && input[i] != '_') {
            input[j] = input[i];
            j++;
        }
    }
    input[j] = '\0';
}

int translateNumberByBase(char *input_string) {
    removeSpacesAndUnderlines(input_string);
    int len = strlen(input_string);

    if (len == 1 && (input_string[0] >= '0' && input_string[0] <= '9')) {
        printf("Found RANGE_DECIMAL_NUMBER: %d\n", atoi(input_string));
    } else if (len >= 2 && (input_string[0] >= '0' && input_string[0] <= '9') && (input_string[1] >= '0' && input_string[1] <= '9')) {
        printf("Found RANGE_DECIMAL_NUMBER: %d\n", atoi(input_string));
    }


    if (input_string[0] == '0' && (len > 2)){
        if (input_string[1] == 'x'){
            printf("Found RANGE_HEXADECIMAL_NUMBER: %ld\n", strtol(input_string + 2, NULL, 16));
        } else if (input_string[1] == 'b') {
            printf("Found RANGE_BIN_NUMBER: %ld\n", strtol(input_string + 2, NULL, 2));
        } else if (input_string[1] == 'o'){
            printf("Found RANGE_OCTAL_NUMBER: %ld\n", strtol(input_string + 2, NULL, 8));
        } else {
            printf("Found RANGE_DECIMAL_NUMBER: %d\n", atoi(input_string));
        }
    }

    return -1; // не удалось произвести операцию перевода с числом
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


