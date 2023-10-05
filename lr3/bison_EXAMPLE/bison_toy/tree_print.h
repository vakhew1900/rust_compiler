#include <stdio.h>

int tree_print(void);
void lst_print(struct Statements_List*stmts);
void stmt_print(struct Statement *stmt);
void expr_print(struct Expression *expr);
void print_indent();
int level=0;
extern struct Program *prg;

int tree_print(void)
{
	printf("Program:");
	level++;
	lst_print(prg->stmts);
	level--;
	return 0;
}

void lst_print(struct Statements_List*stmts)
{
	while(stmts!=0)
	{
		level++;
		stmt_print(stmts->stm);
		level--;
		stmts=stmts->next;
	} 
}
void stmt_print(struct Statement *stmt)
{
	print_indent();
	printf("print");
	level++;
	expr_print(stmt->to_print);
	level--;
}
void expr_print(struct Expression *expr)
{
	print_indent();
	switch(expr->type)
	{
	case 0:
		printf("%d",expr->value);
		break;
	case 1:
		printf("+");
		level++;
		expr_print(expr->left);
		level--;
		level++;
		expr_print(expr->right);
		level--;
		break;
	case 2:
		printf("-");
		level++;
		expr_print(expr->left);
		level--;
		level++;
		expr_print(expr->right);
		level--;
		break;
	case 3:
		printf("*");
		level++;
		expr_print(expr->left);
		level--;
		level++;
		expr_print(expr->right);
		level--;
		break;
	case 4:
		printf("/");
		level++;
		expr_print(expr->left);
		level--;
		level++;
		expr_print(expr->right);
		level--;
		break;
	}
}

void print_indent()
{
	int i;
	printf("\n");
	for(i=0;i<level;i++)
	{
		printf("  ");
	}
}




