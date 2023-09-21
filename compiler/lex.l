%option noyywrap
%option never-interactive

DIGIT [0-9]

%x STRING
%x ML_COMMENT

%{
	#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    char str[1024];
%}

%%

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
while   { printf("Found KW_WHILE: %s\n", yytext); }

bool  { printf("Found TYPE_BOOL: %s\n", yytext); }
i32  { printf("Found TYPE_I32: %s\n", yytext); }
i64  { printf("Found TYPE_I64: %s\n", yytext); }
f32  { printf("Found TYPE_F32: %s\n", yytext); }
f64  { printf("Found TYPE_F64: %s\n", yytext); }
String  { printf("Found TYPE_STRING: %s\n", yytext); }

"/*" { strcpy(str,""); BEGIN(ML_COMMENT); }
 <ML_COMMENT>[^*]* { strcat(str,yytext); }
 <ML_COMMENT>"*"+[^/]* { strcat(str,yytext); }
 <ML_COMMENT>"*"+"/" { printf("Found ML_COMMENT: %s\n", str);  BEGIN(INITIAL); }
 <ML_COMMENT><<EOF>> { printf("ML_COMMENT Error: comments are not closed"); BEGIN(INITIAL);}

 \/\/[^\n]* { printf("Found COMMENT: %s\n", yytext); }

%%

