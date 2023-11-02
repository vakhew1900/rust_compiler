%{
    #include <iostream>
    void yyerror(char const* s);
    extern int yylex(void);
    using namespace std;
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
    AssociatedItemNode* associated_item;
    AssociatedItemListNode* associated_items;
    TraitNode* trait;
    ImplStmtNode* impl_stmt;
    TypeNode* type;
}

%type <prg>Program
%type <expr>ExprWithoutBlock
%type <expr>ExprWithBlock
%type <expr>BlockExpr
%type <expr>StructExprField
%type <expr_list>ExprList
%type <expr_list>ExprListEmpty
%type <expr_list>StructExprFieldList
%type <expr_list>StructExprFieldListEmpty
%type <stmt>Stmt
%type <stmt_list>StmtList
%type <let_stmt>LetStmt
%type <mod_stmt>ModuleStmt
%type <item>Item
%type <item>SimpleItem
%type <item_list>ItemList
%type <item_list>ItemListEmpty
%type <struct_>StructStruct
%type <struct_item>StructField
%type <struct_items>StructFieldList
%type <struct_items>StructFieldListEmpty
%type <enum_stmt>EnumStmt
%type <enum_item>EnumItem
%type <enum_items>EnumItemList
%type <enum_items>EnumItemListEmpty
%type <function_stmt>FuncStmt
%type <function_param>FuncParam
%type <function_params>FuncParamList
%type <function_params>FuncParamListEmpty
%type <const_stmt>ConstStmt
%type <associated_item>AssociatedItem
%type <associated_items>AssociatedItemList
%type <associated_items>AssociatedItemListEmpty
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
%left '!' '&' UMINUS USTAR /*  - * */
%nonassoc '?'
%left '.' '['  DOUBLEDOTS
%nonassoc  '(' ')'

%start Program

%%


/* ---------------------- PROGRAM --------------------------- */

Program: ItemListEmpty { $$ = new ProgramNode($1); }
/* Необходимо уточнить, надо ли как-то обозначить, что Stmt все должны быть Item, иначе программа не заработает */

/* ----------------------------- STATEMENT -----------------------------  */


StmtList: Stmt
        | StmtList Stmt
        ;

Stmt: ';'
    | LetStmt
    | ExprStmt
    ;

ItemListEmpty: /*empty*/
             | ItemList
             ;

ItemList: Item
         | ItemList Item
         ;

Item: SimpleItem
     | Visibility SimpleItem
     ;

SimpleItem:  FuncStmt
          | StructStmt
          | EnumStmt
          | ImplStmt
          | TraitStmt
          | ConstStmt
          | ModuleStmt
          ;

/* ---------- Function ------------ */

FuncStmt: DecFuncStmt
        | ImplFuncStmt
        ;

DecFuncStmt: FN ID '(' FuncParamListEmpty ')' ';'
           | FN ID '(' FuncParamListEmpty ')' RIGHT_ARROW  Type ';'
           ;

ImplFuncStmt: FN ID '(' FuncParamListEmpty ')' BlockExpr
            | FN ID '(' FuncParamListEmpty ')' RIGHT_ARROW  Type BlockExpr
            ;

FuncParamListEmpty: /* empty */
               | FuncParamList
               ;

FuncParamList: SELF
             | SELF_REF
             | MUT_SELF_REF
             | FuncParam
             | FuncParamList ',' FuncParam
             ;

FuncParam: ID ':' Type /* Возможен конфликт */
         | MUT ID ':' Type
         | ID ':' MUT_REF Type
         | ID ':' '&' Type
         ;

/* ========== Struct =========== */

StructStmt: StructStruct
          | TupleStruct  /* Надо ли ? */
          ;

StructStruct : STRUCT ID '{' StructFieldListEmpty '}'
             ;

StructFieldListEmpty: /* empty */
                    | StructFieldList
                    | StructFieldList ','
                    ;

StructFieldList: StructField
               | StructFieldList ',' StructField
               ;

StructField: ID ':' Type  /* Возможен конфликт с FunctionParam */
           | Visibility ID ':' Type
           ;

/*--- TupleStruct ----*/

TupleStruct: STRUCT ID '(' TupleFieldListEmpty ')'
           ;

TupleFieldListEmpty: /* empty */
                    | TupleFieldList
                    | TupleFieldList ','
                    ;

TupleFieldList: Type /* Возможен конфликт */
               | Visibility Type
               | TupleFieldList ',' Type
               | TupleFieldList ',' Visibility Type
               ;

