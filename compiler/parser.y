%{
    #include <iostream>
    #include "classesnodes.h"
    void yyerror(char const* s);
    extern int yylex(void);
    using namespace std;
    ProgramNode* global_program;
%}

%union {
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
}

%type <prg>Program
%type <expr>ExprWithoutBlock
%type <expr>ExprWithBlock
%type <expr>BlockExpr
%type <expr>IfExpr
%type <expr>SimpleIfElseExpr
%type <expr>SimpleIfExpr
%type <expr>InfiniteLoopExpr
%type <expr>LoopExpr
%type <expr>PredicateLoopExpr
%type <expr>IteratorLoopExpr
%type <expr>PathCallExpr
%type <expr>StructExprField
%type <expr_list>ExprList
%type <expr_list>ExprListEmpty
%type <expr_list>StructExprFieldList
%type <stmt>Stmt
%type <stmt>ExprStmt
%type <stmt_list>StmtList
%type <let_stmt>LetStmt
%type <mod_stmt>ModuleStmt
%type <item>Item
%type <item>SimpleItem
%type <item_list>ItemList
%type <item_list>ItemListEmpty
%type <struct_>StructStruct
%type <struct_>StructStmt
%type <struct_>TupleStruct
%type <struct_item>StructField
%type <struct_items>StructFieldList
%type <struct_items>StructFieldListEmpty
%type <struct_items>TupleFieldList
%type <struct_items>TupleFieldListEmpty
%type <enum_stmt>EnumStmt
%type <enum_item>EnumItem
%type <enum_items>EnumItemList
%type <enum_items>EnumItemListEmpty
%type <function_stmt>FuncStmt
%type <function_stmt>ImplFuncStmt
%type <function_stmt>DecFuncStmt
%type <function_param>FuncParam
%type <function_params>FuncParamList
%type <function_params>FuncParamListEmpty
%type <const_stmt>ConstStmt
%type <item>AssociatedItem
%type <item_list>AssociatedItemList
%type <item_list>AssociatedItemListEmpty
%type <impl_stmt>ImplStmt
%type <trait>TraitStmt
%type <type>Type
%type <vis>Visibility

%type <int_literal>INT_LITERAL
%type <string_literal>STRING_LITERAL
%type <string_literal>RAW_STRING_LITERAL
%type <identifier>ID
%type <bool_literal>TRUE
%type <bool_literal>FALSE
%type <float_literal>FLOAT_LITERAL
%type <char_literal>CHAR_LITERAL


%token BOOL CHAR FLOAT INT STRING
%token TRUE FALSE CHAR_LITERAL INT_LITERAL FLOAT_LITERAL STRING_LITERAL RAW_STRING_LITERAL
%token ID
%token FOR LOOP WHILE IN CONTINUE
%token IF ELSE
%token LET MUT CONST
%token FN ENUM STRUCT TRAIT
%token IMPL SELF BIG_SELF PUB SELF_REF MUT_SELF_REF MUT_REF MOD SUPER
%token ';'  RIGHT_ARROW

/* BREAK и RETURN  в документации почему-то присуствует в приоритетах операций. Стоит наверное с этим разобраться */

%nonassoc BREAK RETURN
%nonassoc '{' '}'
%right ':'
%right '='
%nonassoc RANGE   /* .. */
%left OR  /* || */
%left AND /* && */
%left '<' '>'  EQUAL NOT_EQUAL LESS_EQUAL GREATER_EQUAL  // == != <= >=
%left '+' '-'
%left '*' '/' '%'
%left AS
%left '!' '&' MUT_REF UMINUS USTAR /*  - * */
%nonassoc '?'
%left '.' '['  DOUBLEDOTS
%nonassoc  '(' ')'

%start Program

%%


/* ---------------------- PROGRAM --------------------------- */

Program: ItemListEmpty { $$ = global_program = new ProgramNode($1); }
/* Необходимо уточнить, надо ли как-то обозначить, что Stmt все должны быть Item, иначе программа не заработает */

