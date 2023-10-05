typedef union {
	int int_const;
	struct Expression *exp;
	struct Statement *stm;
	struct Program *prg;
	struct Statements_List *lst;
} YYSTYPE;
#define	PRINT	258
#define	INT	259


extern YYSTYPE yylval;
