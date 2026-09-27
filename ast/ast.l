%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char data[5];
    struct node *left;
    struct node *right;
}Node;

#include "y.tab.h"

%}

%%

[a-zA-Z][a-zA-Z0-9]*   { strcpy(yylval.str,yytext);
                         return ID; }
[ \t]  ;
"+"    { return '+'; }
"-"    { return '-'; }
"*"    { return '*'; }
"/"    { return '/'; }
"("    { return '('; }
")"    { return ')'; }
[ \n]  { return '\n'; }
.      { return yytext[0]; }

%%
int yywrap()
{
   return 1;
}
