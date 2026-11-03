%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token VALID INVALID

%%
input : /* empty */
      | input line
      ;
line  : VALID '\n' { printf("Valid Identifier\n"); }
      | INVALID '\n' { printf("Invalid Identifier\n"); }
      ;
%%

int main()
{
    printf("Enter an identifier: ");
    yyparse();
    return 0;
}

void yyerror(const char *s)
{
    printf("Invalid Identifier\n");
}