/* ============= ENUM ================ */

EnumStmt: ENUM ID '{' EnumItemListEmpty '}'
        ;

EnumItemListEmpty: /* empty */
                 | ','
                 | EnumItemList
                 | EnumItemList ','
                 ;

EnumItemList: EnumItem
            | EnumItemList ',' EnumItem
            ;

EnumItem: ID
        | Visibility ID
        | ID '=' ExprWithBlock /* В таком случае ID  должен быть всегда только целочисленным числом. Нельзя на парсере определить такое*/
        | ID '=' ExprWithoutBlock
        | Visibility ID '=' ExprWithBlock
        | Visibility ID '=' ExprWithoutBlock
        | Visibility ID '{' StructFieldListEmpty '}'
        | ID '{' StructFieldListEmpty '}'
        ;

/* =========== IMPL ================ */

ImplStmt: IMPL Type '{'AssociatedItemListEmpty '}'
        | IMPL ID FOR Type '{'AssociatedItemListEmpty '}'
        ;

AssociatedItemListEmpty: /* empty */
                       | AssociatedItemList
                       ;

AssociatedItemList: AssociatedItem
                  | AssociatedItemList AssociatedItem
                  ;

/* Необходима еще проверка для Impl то что FuncStmt является именно реализацией */
AssociatedItem: FuncStmt
              | ConstStmt
              | Visibility FuncStmt
              | Visibility ConstStmt
              ;


/* ============ TRAIT ================ */

TraitStmt: TRAIT ID '{' AssociatedItemListEmpty '}'
         ;

/* ============ CONST =============== */

ConstStmt: CONST ID ':' Type '=' ExprWithBlock ';'
         | CONST ID ':' Type '=' ExprWithoutBlock ';'
         | CONST ID ':' Type ';'
         ;

/* =========== Module ================= */

ModuleStmt: MOD ID ';'
          | MOD ID '{' ItemListEmpty '}'
          ;

/* ========= LetStmt ============ */
LetStmt: LET ID '=' ExprWithBlock ';'
       | LET ID '=' ExprWithoutBlock ';'
       | LET ID ':' Type '=' ExprWithBlock ';'
       | LET ID ':' Type '=' ExprWithoutBlock ';'
       | LET MUT ID ';'
       | LET MUT ID ':' Type ';'
       | LET MUT ID '=' ExprWithBlock ';'
       | LET MUT ID '=' ExprWithoutBlock ';'
       | LET MUT ID ':' Type '=' ExprWithBlock ';'
       | LET MUT ID ':' Type '=' ExprWithoutBlock ';'
       ;

/* === Expression Statement === */
ExprStmt: ExprWithoutBlock ';'
        | ExprWithBlock ';'
        ;
        /* конфликт при  "| ExprWithBlock"


/*----------------------- EXPRESSION ---------------------- */

ExprListEmpty: /*empty*/
             | ExprList ','
             | ExprList
             ;

ExprList: ExprWithBlock { $$ = new ExprListNode($1); }
        | ExprWithoutBlock { $$ = new ExprListNode($1); }
        | ExprList ',' ExprWithBlock { $$ = ExprListNode::Append($1, $3); }
        | ExprList ',' ExprWithoutBlock { $$ = ExprListNode::Append($1, $3); }
        ;

