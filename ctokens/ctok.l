%{
#include <stdio.h>
#include <stdlib.h>
%}

keyword    auto|int|break|continue|case|default|return|char|const|do|double|else|enum>
integer    [0-9]+
string     \"[^\n\"]*\"
identifier [_a-zA-Z][_a-zA-Z0-9]*
comment    "//".*|"/*"(.*|\n)*"*/"

relop      "=="|"!="|">"|"<"|"<="|">="
assignop   "="|"+="|"-="|"*="|"/="|"%="
bitwiseop  "&"|"|"|"^"|"~"|">>"|"<<"
logicalop  "&&"|"||"|"!"
arithop    "+"|"-"|"*"|"/"|"%"

punct      [.,;()\[\]]

%%

#[^\n]*    { printf("Preprocessor Directive: %s\n",yytext); }
{keyword}  { printf("Keyword: %s\n",yytext); }
[a-zA-Z_][a-zA-Z0-9_]*[ \t]*\(    { printf("Function: %s\n",yytext); }
\)         { printf("Enf of function:  %s\n",yytext); }
\{          { printf("Begin block:  %s\n",yytext); }
\}          { printf("End block:  %s\n",yytext); }

{identifier}  { printf("Variable:  %s\n",yytext); }
{integer}  { printf("Integer:  %s\n",yytext); }
{string}   { printf("String:  %s\n",yytext); }
{comment}  { printf("Comment:  %s\n",yytext); }

{relop}    { printf("Relational operator: %s\n",yytext); }
{assignop}   { printf("Assignment operator: %s\n",yytext); }
{bitwiseop}   { printf("Bitwise operator: %s\n",yytext); }
{logicalop}   { printf("Logical operator: %s\n",yytext); }
{arithop}     { printf("Arithmetic operator: %s\n",yytext); }

{punct}       { printf("Punctuator:  %s\n",yytext); }
[ \t\n]+     ;
.            ;

%%

int main()
{
   FILE *file;
   file = fopen("input.c","r");

   if(file == NULL)
   {
        printf("File open error\n");
        exit(1);
   }

   yyin = file;

   yylex();
   fclose(file);
   return 0;
}

int yywrap()
{
   return 1;
}
