%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yylex();
void yyerror(char *s);

typedef struct node {
   char data[5];
   struct node *left;
   struct node *right;
}Node;

Node *root;

Node *createNode(char *data, Node *left, Node *right)
{
    Node *temp = (Node *)malloc(sizeof(Node));

    strcpy(temp->data,data);
    temp->left = left;
    temp->right = right;

    return temp;
}

void postorder(Node *root)
{
   if(root == NULL)
      return ;
   postorder(root->left);
   postorder(root->right);
   printf("%s",root->data);
}

%}

%union
{
   char str[10];
   Node *node;
}

%token <str> ID
%type <node> expr term factor

%left '+' '-'
%left '*' '/'

%%

input: expr '\n'
       {
           root = $1;
           printf("Postorder traversal of AST: \n");
           postorder(root);
           printf("\n");
       };
expr: expr '+' term
      {
         $$ = createNode("+",$1,$3);
      }
    | expr '-' term
      {
         $$ = createNode("-",$1,$3);
      }
    | term
      {
         $$ = $1;
      }
      ;

term: term '*' factor
      {
         $$ = createNode("*",$1,$3);
      }
    | term '/' factor
      {
         $$ = createNode("/",$1,$3);
      }
    | factor
      {
         $$ = $1;
      }
      ;

factor: '(' expr ')'
         {
            $$ = $2;
         }
       | ID
         {
           $$ = createNode($1,NULL,NULL);
         }
         ;

%%

int main()
{
    printf("Enter an expression: ");
    yyparse();
    return 0;
}

void yyerror(char *s)
{
   printf("Invalid expression\n");
}
