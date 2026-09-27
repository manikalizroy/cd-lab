#include <stdio.h>
#include <string.h>

#define MAX 20
#define LEN 20

struct instruction
{
    char result[LEN];
    char op1[LEN];
    char op2[LEN];
    char op;
};

struct instruction code[MAX];

int n;

/* Check whether a string is a number */
int isNumber(char *s)
{
    int i = 0;

    if (s[0] == '-')
        i = 1;

    if (s[i] == '\0')
        return 0;

    while (s[i] != '\0')
    {
        if (s[i] < '0' || s[i] > '9')
            return 0;

        i++;
    }

    return 1;
}

/* Return constant value of a variable, if known */
char *getValue(char *var)
{
    for (int i = 0; i < n; i++)
    {
        if (code[i].op == '=' &&
            strcmp(code[i].result, var) == 0 &&
            isNumber(code[i].op1))
        {
            return code[i].op1;
        }
    }

    return var;
}

/* Perform constant propagation */
void constantPropagation()
{
    for (int i = 0; i < n; i++)
    {
        /* Propagate first operand */
        strcpy(code[i].op1, getValue(code[i].op1));

        /* Propagate second operand */
        if (code[i].op != '=')
        {
            strcpy(code[i].op2, getValue(code[i].op2));
        }
    }
}

int main()
{
    printf("Enter number of instructions: ");
    scanf("%d", &n);

    printf("Enter instructions:\n");
    printf("Example:\n");
    printf("a = 5\n");
    printf("b = a + 10\n");
    printf("c = b * 2\n\n");

    for (int i = 0; i < n; i++)
    {
        char equal;

        /* Read: result = operand */
        scanf("%s %c %s",
              code[i].result,
              &equal,
              code[i].op1);

        /* Assignment */
        if (equal == '=')
        {
            /* Check if there is another operator */
            char next;
            int ch = getchar();

            if (ch == '\n' || ch == EOF)
            {
                code[i].op = '=';
                strcpy(code[i].op2, "");
            }
            else
            {
                ungetc(ch, stdin);

                scanf(" %c %s",
                      &code[i].op,
                      code[i].op2);
            }
        }
    }

    constantPropagation();

    printf("\nAfter Constant Propagation:\n");

    for (int i = 0; i < n; i++)
    {
        if (code[i].op == '=')
        {
            printf("%s = %s\n",
                   code[i].result,
                   code[i].op1);
        }
        else
        {
            printf("%s = %s %c %s\n",
                   code[i].result,
                   code[i].op1,
                   code[i].op,
                   code[i].op2);
        }
    }

    return 0;
}