/* ----------------------------- STATEMENT -----------------------------  */


StmtList: Stmt { $$ = new StmtListNode($1); }
        | StmtList Stmt { $$ = StmtListNode::Append($1, $2); }
        ;

Stmt: ';' { $$ = new StmtNode(StmtNode::semicolon, 0, 0, 0); }
    | LetStmt { $$ = new StmtNode(StmtNode::let, NULL, NULL, $1); }
    | ExprStmt { $$ = $1;}
    ;

ItemListEmpty: /*empty*/ { $$ = 0; }
             | ItemList { $$ = new ItemListNode($1); }
             ;

ItemList: Item { $$ = new ItemListNode($1); }
         | ItemList Item { $$ = ItemListNode::Append($1, $2); }
         ;

Item: SimpleItem { $$ = $1;}
     | Visibility SimpleItem { $$ = ItemNode::AddVisibility($1, $2);}
     ;

SimpleItem: FuncStmt  { $$ = ItemNode::DeclarationFunction(self, $1); }
          | StructStmt { $$ = ItemNode::DeclarationStruct(self, $1); }
          | EnumStmt { $$ = ItemNode::DeclarationEnum(self, $1); }
          | ImplStmt { $$ = ItemNode::DeclarationImpl(self, $1); }
          | TraitStmt { $$ = ItemNode::DeclarationTrait(self, $1); }
          | ConstStmt { $$ = ItemNode::DeclarationConst(self, $1); }
          | ModuleStmt { $$ = ItemNode::DeclarationModule(self, $1); }
          ;

/* ---------- Function ------------ */

FuncStmt: DecFuncStmt { $$ = $1; }
        | ImplFuncStmt { $$ = $1; }
        ;

DecFuncStmt: FN ID '(' FuncParamListEmpty ')' ';' { $$ = new FuncStmtNode($2, 0, $4, 0); }
           | FN ID '(' FuncParamListEmpty ')' RIGHT_ARROW  Type ';' { $$ = new FuncStmtNode($2, $7, $4, 0); }
           ;

ImplFuncStmt: FN ID '(' FuncParamListEmpty ')' BlockExpr { $$ = new FuncStmtNode($2, 0, $4, $6); }
            | FN ID '(' FuncParamListEmpty ')' RIGHT_ARROW  Type BlockExpr { $$ = new FuncStmtNode($2, $7, $4, $8); }
            ;

FuncParamListEmpty: /* empty */ { $$ = FuncParamListNode::FunctionParamsFinal(FuncParamListNode::static_, 0); }
               | FuncParamList { $$ = $1; }
               ;

FuncParamList: SELF { $$ = FuncParamListNode::FunctionParamsFinal(FuncParamListNode::self, 0); }
             | SELF_REF { $$ = FuncParamListNode::FunctionParamsFinal(FuncParamListNode::self_ref, 0); }
             | MUT_SELF_REF { $$ = FuncParamListNode::FunctionParamsFinal(FuncParamListNode::mut_self_ref, 0); }
             | FuncParam  { $$ = new FuncParamListNode(FuncParamListNode::static_, $1); }
             | FuncParamList ',' FuncParam { $$ = FuncParamListNode::Append($1, $3); }
             ;

FuncParam: ID ':' Type { $$ = new FuncParamNode($1, $3, FuncParamNode::noMut); }
         | MUT ID ':' Type { $$ = new FuncParamNode($2, $4, FuncParamNode::mut); }
         | ID ':' MUT_REF Type { $$ = new FuncParamNode($1, $4, FuncParamNode::mut_ref); }
         | ID ':' '&' Type { $$ = new FuncParamNode($1, $4, FuncParamNode::link); }
         ;

/* ========== Struct =========== */

StructStmt: StructStruct { $$ = $1; }
          | TupleStruct  { $$ = $1; }
          ;

StructStruct : STRUCT ID '{' StructFieldListEmpty '}' { $$ = new StructStructNode($2, $4); }
             | STRUCT ID ';' { $$ = new StructStructNode($2, 0); }
             ;