ExprWithoutBlock: CHAR_LITERAL { $$ = ExprNode::ExprFromCharLiteral(char_lit, $1); }
                | STRING_LITERAL { $$ = ExprNode::ExprFromStringLiteral(string_lit, $1);  }
                | RAW_STRING_LITERAL { $$ = ExprNode::ExprFromStringLiteral(raw_string_lit, $1); }
                | INT_LITERAL { $$ = ExprNode::ExprFromIntLiteral(int_lit, $1); }
                | FLOAT_LITERAL { $$ = ExprNode::ExprFromFloatLiteral(float_lit, $1); }
                | TRUE { $$ = ExprNode::ExprFromBoolLiteral(bool_lit, $1); }
                | FALSE { $$ = ExprNode::ExprFromBoolLiteral(bool_lit, $1); }
                | ExprWithoutBlock '+' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(plus, $1, $3); }
                | ExprWithoutBlock '+' ExprWithBlock { $$ = ExprNode::OperatorExpr(plus, $1, $3); }
                | ExprWithBlock '+' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(plus, $1, $3); }
                | ExprWithBlock '+' ExprWithBlock { $$ = ExprNode::OperatorExpr(plus, $1, $3); }
                | ExprWithoutBlock '-' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(minus, $1, $3); }
                | ExprWithoutBlock '-' ExprWithBlock { $$ = ExprNode::OperatorExpr(minus, $1, $3); }
                | ExprWithBlock '-' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(minus, $1, $3); }
                | ExprWithBlock '-' ExprWithBlock { $$ = ExprNode::OperatorExpr(minus, $1, $3); }
                | ExprWithoutBlock '/' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(div_expr, $1, $3); }
                | ExprWithoutBlock '/' ExprWithBlock { $$ = ExprNode::OperatorExpr(div_expr, $1, $3); }
                | ExprWithBlock '/' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(div_expr, $1, $3); }
                | ExprWithBlock '/' ExprWithBlock { $$ = ExprNode::OperatorExpr(div_expr, $1, $3); }
                | ExprWithoutBlock '*' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(mul_expr, $1, $3); }
                | ExprWithoutBlock '*' ExprWithBlock { $$ = ExprNode::OperatorExpr(mul_expr, $1, $3); }
                | ExprWithBlock '*' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(mul_expr, $1, $3); }
                | ExprWithBlock '*' ExprWithBlock { $$ = ExprNode::OperatorExpr(mul_expr, $1, $3); }
                | ExprWithoutBlock '%' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(mod, $1, $3); }
                | ExprWithoutBlock '%' ExprWithBlock { $$ = ExprNode::OperatorExpr(mod, $1, $3); }
                | ExprWithBlock '%' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(mod, $1, $3); }
                | ExprWithBlock '%' ExprWithBlock { $$ = ExprNode::OperatorExpr(mod, $1, $3); }
                | ExprWithoutBlock AND ExprWithoutBlock { $$ = ExprNode::OperatorExpr(and_, $1, $3); }
                | ExprWithoutBlock AND ExprWithBlock { $$ = ExprNode::OperatorExpr(and_, $1, $3); }
                | ExprWithBlock AND ExprWithoutBlock { $$ = ExprNode::OperatorExpr(and_, $1, $3); }
                | ExprWithBlock AND ExprWithBlock { $$ = ExprNode::OperatorExpr(and_, $1, $3); }
                | ExprWithoutBlock OR ExprWithoutBlock { $$ = ExprNode::OperatorExpr(or_, $1, $3); }
                | ExprWithoutBlock OR ExprWithBlock { $$ = ExprNode::OperatorExpr(or_, $1, $3); }
                | ExprWithBlock OR ExprWithoutBlock { $$ = ExprNode::OperatorExpr(or_, $1, $3); }
                | ExprWithBlock OR ExprWithBlock { $$ = ExprNode::OperatorExpr(or_, $1, $3); }
                | ExprWithoutBlock '=' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(asign, $1, $3); }
                | ExprWithoutBlock '=' ExprWithBlock { $$ = ExprNode::OperatorExpr(asign, $1, $3); }
                | ExprWithBlock '=' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(asign, $1, $3); }
                | ExprWithBlock '=' ExprWithBlock { $$ = ExprNode::OperatorExpr(asign, $1, $3); }
                | ExprWithoutBlock EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(equal, $1, $3); }
                | ExprWithoutBlock EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(equal, $1, $3); }
                | ExprWithBlock EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(equal, $1, $3); }
                | ExprWithBlock EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(equal, $1, $3); }
                | ExprWithoutBlock NOT_EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(not_equal, $1, $3); }
                | ExprWithoutBlock NOT_EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(not_equal, $1, $3); }
                | ExprWithBlock NOT_EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(not_equal, $1, $3); }
                | ExprWithBlock NOT_EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(not_equal, $1, $3); }
                | ExprWithoutBlock '>' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(greater, $1, $3); }
                | ExprWithoutBlock '>' ExprWithBlock { $$ = ExprNode::OperatorExpr(greater, $1, $3); }
                | ExprWithBlock '>' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(greater, $1, $3); }
                | ExprWithBlock '>' ExprWithBlock { $$ = ExprNode::OperatorExpr(greater, $1, $3); }
                | ExprWithoutBlock '<' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(less, $1, $3); }
                | ExprWithoutBlock '<' ExprWithBlock { $$ = ExprNode::OperatorExpr(less, $1, $3); }
                | ExprWithBlock '<' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(less, $1, $3); }
                | ExprWithBlock '<' ExprWithBlock { $$ = ExprNode::OperatorExpr(less, $1, $3); }
                | ExprWithoutBlock GREATER_EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(greater_equal, $1, $3); }
                | ExprWithoutBlock GREATER_EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(greater_equal, $1, $3); }
                | ExprWithBlock GREATER_EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(greater_equal, $1, $3); }
                | ExprWithBlock GREATER_EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(greater_equal, $1, $3); }
                | ExprWithoutBlock LESS_EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(less_equal, $1, $3); }
                | ExprWithoutBlock LESS_EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(less_equal, $1, $3); }
                | ExprWithBlock LESS_EQUAL ExprWithoutBlock { $$ = ExprNode::OperatorExpr(less_equal, $1, $3); }
                | ExprWithBlock LESS_EQUAL ExprWithBlock { $$ = ExprNode::OperatorExpr(less_equal, $1, $3); }
                | '-' ExprWithoutBlock %prec UMINUS { $$ = ExprNode::OperatorExpr(uminus, $2, 0); }
                | '-' ExprWithBlock %prec UMINUS { $$ = ExprNode::OperatorExpr(uminus, $2, 0); }
                | '!' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(negotation, $2, 0); }
                | '!' ExprWithBlock { $$ = ExprNode::OperatorExpr(negotation, $2, 0); }
                | ExprWithoutBlock '?' { $$ = ExprNode::OperatorExpr(question, $1, 0); }
                | ExprWithBlock '?' { $$ = ExprNode::OperatorExpr(question, $1, 0); }
                | '*' ExprWithoutBlock %prec USTAR { $$ = ExprNode::OperatorExpr(ustar, $2, 0); }
                | '*' ExprWithBlock %prec USTAR { $$ = ExprNode::OperatorExpr(ustar, $2, 0); }
                | '&' ExprWithoutBlock { $$ = ExprNode::OperatorExpr(link, $2, 0); }
                | '&' ExprWithBlock { $$ = ExprNode::OperatorExpr(link, $2, 0); }
                | '[' ExprListEmpty ']'  { $$ = ExprNode::ArrExprFromList(array_expr, $2); }
                | '[' ExprWithoutBlock ';' ExprWithoutBlock ']' { $$ = ExprNode::ArrExprAutoFill(array_expr_auto_fill, $2, $4); }
                | '[' ExprWithoutBlock ';' ExprWithBlock ']' { $$ = ExprNode::ArrExprAutoFill(array_expr_auto_fill, $2, $4); }
                | '[' ExprWithBlock ';' ExprWithoutBlock ']' { $$ = ExprNode::ArrExprAutoFill(array_expr_auto_fill, $2, $4); }
                | '[' ExprWithBlock ';' ExprWithBlock ']' { $$ = ExprNode::ArrExprAutoFill(array_expr_auto_fill, $2, $4); }
                | ExprWithoutBlock '[' ExprWithoutBlock ']' { $$ = ExprNode::OperatorExpr(index_expr, $1, $3); }
                | ExprWithoutBlock '[' ExprWithBlock ']' { $$ = ExprNode::OperatorExpr(index_expr, $1, $3); }
                | ExprWithBlock '[' ExprWithoutBlock ']' { $$ = ExprNode::OperatorExpr(index_expr, $1, $3); }
                | ExprWithBlock '[' ExprWithBlock ']' { $$ = ExprNode::OperatorExpr(index_expr, $1, $3); }
                | ExprWithoutBlock '.' INT_LITERAL { $$ = ExprNode::TupleExpr(tuple_expr, $1, $3); }
                | ExprWithBlock '.' INT_LITERAL { $$ = ExprNode::TupleExpr(tuple_expr, $1, $3); }
                | CONTINUE { $$ = ExprNode::OperatorExpr(continue_expr, 0, 0); }
                | BREAK { $$ = ExprNode::OperatorExpr(break_expr, 0, 0); }
                | RANGE { $$ = ExprNode::RangeExpr(range_right, 0, 0); }
                | RANGE ExprWithoutBlock { $$ = ExprNode::RangeExpr(range_right, $2, 0); }
                | RANGE ExprWithBlock { $$ = ExprNode::RangeExpr(range_right, $2, 0); }
                | ExprWithoutBlock RANGE { $$ = ExprNode::RangeExpr(range_left, $1, 0); }
                | ExprWithBlock RANGE { $$ = ExprNode::RangeExpr(range_left, $1, 0); }
                | ExprWithoutBlock RANGE ExprWithoutBlock { $$ = ExprNode::RangeExpr(range_expr, $1, $3); }
                | ExprWithoutBlock RANGE ExprWithBlock { $$ = ExprNode::RangeExpr(range_expr, $1, $3); }
                | ExprWithBlock RANGE ExprWithoutBlock { $$ = ExprNode::RangeExpr(range_expr, $1, $3); }
                | ExprWithBlock RANGE ExprWithBlock { $$ = ExprNode::RangeExpr(range_expr, $1, $3); }
                | RETURN { $$ = ExprNode::OperatorExpr(return_expr, 0, 0); }
                | RETURN ExprWithoutBlock { $$ = ExprNode::OperatorExpr(return_expr, $2, 0); }
                | RETURN ExprWithBlock { $$ = ExprNode::OperatorExpr(return_expr, $2, 0); }
                | ExprWithoutBlock '.' ID { $$ = ExprNode::CallAccessExpr(field_access_expr, $3, $1, 0); }
                | ExprWithBlock '.' ID { $$ =  ExprNode::CallAccessExpr(field_access_expr, $3, $1, 0); }
                | ExprWithoutBlock '.' ID '(' ExprListEmpty ')' { $$ =  ExprNode::CallAccessExpr(method_expr, $3, $1, $5); }
                | ExprWithBlock '.' ID '(' ExprListEmpty ')' { $$ =  ExprNode::CallAccessExpr(method_expr, $3, $1, $5); }
                | PathCallExpr { $$ = $1 } // ????????
                | PathCallExpr '(' ExprListEmpty ')' { $$ = ExprNode::StaticMethod(static_method, $1, $3); } // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                | PathCallExpr '{' StructExprFieldListEmpty '}' { $$ = ExprNode::FieldListAccess(static_method, $1, $3); } // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                | '(' ExprWithBlock ')' { $$ = $2; }
                |'(' ExprWithoutBlock ')' { $$ = $2; }
                ;


