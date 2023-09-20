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

as  { printf("Found KW_AS: %s\n", yytext); }
break   { printf("Found KW_BREAK: %s\n", yytext); }
const   { printf("Found KW_CONST: %s\n", yytext); }
continue    { printf("Found KW_CONTINUE: %s\n", yytext); }
crate   { printf("Found KW_CRATE: %s\n", yytext); }
else   { printf("Found KW_ELSE: %s\n", yytext); }
enum   { printf("Found KW_ENUM: %s\n", yytext); }
extern   { printf("Found KW_EXTERN: %s\n", yytext); }
false   { printf("Found KW_FALSE: %s\n", yytext); }
fn   { printf("Found KW_FN: %s\n", yytext); }
for   { printf("Found KW_FOR: %s\n", yytext); }
if   { printf("Found KW_IF: %s\n", yytext); }
impl   { printf("Found KW_IMPL: %s\n", yytext); }
in   { printf("Found KW_IN: %s\n", yytext); }
let   { printf("Found KW_LET: %s\n", yytext); }
loop   { printf("Found KW_LOOP: %s\n", yytext); }
match   { printf("Found KW_MATCH: %s\n", yytext); }
mod   { printf("Found KW_MOD: %s\n", yytext); }
move    { printf("Found KW_MOVE: %s\n", yytext); }
mut    { printf("Found KW_MUT: %s\n", yytext); }
pub    { printf("Found KW_PUB: %s\n", yytext); }
ref    { printf("Found KW_REF: %s\n", yytext); }
return    { printf("Found KW_RETURN: %s\n", yytext); }
self    { printf("Found KW_SELFVALUE: %s\n", yytext); }
Self    { printf("Found KW_SELFTYPE: %s\n", yytext); }
static    { printf("Found KW_STATIC: %s\n", yytext); }
struct    { printf("Found KW_STRUCT: %s\n", yytext); }
super    { printf("Found KW_SUPER: %s\n", yytext); }
trait    { printf("Found KW_TRAIT: %s\n", yytext); }
true    { printf("Found KW_TRUE: %s\n", yytext); }
type    { printf("Found KW_TYPE: %s\n", yytext); }
unsafe    { printf("Found KW_UNSAFE: %s\n", yytext); }
use    { printf("Found KW_USE: %s\n", yytext); }
where    { printf("Found KW_WHERE: %s\n", yytext); }
while    { printf("Found KW_WHILE: %s\n", yytext); }

/* ==================== TYPE ==================== */

bool  { printf("Found TYPE_BOOL: %s\n", yytext); }
i32  { printf("Found TYPE_I32: %s\n", yytext); }
i64  { printf("Found TYPE_I64: %s\n", yytext); }
f32  { printf("Found TYPE_F32: %s\n", yytext); }
f64  { printf("Found TYPE_F64: %s\n", yytext); }
String  { printf("Found TYPE_STRING: %s\n", yytext); }

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