StructFieldListEmpty: /* empty */ { $$ = 0; }
                    | StructFieldList { $$ = new StructFieldListNode($1); }
                    | StructFieldList ',' { $$ = new StructFieldListNode($1); }
                    ;

StructFieldList: StructField { $$ = new StructFieldListNode($1); }
               | StructFieldList ',' StructField { $$ = StructFieldListNode::Append($1, $3); }
               ;

StructField: ID ':' Type { $$ = new StructFieldNode($1, $3, self); }
           | Visibility ID ':' Type { $$ = new StructFieldNode($2, $4, $1); }
           ;

/*--- TupleStruct ----*/

TupleStruct: STRUCT ID '(' TupleFieldListEmpty ')' { $$ = new StructStructNode($2, $4); }
           ;

TupleFieldListEmpty: /* empty */ { $$ = 0; }
                    | TupleFieldList { $$ = new StructFieldListNode($1); }
                    | TupleFieldList ',' { $$ = new StructFieldListNode($1); }
                    ;

TupleFieldList: Type { $$ = new StructFieldListNode(new StructFieldNode(0, $1, self)); }
               | Visibility Type { $$ = new StructFieldListNode(new StructFieldNode(0, $2, $1)); }
               | TupleFieldList ',' Type { $$ = StructFieldListNode::Append($1, new StructFieldNode(0, $3, self)); }
               | TupleFieldList ',' Visibility Type { $$ = StructFieldListNode::Append($1, new StructFieldNode(0, $4, $3)); }
               ;

/* ============= ENUM ================ */

EnumStmt: ENUM ID '{' EnumItemListEmpty '}' { $$ = new EnumStmtNode($2, $4); }
        ;

EnumItemListEmpty: /* empty */ { $$ = 0; }
                 | ',' { $$ = 0; }
                 | EnumItemList { $$ = new EnumItemListNode($1); }
                 | EnumItemList ',' { $$ = new EnumItemListNode($1); }
                 ;

EnumItemList: EnumItem { $$ = new EnumItemListNode($1); }
            | EnumItemList ',' EnumItem { $$ = EnumItemListNode::Append($1, $3); }
            ;

EnumItem: ID { $$ = new EnumItemNode($1, self, 0, 0); }
        | Visibility ID { $$ = new EnumItemNode($2, $1, 0, 0); }
        | ID '=' ExprWithBlock { $$ = new EnumItemNode($1, self, NULL, $3); } /* В таком случае ID  должен быть всегда только целочисленным числом. Нельзя на парсере определить такое*/
        | ID '=' ExprWithoutBlock { $$ = new EnumItemNode($1, self, 0, $3); }
        | Visibility ID '=' ExprWithBlock { $$ = new EnumItemNode($2, $1, 0, $4); }
        | Visibility ID '=' ExprWithoutBlock { $$ = new EnumItemNode($2, $1, 0, $4); }
        | Visibility ID '{' StructFieldListEmpty '}' { $$ = new EnumItemNode($2, $1, $4, 0); }
        | ID '{' StructFieldListEmpty '}' { $$ = new EnumItemNode($1, self, $3, 0); }
        ;

/* =========== IMPL ================ */

ImplStmt: IMPL Type '{'AssociatedItemListEmpty '}' { $$ = new ImplStmtNode(ImplStmtNode::inherent, $2, 0, $4); }
        | IMPL ID FOR Type '{'AssociatedItemListEmpty '}' { $$ = new ImplStmtNode(ImplStmtNode::trait, $4, $2, $6); }
        ;

AssociatedItemListEmpty: /* empty */ { $$ = NULL; }
                       | AssociatedItemList { $$ = $1; }
                       ;

AssociatedItemList: AssociatedItem { $$ = $$ = new ItemListNode($1); }
                  | AssociatedItemList AssociatedItem { $$ = $$ = ItemListNode::Append($1, $2); }
                  ;