PathCallExpr: ID { $$ =  ExprNode::CallAccessExpr(id_, $1, 0, 0); }
            | SUPER { $$ =  ExprNode::CallAccessExpr(super_expr, "super", 0, 0); }
            | SELF { $$ =  ExprNode::CallAccessExpr(self_expr, "self", 0, 0); }
            | PathCallExpr DOUBLEDOTS ID { $$ = ExprNode::PathCallExpr(path_call_expr, $3, $1); }
            ;

StructExprFieldListEmpty: /*empty*/
                        | StructExprFieldList
                        ;

StructExprFieldList: ',' StructExprField
                    | StructExprFieldList ',' StructExprField
                    ;
StructExprField:
               | ID ':' ExprWithoutBlock
               | ID ':' ExprWithBlock  // Мб сделать проще и юзать тут тип?
               ;

ExprWithBlock: BlockExpr
             | LoopExpr
             | IfExpr
             ;


BlockExpr: '{' StmtList '}'
         | '{' ExprWithoutBlock '}'
         | '{' StmtList ExprWithoutBlock '}'
         | '{' '}'
         ;



LoopExpr: InfiniteLoopExpr
        | PredicateLoopExpr
        | IteratorLoopExpr
        ;

InfiniteLoopExpr: LOOP BlockExpr
                ;

