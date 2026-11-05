//conversion of NFA with epsilon transition to NFA without epsilon transition.
#include <stdio.h>

int main()
{
    int n, m, t, f;
    int i, j, k, a, b, s, p, q;
    char alphabet[10], ch;

    int eps[10][10] = {0};
    int trans[10][10][10] = {0};
    int closure[10][10] = {0};
    int newtrans[10][10][10] = {0};

    int final[10] = {0};
    int newfinal[10] = {0};

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter input symbols:\n");
    for(i = 0; i < m; i++)
        scanf(" %c", &alphabet[i]);

    printf("Enter number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (from symbol to):\n");
    printf("Use $ for epsilon transition\n");

    for(i = 0; i < t; i++)
    {
        scanf("%d %c %d", &a, &ch, &b);

        if(ch == '$')
            eps[a][b] = 1;
        else
        {
            for(j = 0; j < m; j++)
            {
                if(alphabet[j] == ch)
                    trans[a][j][b] = 1;
            }
        }
    }

    printf("Enter number of final states: ");
    scanf("%d", &f);

    printf("Enter final states:\n");
    for(i = 0; i < f; i++)
    {
        scanf("%d", &a);
        final[a] = 1;
    }

    // Find epsilon closure
    for(i = 0; i < n; i++)
        closure[i][i] = 1;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(eps[i][j])
                closure[i][j] = 1;
        }
    }

    // Transitive closure
    for(k = 0; k < n; k++)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                if(closure[i][k] && closure[k][j])
                    closure[i][j] = 1;
            }
        }
    }

    // Find new transitions
    for(i = 0; i < n; i++)
    {
        for(s = 0; s < m; s++)
        {
            for(p = 0; p < n; p++)
            {
                if(closure[i][p])
                {
                    for(q = 0; q < n; q++)
                    {
                        if(trans[p][s][q])
                        {
                            for(j = 0; j < n; j++)
                            {
                                if(closure[q][j])
                                    newtrans[i][s][j] = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    // Find new final states
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(closure[i][j] && final[j])
                newfinal[i] = 1;
        }
    }

    // Display new transitions
    printf("\nNFA without epsilon transitions:\n");

    for(i = 0; i < n; i++)
    {
        for(s = 0; s < m; s++)
        {
            printf("q%d --%c--> { ", i, alphabet[s]);

            for(j = 0; j < n; j++)
            {
                if(newtrans[i][s][j])
                    printf("q%d ", j);
            }

            printf("}\n");
        }
    }

    // Display new final states
    printf("\nNew final states: { ");

    for(i = 0; i < n; i++)
    {
        if(newfinal[i])
            printf("q%d ", i);
    }

    printf("}\n");

    return 0;
}

/*
Sample:
Enter number of states: 5
Enter number of input symbols: 2
Enter input symbols:
a b
Enter number of transitions: 5
Enter transitions (from symbol to):
Use $ for epsilon transition
0 $ 1
1 $ 2
0 a 3
2 b 4
3 $ 4
Enter number of final states: 2
Enter final states:
2 4

OUTPUT
NFA without epsilon transitions:

q0 --a--> { q3 q4 }
q0 --b--> { q4 }

q1 --a--> { }
q1 --b--> { q4 }

q2 --a--> { }
q2 --b--> { q4 }

q3 --a--> { }
q3 --b--> { }

q4 --a--> { }
q4 --b--> { }

New final states: { q0 q1 q2 q3 q4 }
*/
