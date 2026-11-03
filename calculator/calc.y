%{
#include <stdio.h>
int yylex();
void yyerror(char *s);
%}

%token NUM
%left '+' '-'
%left '*' '/'
%right UMINUS

%%
input : /* empty */
      | input line
      ;

line : expr '\n' { printf("Result: %d\n",$1); }
     ;

expr  : expr '+' expr { $$ = $1 + $3; }
      | expr '-' expr { $$ = $1 - $3; }
      | expr '*' expr { $$ = $1 * $3; }
      | expr '/' expr {
                        if($3 == 0){
                           printf("Division by zero\n");
                           YYERROR;
                        }
                        $$ = $1/$3; }
      | '('expr')'  { $$ = $2; }
      | '-'expr %prec UMINUS { $$ = -$2; }
      | NUM { $$ = $1; }
      ;

%%
int main()
{
   printf("enter an arithmetic expression: \n");
   yyparse();
   return 0;
}

void yyerror(char *s)
{
   printf("invlaid expression\n");
}