/* Необходима еще проверка для Impl то что FuncStmt является именно реализацией */
AssociatedItem: FuncStmt { $$ = ItemNode::DeclarationFunction(self, $1); } // ImplFuncStmt
              | ConstStmt { $$ = ItemNode::DeclarationConst(self, $1); }
              | Visibility FuncStmt { $$ = ItemNode::DeclarationFunction($1, $2); }
              | Visibility ConstStmt { $$ = ItemNode::DeclarationConst($1, $2); }
              ;


/* ============ TRAIT ================ */

TraitStmt: TRAIT ID '{' AssociatedItemListEmpty '}' { $$ = new TraitNode($2, $4); }
         ;

/* ============ CONST =============== */

ConstStmt: CONST ID ':' Type '=' ExprWithBlock ';' { $$ = ConstStmtNode::ConstStmt($2, $4, $6); }
         | CONST ID ':' Type '=' ExprWithoutBlock ';' { $$ = ConstStmtNode::ConstStmt($2, $4, $6); }
         | CONST ID ':' Type ';' { $$ = ConstStmtNode::ConstStmt($2, $4, 0); }
         ;

/* =========== Module ================= */

ModuleStmt: MOD ID '{' ItemListEmpty '}' { $$ = new ModuleStmtNode($2, $4); }
          ;

/* ========= LetStmt ============ */
LetStmt: LET ID '=' ExprWithBlock ';' { $$ = new LetStmtNode($2, 0, LetStmtNode::noMut, $4); }
       | LET ID '=' ExprWithoutBlock ';' { $$ = new LetStmtNode($2, 0, LetStmtNode::noMut, $4); }
       | LET ID ':' Type '=' ExprWithBlock ';' { $$ = new LetStmtNode($2, $4, LetStmtNode::noMut, $6); }
       | LET ID ':' Type '=' ExprWithoutBlock ';' { $$ = new LetStmtNode($2, $4, LetStmtNode::noMut, $6); }
       | LET MUT ID ';' { $$ = new LetStmtNode($3, 0, LetStmtNode::mut, 0); }
       | LET MUT ID ':' Type ';' { $$ = new LetStmtNode($3, $5, LetStmtNode::mut, 0); }
       | LET MUT ID '=' ExprWithBlock ';' { $$ = new LetStmtNode($3, 0, LetStmtNode::mut, $5); }
       | LET MUT ID '=' ExprWithoutBlock ';' { $$ = new LetStmtNode($3, 0, LetStmtNode::mut, $5); }
       | LET MUT ID ':' Type '=' ExprWithBlock ';' { $$ = new LetStmtNode($3, $5, LetStmtNode::mut, $7); }
       | LET MUT ID ':' Type '=' ExprWithoutBlock ';' { $$ = new LetStmtNode($3, $5, LetStmtNode::mut, $7); }
       ;

/* === Expression Statement === */
ExprStmt: ExprWithoutBlock ';' {$$ = new StmtNode(StmtNode::exprstmt, $1, 0, 0);}
        | ExprWithBlock {$$ = new StmtNode(StmtNode::exprstmt, $1, 0, 0);}
        ;


/*----------------------- EXPRESSION ---------------------- */

ExprListEmpty: /*empty*/ { $$ = 0; }
             | ExprList ',' { $$ = new ExprListNode($1); }
             | ExprList { $$ = new ExprListNode($1); }
             ;

ExprList: ExprWithBlock { $$ = new ExprListNode($1); }
        | ExprWithoutBlock { $$ = new ExprListNode($1); }
        | ExprList ',' ExprWithBlock { $$ = ExprListNode::Append($1, $3); }
        | ExprList ',' ExprWithoutBlock { $$ = ExprListNode::Append($1, $3); }
        ;