PredicateLoopExpr: WHILE '(' ExprWithBlock ')' BlockExpr
                 | WHILE '(' ExprWithoutBlock ')' BlockExpr
                 ;

IteratorLoopExpr: FOR '(' ID IN ExprWithBlock ')' BlockExpr
                | FOR '(' ID IN ExprWithoutBlock ')' BlockExpr
                ;

IfExpr: SimpleIfElseExpr
      | SimpleIfElseExpr ELSE BlockExpr
      ;


SimpleIfElseExpr: SimpleIfExpr
                | SimpleIfElseExpr ELSE SimpleIfExpr
                ;

SimpleIfExpr: IF '(' ExprWithoutBlock ')' BlockExpr
            | IF '(' ExprWithBlock ')' BlockExpr
            ;


/*-------------------------TYPE -------------------------- */

Type: BOOL { $$ = new TypeNode(bool_); }
    | CHAR { $$ = new TypeNode(char_); }
    | FLOAT { $$ = new TypeNode(float_); }
    | INT { $$ = new TypeNode(int_); }
    | STRING { $$ = new TypeNode(string_); }
    | ID { $$ = new TypeNode(id_); }
    | '[' Type ';' ExprWithBlock ']' { $$ = new TypeNode(array_, $2, $4); }
    | '[' Type ';' ExprWithoutBlock ']' { $$ = new TypeNode(array_, $2, $4); }
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