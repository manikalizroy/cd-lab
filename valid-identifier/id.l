%{
#include "y.tab.h"
%}

%%
[a-zA-Z][a-zA-Z0-9]*  { return VALID; }
[^ \t\n]+             { return INVALID; }
[ \t]+                { /* Ignore whitespace */ }
[ \n]                 { return '\n'; }
%%

int yywrap()
{
    return 1;
}