ExprWithoutBlock: CHAR_LITERAL { $$ = ExprNode::ExprFromCharLiteral(ExprNode::char_lit, $1); }
                | STRING_LITERAL { $$ = ExprNode::ExprFromStringLiteral(ExprNode::string_lit, $1);  }
                | RAW_STRING_LITERAL { $$ = ExprNode::ExprFromStringLiteral(ExprNode::raw_string_lit, $1); }
                | INT_LITERAL { $$ = ExprNode::ExprFromIntLiteral(ExprNode::int_lit, $1); }
                | FLOAT_LITERAL { $$ = ExprNode::ExprFromFloatLiteral(ExprNode::float_lit, $1); }
                | TRUE { $$ = ExprNode::ExprFromBoolLiteral(ExprNode::bool_lit, $1); }
                | FALSE { $$ = ExprNode::ExprFromBoolLiteral(ExprNode::bool_lit, $1); }
                | ExprWithoutBlock '+' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::plus, $1, $3); }
                | ExprWithoutBlock '+' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::plus, $1, $3); }
                | ExprWithBlock '+' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::plus, $1, $3); }
                | ExprWithBlock '+' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::plus, $1, $3); }
                | ExprWithoutBlock '-' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::minus, $1, $3); }
                | ExprWithoutBlock '-' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::minus, $1, $3); }
                | ExprWithBlock '-' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::minus, $1, $3); }
                | ExprWithBlock '-' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::minus, $1, $3); }
                | ExprWithoutBlock '/' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::div_expr, $1, $3); }
                | ExprWithoutBlock '/' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::div_expr, $1, $3); }
                | ExprWithBlock '/' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::div_expr, $1, $3); }
                | ExprWithBlock '/' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::div_expr, $1, $3); }
                | ExprWithoutBlock '*' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::mul_expr, $1, $3); }
                | ExprWithoutBlock '*' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::mul_expr, $1, $3); }
                | ExprWithBlock '*' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::mul_expr, $1, $3); }
                | ExprWithBlock '*' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::mul_expr, $1, $3); }
                | ExprWithoutBlock '%' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::mod, $1, $3); }
                | ExprWithoutBlock '%' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::mod, $1, $3); }
                | ExprWithBlock '%' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::mod, $1, $3); }
                | ExprWithBlock '%' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::mod, $1, $3); }
                | ExprWithoutBlock AND ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::and_, $1, $3); }
                | ExprWithoutBlock AND ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::and_, $1, $3); }
                | ExprWithBlock AND ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::and_, $1, $3); }
                | ExprWithBlock AND ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::and_, $1, $3); }
                | ExprWithoutBlock OR ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::or_, $1, $3); }
                | ExprWithoutBlock OR ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::or_, $1, $3); }
                | ExprWithBlock OR ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::or_, $1, $3); }
                | ExprWithBlock OR ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::or_, $1, $3); }
                | ExprWithoutBlock '=' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::asign, $1, $3); }
                | ExprWithoutBlock '=' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::asign, $1, $3); }
                | ExprWithBlock '=' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::asign, $1, $3); }
                | ExprWithBlock '=' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::asign, $1, $3); }
                | ExprWithoutBlock EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::equal, $1, $3); }
                | ExprWithoutBlock EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::equal, $1, $3); }
                | ExprWithBlock EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::equal, $1, $3); }
                | ExprWithBlock EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::equal, $1, $3); }
                | ExprWithoutBlock NOT_EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::not_equal, $1, $3); }
                | ExprWithoutBlock NOT_EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::not_equal, $1, $3); }
                | ExprWithBlock NOT_EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::not_equal, $1, $3); }
                | ExprWithBlock NOT_EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::not_equal, $1, $3); }
                | ExprWithoutBlock '>' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::greater, $1, $3); }
                | ExprWithoutBlock '>' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::greater, $1, $3); }
                | ExprWithBlock '>' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::greater, $1, $3); }
                | ExprWithBlock '>' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::greater, $1, $3); }
                | ExprWithoutBlock '<' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::less, $1, $3); }
                | ExprWithoutBlock '<' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::less, $1, $3); }
                | ExprWithBlock '<' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::less, $1, $3); }
                | ExprWithBlock '<' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::less, $1, $3); }
                | ExprWithoutBlock GREATER_EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::greater_equal, $1, $3); }
                | ExprWithoutBlock GREATER_EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::greater_equal, $1, $3); }
                | ExprWithBlock GREATER_EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::greater_equal, $1, $3); }
                | ExprWithBlock GREATER_EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::greater_equal, $1, $3); }
                | ExprWithoutBlock LESS_EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::less_equal, $1, $3); }
                | ExprWithoutBlock LESS_EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::less_equal, $1, $3); }
                | ExprWithBlock LESS_EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::less_equal, $1, $3); }
                | ExprWithBlock LESS_EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::less_equal, $1, $3); }
                | '-' ExprWithoutBlock %prec UMINUS { $$ = ExprNode::OperatorExpr(ExprNode::uminus, $2, 0); }
                | '-' ExprWithBlock %prec UMINUS { $$ = ExprNode::OperatorExpr(ExprNode::uminus, $2, 0); }
                | '!' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::negotation, $2, 0); }
                | '!' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::negotation, $2, 0); }
                | ExprWithoutBlock '?' { $$ = ExprNode::OperatorExpr(ExprNode::question, $1, 0); }
                | ExprWithBlock '?' { $$ = ExprNode::OperatorExpr(ExprNode::question, $1, 0); }
                | '*' ExprWithoutBlock %prec USTAR { $$ = ExprNode::OperatorExpr(ExprNode::ustar, $2, 0); }
                | '*' ExprWithBlock %prec USTAR { $$ = ExprNode::OperatorExpr(ExprNode::ustar, $2, 0); }
                | '&' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::link, $2, 0); }
                | '&' ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::link, $2, 0); }
                | MUT_REF ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::mut_link, $2, 0); }
                | MUT_REF ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::mut_link, $2, 0); }
                | '[' ExprListEmpty ']'  { $$ = ExprNode::ArrExprFromList(ExprNode::array_expr, $2); }
                | '[' ExprWithoutBlock ';' ExprWithoutBlock ']' { $$ = ExprNode::ArrExprAutoFill(ExprNode::array_expr_auto_fill, $2, $4); }
                | '[' ExprWithoutBlock ';' ExprWithBlock ']' { $$ = ExprNode::ArrExprAutoFill(ExprNode::array_expr_auto_fill, $2, $4); }
                | '[' ExprWithBlock ';' ExprWithoutBlock ']' { $$ = ExprNode::ArrExprAutoFill(ExprNode::array_expr_auto_fill, $2, $4); }
                | '[' ExprWithBlock ';' ExprWithBlock ']' { $$ = ExprNode::ArrExprAutoFill(ExprNode::array_expr_auto_fill, $2, $4); }
                | ExprWithoutBlock '[' ExprWithoutBlock ']' { $$ = ExprNode::OperatorExpr(ExprNode::index_expr, $1, $3); }
                | ExprWithoutBlock '[' ExprWithBlock ']' { $$ = ExprNode::OperatorExpr(ExprNode::index_expr, $1, $3); }
                | ExprWithBlock '[' ExprWithoutBlock ']' { $$ = ExprNode::OperatorExpr(ExprNode::index_expr, $1, $3); }
                | ExprWithBlock '[' ExprWithBlock ']' { $$ = ExprNode::OperatorExpr(ExprNode::index_expr, $1, $3); }
                | ExprWithoutBlock '.' INT_LITERAL { $$ = ExprNode::TupleExpr(ExprNode::tuple_expr, $1, $3); }
                | ExprWithBlock '.' INT_LITERAL { $$ = ExprNode::TupleExpr(ExprNode::tuple_expr, $1, $3); }
                | CONTINUE { $$ = ExprNode::OperatorExpr(ExprNode::continue_expr, 0, 0); }
                | BREAK { $$ = ExprNode::OperatorExpr(ExprNode::break_expr, 0, 0); }
                | BREAK ExprWithoutBlock{ $$ = ExprNode::OperatorExpr(ExprNode::break_with_val_expr, $2, 0); }
                | BREAK ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::break_with_val_expr, $2, 0); }
                | RANGE { $$ = ExprNode::RangeExpr(ExprNode::range_right, 0, 0); }
                | RANGE ExprWithoutBlock { $$ = ExprNode::RangeExpr(ExprNode::range_right, $2, 0); }
                | RANGE ExprWithBlock { $$ = ExprNode::RangeExpr(ExprNode::range_right, $2, 0); }
                | ExprWithoutBlock RANGE { $$ = ExprNode::RangeExpr(ExprNode::range_left, $1, 0); }
                | ExprWithBlock RANGE { $$ = ExprNode::RangeExpr(ExprNode::range_left, $1, 0); }
                | ExprWithoutBlock RANGE ExprWithoutBlock { $$ = ExprNode::RangeExpr(ExprNode::range_expr, $1, $3); }
                | ExprWithoutBlock RANGE ExprWithBlock { $$ = ExprNode::RangeExpr(ExprNode::range_expr, $1, $3); }
                | ExprWithBlock RANGE ExprWithoutBlock { $$ = ExprNode::RangeExpr(ExprNode::range_expr, $1, $3); }
                | ExprWithBlock RANGE ExprWithBlock { $$ = ExprNode::RangeExpr(ExprNode::range_expr, $1, $3); }
                | RETURN { $$ = ExprNode::OperatorExpr(ExprNode::return_expr, 0, 0); }
                | RETURN ExprWithoutBlock { $$ = ExprNode::OperatorExpr(ExprNode::return_expr, $2, 0); }
                | RETURN ExprWithBlock { $$ = ExprNode::OperatorExpr(ExprNode::return_expr, $2, 0); }
                | ExprWithoutBlock '.' ID { $$ = ExprNode::CallAccessExpr(ExprNode::field_access_expr, $3, $1, 0); }
                | ExprWithBlock '.' ID { $$ =  ExprNode::CallAccessExpr(ExprNode::field_access_expr, $3, $1, 0); }
                | ExprWithoutBlock '.' ID '(' ExprListEmpty ')' { $$ =  ExprNode::CallAccessExpr(ExprNode::method_expr, $3, $1, $5); }
                | ExprWithBlock '.' ID '(' ExprListEmpty ')' { $$ =  ExprNode::CallAccessExpr(ExprNode::method_expr, $3, $1, $5); }
                | PathCallExpr { $$ = $1 }
                | PathCallExpr '(' ExprListEmpty ')' { $$ = ExprNode::StaticMethod(ExprNode::static_method, $1, $3); }
                | ExprWithoutBlock '{' StructExprFieldList '}' { $$ = ExprNode::FieldListAccess(ExprNode::struct_creation, $1, $3); }
                | '(' ExprWithBlock ')' { $$ = $2; }
                |'(' ExprWithoutBlock ')' { $$ = $2; }
                | ExprWithBlock AS Type //ToDo  добавить в enum и создать новый элемент
                | ExprWithoutBlock AS Type //ToDo добавить в enum и создать новый элемент Expr
                ;


