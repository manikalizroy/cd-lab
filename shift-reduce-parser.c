#include <stdio.h>
#include <string.h>

char stack[100], input[100];
int top = -1, i = 0;

int main()
{
    printf("Grammar:\n");
    printf("E -> E+E | E*E | (E) | i\n");

    printf("\nEnter the input string: ");
    scanf("%99s", input);

    int len = strlen(input);

    printf("\n%-20s %-20s %-20s\n",
           "Stack", "Input", "Action");
    printf("--------------------------------------------------\n");

    while (1)
    {
        // Accept if input is consumed and stack is E
        if (i == len && top == 0 && stack[0] == 'E')
        {
            printf("%-20s %-20s ACCEPT\n",
                   stack, "$");
            break;
        }

        // Shift operation
        if (i < len)
        {
            stack[++top] = input[i++];
            stack[top + 1] = '\0';

            printf("%-20s %-20s SHIFT\n",
                   stack, input + i);
        }

        // Reduce i -> E
        int reduced = 1;

        while (reduced)
        {
            reduced = 0;

            // E -> i
            if (top >= 0 && stack[top] == 'i')
            {
                stack[top] = 'E';
                printf("%-20s %-20s REDUCE E->i\n",
                       stack, input + i);
                reduced = 1;
            }

            // E -> (E)
            else if (top >= 2 &&
                     stack[top - 2] == '(' &&
                     stack[top - 1] == 'E' &&
                     stack[top] == ')')
            {
                top -= 2;
                stack[top] = 'E';
                stack[top + 1] = '\0';

                printf("%-20s %-20s REDUCE E->(E)\n",
                       stack, input + i);
                reduced = 1;
            }

            // E -> E+E
            else if (top >= 2 &&
                     stack[top - 2] == 'E' &&
                     stack[top - 1] == '+' &&
                     stack[top] == 'E')
            {
                top -= 2;
                stack[top] = 'E';
                stack[top + 1] = '\0';

                printf("%-20s %-20s REDUCE E->E+E\n",
                       stack, input + i);
                reduced = 1;
            }

            // E -> E*E
            else if (top >= 2 &&
                     stack[top - 2] == 'E' &&
                     stack[top - 1] == '*' &&
                     stack[top] == 'E')
            {
                top -= 2;
                stack[top] = 'E';
                stack[top + 1] = '\0';

                printf("%-20s %-20s REDUCE E->E*E\n",
                       stack, input + i);
                reduced = 1;
            }
        }

        // Reject if all input is consumed but not accepted
        if (i == len && !(top == 0 && stack[0] == 'E'))
        {
            printf("%-20s %-20s REJECT\n",
                   stack, "$");
            break;
        }
    }

    return 0;
}




/* Sample output
Grammar:
E -> E+E | E*E | (E) | i

Enter the input string: (i+i)*i

Stack                Input                Action
--------------------------------------------------
(                    i+i)*i               SHIFT
(i                   +i)*i                SHIFT
(E                   +i)*i                REDUCE E->i
(E+                  i)*i                 SHIFT
(E+i                 )*i                  SHIFT
(E+E                 )*i                  REDUCE E->i
(E                   )*i                  REDUCE E->E+E
(E)                  *i                   SHIFT
E                    *i                   REDUCE E->(E)
E*                   i                    SHIFT
E*i                                       SHIFT
E*E                                       REDUCE E->i
E                                         REDUCE E->E*E
E                    $                    ACCEPT

----------------------------------------------------

Grammar:
E -> E+E | E*E | (E) | i

Enter the input string: i(I+I

Stack                Input                Action
--------------------------------------------------
i                    (I+I                 SHIFT
E                    (I+I                 REDUCE E->i
E(                   I+I                  SHIFT
E(I                  +I                   SHIFT
E(I+                 I                    SHIFT
E(I+I                                     SHIFT
E(I+I                $                    REJECT

*/
