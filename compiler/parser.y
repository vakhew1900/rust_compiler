%token BOOL CHAR FLOAT INT STRING
%token TRUE FALSE CHAR_LITERAL INT_LITERAL FLOAT_LITERAL STRING_LITERAL
%token ID
%token FOR LOOP WHILE IN CONTINUE BREAK RETURN
%token IF ELSE
%token LET MUT CONST
%token FN ENUM STRUCT TRAIN
%token IMPL SELF  PUB SELF_REF MUT_SELF_REF
%token ';'

/* BREAK и RETURN  в документации почему-то присуствует в приоритетах операций. Стоит наверное с этим разобраться */

%right ':'
%right '='
%nonassoc RANGE   /* .. */
%left OR  /* || */
%left AND /* && */
%left '<' '>'  EQUAL NOT_EQUAL     // == !=
%left '+' '-'
%left '*' '/'
%left '!' UMINUS USTAR /*  - * */
%nonassoc '?'
%left '.' '[' ']'
%nonassoc '(' ')'

%%


/* ---------------------- PROGRAM --------------------------- */


/* ---------------------- LIST ------------------------------ */

/* ---------------------- STATEMENT -----------------------  */

Stmt: ';'
    | LetStmt
    | Expr ';'
    ;

LetStmt: LET ID ';'
       | LET ID ':' Type ';'
       | LET ID = Expr ';'
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