%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s);
%}

%token NUM

%left '+' '-'
%left '*' '/'
%left UMINUS

%%

input:
      /* empty */
    | input line
    ;

line:
      expr '\n'     { printf("Result = %d\n", $1); }
    ;

expr:
      expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { $$ = $1 / $3; }
    | '(' expr ')'  { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | NUM            { $$ = $1; }
    ;

%%

int main()
{
    printf("Enter arithmetic expressions:\n");
    yyparse();
    return 0;
}

void yyerror(char *s)
{
    printf("Invalid Expression\n");
}