PathCallExpr: ID { $$ =  ExprNode::CallAccessExpr(ExprNode::id_, $1, 0, 0); }
            | SUPER { $$ =  ExprNode::CallAccessExpr(ExprNode::super_expr, new string("super"), 0, 0); }
            | SELF { $$ =  ExprNode::CallAccessExpr(ExprNode::self_expr, new string("self"), 0, 0); }
            | PathCallExpr DOUBLEDOTS ID { $$ = ExprNode::PathCallExpr(ExprNode::path_call_expr, $3, $1); }
            ;



StructExprFieldList:  StructExprField { $$ = new ExprListNode($1); }
                    | ',' StructExprField { $$ = new ExprListNode($2); }
                    | StructExprFieldList ',' StructExprField { $$ = ExprListNode::Append($1, $3); }
                    ;
StructExprField: ID ':' ExprWithoutBlock  { $$ = ExprNode::ExprFromStructField(ExprNode::struct_field_expr, $1, $3); }
               | ID ':' ExprWithBlock   { $$ = ExprNode::ExprFromStructField(ExprNode::struct_field_expr, $1, $3); }
               ;

ExprWithBlock: BlockExpr { $$ = $1; }
             | LoopExpr { $$ = $1; }
             | IfExpr { $$ = $1; }
             ;


