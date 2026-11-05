//The ε-closure of all states of a given NFA

#include <stdio.h>

int main()
{
    int n, e;
    int trans[10][10] = {0};
    int closure[10][10] = {0};

    printf("Enter the number of states: ");
    scanf("%d", &n);

    printf("Enter the number of epsilon transitions: ");
    scanf("%d", &e);

    printf("Enter epsilon transitions (from to): \n(Eg: 0 1\n  1 2)\n");

    for(int i = 0; i < e; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        trans[a][b] = 1;
    }

    // Initialize epsilon closure
    for(int i = 0; i < n; i++)
    {
        closure[i][i] = 1;
    }

    // Add direct epsilon transitions
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(trans[i][j])
                closure[i][j] = 1;
        }
    }

    // Find transitive epsilon closure
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(closure[i][k] && closure[k][j])
                    closure[i][j] = 1;
            }
        }
    }

    // Display epsilon closure of each state
    printf("\nEpsilon Closure of all states:\n");

    for(int i = 0; i < n; i++)
    {
        printf("E-closure(q%d) = { ", i);

        for(int j = 0; j < n; j++)
        {
            if(closure[i][j])
                printf("q%d ", j);
        }

        printf("}\n");
    }

    return 0;
}
