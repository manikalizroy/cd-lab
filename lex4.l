//implement lexical analyser using lex tool

%{
#include <stdio.h>
%}

%%

^#[^\n]*  { printf("%s \tPreprocessor Diective\n",yytext); }

\".*\"    {
          printf("%s \tString literal\n", yytext); }

[+\-*/%<>=|&!]  { printf("%s \tOperator\n", yytext); }

"int"|"float"|"char"|"for"|"while"|"if"|"else"|"return"  { printf("%s \t Keyword\n", yytext); }

"printf"|"scanf"|"main"  { printf("%s \tFunction\n", yytext); }

[a-zA-Z_][a-zA-Z_0-9]*  { printf("%s \tIdentifier\n", yytext); }

[0-9]+  { printf("%s \tNumber\n", yytext); }

[:;,{}\[\]()]  { printf("%s \tSpecial Symbol\n", yytext); }

[ \t\n]+  { }

.       { printf("Invalid operator"); }


%%

int main()
{
   yyin = fopen("input.c","r");

   if(yyin == NULL)
   {
     printf("Error opening file\n");
     return 1;
   }
   yylex();

   fclose(yyin);
   return 0;
}


int yywrap()
{
   return 1;
}
