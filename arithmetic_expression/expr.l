%{
#include "y.tab.h"
%}

%%
[0-9]+      { return NUMBER; }
[ \t\n]+    { /* Ignore whitespace */ }
.           { return yytext[0]; }
%%

int yywrap()
{
    return 1;
}
