%token BOOL CHAR FLOAT INT STRING
%token TRUE FALSE CHAR_LITERAL INT_LITERAL FLOAT_LITERAL STRING_LITERAL
%token ID
%token FOR LOOP WHILE IN CONTINUE
%token IF ELSE
%token LET MUT CONST
%token FN ENUM STRUCT TRAIN
%token IMPL SELF  PUB SELF_REF MUT_SELF_REF MUT_REF MOD
%token ';' RIGHT_ARROW

/* BREAK и RETURN  в документации почему-то присуствует в приоритетах операций. Стоит наверное с этим разобраться */

%nonassoc BREAK RETURN
%right ':'
%right '='
%nonassoc RANGE   /* .. */
%left OR  /* || */
%left AND /* && */
%left '<' '>'  EQUAL NOT_EQUAL     // == !=
%left '+' '-'
%left '*' '/'
%left '!' '&' UMINUS USTAR /*  - * */
%nonassoc '?'
%left '.' '[' ']'
%nonassoc '(' ')'

%%


/* ---------------------- PROGRAM --------------------------- */

Program: StmtListEmpty /* Необходимо уточнить, надо ли как-то обозначить, что Stmt все должны быть Item, иначе программа не заработает */

/* ----------------------------- STATEMENT -----------------------------  */

StmtListEmpty: /* empty */
             | StmtList
             ;

StmtList: Stmt
        | StmtList Stmt
        ;

Stmt: ';'
    | Item
    | LetStmt
    | Expr ';'
    ;

Item: SimpleItem
      Visibility SimpleItem

SimpleItem:  FuncStmt
          | StructStmt
          | EnumStmt
          | ImplStmt
          | TraitStmt
          | ConstStmt
          ;
          /* ModuleStmt */ /// Можно добавить

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
               | FullFuncParamList
               ;

FullFuncParamList: SelfParam
                 | SelfParam ',' FuncParamList
                 | FuncParamList


SelfParam: SELF,
         | SELF_REF,
         | MUT_SELF_REF
         ;

FuncParamList: FuncParam
             | FuncParamList ',' FuncParam
             ;

FuncParam: ID : Type /* Возможен конфликт */
         | MUT ID : Type
         | ID : MUT_REF Type
         | ID : '&' Type


/* ========== Struct =========== */

StructStmt: StructStruct
          | TupleStruct  /* Надо ли ? */
          ;

StructStruct : STRUCT ID '{' '}'
             | STRUCT ID '{' StructFieldListEmpty '}'
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

TupleStruct: STRUCT ID '(' ')'
           | STRUCT ID '(' TupleFieldListEmpty ')'
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



/* ============ CONST =============== */

ConstStmt: CONST ID ':' Type = Expr ';'
         | CONST ID ':' Type ';'

/* ========= LetStmt ============ */
LetStmt: LET ID = Expr ';'
       | LET ID ':' Type = Expr ';'
       | LET MUT ID ';'
       | LET MUT ID ':' Type ';'
       | LET MUT ID = Expr ';'
       | LET MUT ID ':' Type = Expr ';'
       ;

/*----------------------- EXPRESSION ---------------------- */

Expr: ExprWithoutBlock
    | ExprWithBlock
    ;

BlockExpr: '{' '}'
         | '{' Stmt '}'
         ;

/*-------------------------TYPE -------------------------- */

Type: BOOL
    | CHAR
    | FLOAT
    | INT
    | STRING
    | ID
    | '[' Type ';' Expr ']'
    ;
    /* Не доделан. Можно добавить TupleType */

/*---------------------- VISIBILITY ------------------------- */

Visibility: PUB
          | PUB '(' SUPER ')'
          | PUB '(' SELF ')'
          ;