%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'

%%
expr : expr '+' expr
     | expr '-' expr
     | expr '*' expr
     | expr '/' expr
     | '(' expr ')'
     | NUMBER
     ;
%%

int main()
{
    printf("Enter an arithmetic expression: ");

    if (yyparse() == 0)
        printf("Valid expression\n");
    else
        printf("Invalid expression\n");

    return 0;
}

void yyerror(const char *s)
{
    /* Error message handled in main */
}
