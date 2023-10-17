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

%nonassoc RETURN BREAK
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

/*----------------------- EXPRESSION ---------------------- */


/* ---------------------- STATEMENT -----------------------  */



/*-------------------------TYPE -------------------------- */

Type: BOOL
    | CHAR
    | FLOAT
    | INT
    | STRING
    | ID
    /* Не доделан */
    ;