BlockExpr: '{' StmtList '}' { $$ = ExprNode::BlockExpr(ExprNode::block_expr, 0, $2); }
         | '{' ExprWithoutBlock '}' { $$ = ExprNode::BlockExpr(ExprNode::block_expr, $2, 0); }
         | '{' StmtList ExprWithoutBlock '}' { $$ = ExprNode::BlockExpr(ExprNode::block_expr, $3, $2); }
         | '{' '}' { $$ = ExprNode::BlockExpr(ExprNode::block_expr, 0, 0); }
         ;

LoopExpr: InfiniteLoopExpr { $$ = $1; }
        | PredicateLoopExpr { $$ = $1; }
        | IteratorLoopExpr { $$ = $1; }
        ;

InfiniteLoopExpr: LOOP BlockExpr { $$ = ExprNode::CycleExpr(ExprNode::loop_expr, 0, $2, 0); }
                ;

PredicateLoopExpr: WHILE  ExprWithBlock  BlockExpr { $$ = ExprNode::CycleExpr(ExprNode::loop_while, $2, $3, 0); }
                 | WHILE  ExprWithoutBlock  BlockExpr { $$ = ExprNode::CycleExpr(ExprNode::loop_while, $2, $3, 0); }
                 ;

IteratorLoopExpr: FOR  ID IN ExprWithBlock  BlockExpr { $$ = ExprNode::CycleExpr(ExprNode::loop_for, $4, $5, $2); }
                | FOR  ID IN ExprWithoutBlock  BlockExpr { $$ = ExprNode::CycleExpr(ExprNode::loop_for, $4, $5, $2); }
                ;

