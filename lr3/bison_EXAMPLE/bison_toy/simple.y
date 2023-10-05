%{
#include "tree_structs.h"
#include <stdio.h>
#include <malloc.h>
void yyerror(char const *s);
extern int yylex(void);
struct Program *CreateProgram(struct Statements_List *lst);
struct Statements_List *AppendStatementToList(struct Statements_List *lst,struct Statement *stm);
struct Statements_List *CreateStList(struct Statement *stm);
struct Statement *CreateStatement(struct Expression *exp);
struct Expression *CreateBinExp(int op,struct Expression *left,struct Expression *right);
struct Expression *CreateIntExp(int value);
struct Statements_List *lst_start;
struct Program *prg;
%}
%union {
	int int_const;
	struct Expression *exp;
	struct Statement *stm;
	struct Program *prg;
	struct Statements_List *lst;
}
%type <prg>seq
%type <lst>seq1
%type <stm>stmt
%type <exp>expr
%token PRINT
%token <int_const>INT
%left '-' '+'
%left '*' '/'
%nonassoc ')'
%%
seq: seq1 {$$=prg=CreateProgram(lst_start);}
    ;
seq1: seq1 stmt {$$=AppendStatementToList($1,$2);}
    | stmt {$$=lst_start=CreateStList($1);}
    ;
stmt: PRINT expr ';' {$$=CreateStatement($2);}
    ;
expr: expr '+' expr {$$=CreateBinExp(1,$1,$3);}
    | expr '-' expr {$$=CreateBinExp(2,$1,$3);}
    | expr '*' expr {$$=CreateBinExp(3,$1,$3);}
    | expr '/' expr {$$=CreateBinExp(4,$1,$3);}
    | '(' expr ')' {$$=$2;}
    | INT {$$=CreateIntExp($1);}
    ;
%%

void yyerror(char const *s)
{
 printf("%s",s);
}

struct Program *CreateProgram(struct Statements_List *lst)
{
	struct Program *crt=(struct Program *)malloc(sizeof(struct Program));
	crt->stmts=lst;
	return crt;
}
struct Statements_List *AppendStatementToList(struct Statements_List *lst,struct Statement *stm)
{
	struct Statements_List *crt=(struct Statements_List *)malloc(sizeof(struct Statements_List));
	crt->next=0;
	lst->next=crt;
	crt->stm=stm;
	return crt;
}
struct Statements_List *CreateStList(struct Statement *stm)
{
	struct Statements_List *crt=(struct Statements_List *)malloc(sizeof(struct Statements_List));
	crt->next=0;
	crt->stm=stm;
}
struct Statement *CreateStatement(struct Expression *exp)
{
	struct Statement *crt=(struct Statement *)malloc(sizeof(struct Statement));
	crt->to_print=exp;
	return crt;
}
struct Expression *CreateBinExp(int op,struct Expression *left,struct Expression *right)
{
	struct Expression *crt=(struct Expression *)malloc(sizeof(struct Expression));
	crt->type=op;
	crt->left=left;
	crt->right=right;
	return crt;
}
struct Expression *CreateIntExp(int value)
{
	struct Expression *crt=(struct Expression *)malloc(sizeof(struct Expression));
	crt->type=0;
	crt->value=value;
	return crt;
}