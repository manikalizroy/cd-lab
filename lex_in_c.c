//implementing lexical analyser in c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int i, ch;
    FILE *fp;
    fp = fopen("input.c","r");

    while((ch = fgetc(fp)) != EOF)
    {
        if(isspace(ch))
           continue;

        else if(ch == '/')
        {
           char next;
           next = fgetc(fp);
           if(next == '/')
           {
                while((ch = fgetc(fp)) != '\n' && ch != EOF)
                {
                    printf("Comment\n");
                }
           }
           else if(next == '*')
           {
                 while((ch = fgetc(fp)) != EOF)
                 {
                     if(ch == '*')
                     {
                        next = fgetc(fp);
                        if(next == '/')
                            break;
                     }
                 }
                 printf("Comment\n");
           }
           else
           {
                printf("Operator\n");
                ungetc(next,fp);
           }
        }

        else if(ch == '#')
        {
           char word[50];
           i = 0;

           while((ch = fgetc(fp)) != EOF && ch != '\n')
                word[i++] = ch;

           word[i] = '\0';

           printf("#%s - Preprocessor Directive\n", word);
        }

        else if(ch == '"')
        {
            i=0;
            char word[50];
            while((ch = fgetc(fp)) != '"' && ch != EOF)
            {
                word[i++] = ch;
            }
            word[i] = '\0';
            printf("%s - String Literal\n",word);
        }
        else if(isalpha(ch) || ch == '_')
        {
            i=0;
            char word[50];
            word[i++] = ch;
            while((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_'))
                word[i++] = ch;
            word[i] = '\0';

            if(strcmp(word,"main") == 0 ||
            strcmp(word,"printf") == 0 ||
            strcmp(word,"scanf") == 0 ||
            strcmp(word,"strlen") == 0)
               printf("%s - Function\n",word);

            else if(strcmp(word,"int") == 0 ||
            strcmp(word,"char") == 0 ||
            strcmp(word,"void") == 0 ||
            strcmp(word,"return") == 0 ||
            strcmp(word,"else") == 0 ||
            strcmp(word,"if") == 0 ||
            strcmp(word,"while") == 0 ||
            strcmp(word,"for") == 0)
                printf("%s - Keyword\n",word);
            else
                printf("%s - Identifier\n",word);

        if(ch != EOF)
            ungetc(ch,fp);
        }
        else if(isdigit(ch) || ch == '.')
        {
            i=0;
            char word[50];
            while((ch = fgetc(fp)) != EOF && (isdigit(ch) || ch == '.'))
                word[i++] = ch;
            word[i] = '\0';
            printf("%s - Constant\n",word);
            if(ch != EOF)
               ungetc(ch,fp);
        }
        else if(strchr("+-*<>!=%",ch))
            printf("%c - Operator\n",ch);
        else if(strchr(":;,'{}()[]",ch))
            printf("%c - Special symbol\n",ch);
    }
    fclose(fp);
    return 0;
}