IfExpr: SimpleIfElseExpr { $$ = $1; }
      | SimpleIfElseExpr ELSE BlockExpr { $$ = ExprNode::AddElseBlock($1, $3) }
      ;


SimpleIfElseExpr: SimpleIfExpr  { $$ = ExprNode::IfExprList($1); }
                | SimpleIfElseExpr ELSE SimpleIfExpr { $$ = ExprNode::AddIfBlock($1, $3); }
                ;

SimpleIfExpr: IF  ExprWithoutBlock  BlockExpr { $$ = ExprNode::IfExpr(ExprNode::if_expr, $2, $3); }
            | IF  ExprWithBlock  BlockExpr  { $$ = ExprNode::IfExpr(ExprNode::if_expr, $2, $3); }
            ;


/*-------------------------TYPE -------------------------- */

Type: BOOL { $$ = new TypeNode(TypeNode::bool_); }
    | CHAR { $$ = new TypeNode(TypeNode::char_); }
    | FLOAT { $$ = new TypeNode(TypeNode::float_); }
    | INT { $$ = new TypeNode(TypeNode::int_); }
    | STRING { $$ = new TypeNode(TypeNode::string_); }
    | PathCallExpr { $$ = new TypeNode(TypeNode::id_, $1); } //ToDO поменять тип на pathCallExp в enum и хранить элемент в Expr
    | '[' Type ';' ExprWithBlock ']' { $$ = new TypeNode(TypeNode::array_, $2, $4); }
    | '[' Type ';' ExprWithoutBlock ']' { $$ = new TypeNode(TypeNode::array_, $2, $4); }
    ;
    /* Не доделан. Можно добавить TupleType */

/*---------------------- VISIBILITY ------------------------- */

Visibility: PUB               { $$ = pub; }
          | PUB '(' SUPER ')' { $$ = self; }
          | PUB '(' SELF ')'  { $$ = super; }
          ;

%%

void yyerror(char const *s)
{
    printf("%s\n",s);
}
