#include "classesnodes.h"

typedef union {
    int int_literal;
	string* string_literal;
	string* identifier;
	bool bool_literal;
	float float_literal;
	char char_literal;
    enum Visibility vis;

    ProgramNode* prg;
    ExprNode* expr;
    ExprListNode * expr_list;
    StmtNode* stmt;
    StmtListNode* stmt_list;
    LetStmtNode* let_stmt;
    ModuleStmtNode* mod_stmt;
    ItemNode* item;
    ItemListNode* item_list;
    StructFieldNode* struct_item;
    StructFieldListNode* struct_items;
    StructStructNode* struct_;
    EnumStmtNode* enum_stmt;
    EnumItemNode* enum_item;
    EnumItemListNode* enum_items;
    FuncStmtNode* function_stmt;
    FuncParamNode* function_param;
    FuncParamListNode* function_params;
    ConstStmtNode* const_stmt;
    TraitNode* trait;
    ImplStmtNode* impl_stmt;
    TypeNode* type;
} YYSTYPE;
#define	INT_LITERAL	258
#define	STRING_LITERAL	259
#define	RAW_STRING_LITERAL	260
#define	ID	261
#define	TRUE	262
#define	FALSE	263
#define	FLOAT_LITERAL	264
#define	CHAR_LITERAL	265
#define	BOOL	266
#define	CHAR	267
#define	FLOAT	268
#define	INT	269
#define	STRING	270
#define	FOR	271
#define	LOOP	272
#define	WHILE	273
#define	IN	274
#define	CONTINUE	275
#define	IF	276
#define	ELSE	277
#define	LET	278
#define	MUT	279
#define	CONST	280
#define	FN	281
#define	ENUM	282
#define	STRUCT	283
#define	TRAIT	284
#define	IMPL	285
#define	SELF	286
#define	BIG_SELF	287
#define	PUB	288
#define	SELF_REF	289
#define	MUT_SELF_REF	290
#define	MUT_REF	291
#define	MOD	292
#define	SUPER	293
#define	CRATE	294
#define	RIGHT_ARROW	295
#define	BREAK	296
#define	RETURN	297
#define	RANGE	298
#define	OR	299
#define	AND	300
#define	EQUAL	301
#define	NOT_EQUAL	302
#define	LESS_EQUAL	303
#define	GREATER_EQUAL	304
#define	AS	305
#define	UMINUS	306
#define	USTAR	307
#define	DOUBLEDOTS	308


extern YYSTYPE yylval;

void setFile(const char* filename);
