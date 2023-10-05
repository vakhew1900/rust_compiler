#ifndef SIMPLE_TREE_STRUCTS
#define SIMPLE_TREE_STRUCTS
struct Expression
{
	int type;//0 - int, 1 +, 2-, 3*, 4/
	int value;
	struct Expression *left;
	struct Expression *right;
};

struct Statement
{
	struct Expression *to_print;
};

struct Program
{
	struct Statements_List *stmts;
};

struct Statements_List
{
	struct Statement *stm;
	struct Statements_List *next;
};
#endif