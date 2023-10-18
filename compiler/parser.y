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

Item: FuncStmt
    | StructStmt
    | EnumStmt
    | ImplStmt
    ;
    /* ModuleStmt */ /// Можно добавить


/* ---------- Function ------------ */

FuncStmt: DecFuncStmt
        | ImplFuncStmt
        ;

DecFuncStmt: FN ID '(' FuncParamsEmpty ')' ';'
           | FN ID '(' FuncParamsEmpty ')' RIGHT_ARROW  Type ';'
           ;

ImplFuncStmt: FN ID '(' FuncParamsEmpty ')' BlockExpr
            | FN ID '(' FuncParamsEmpty ')' RIGHT_ARROW  Type BlockExpr
            ;


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

/*-------------------------TYPE -------------------------- */

Type: BOOL
    | CHAR
    | FLOAT
    | INT
    | STRING
    | ID
    /* Не доделан */
    ;