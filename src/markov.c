#include "markov.h"
#include <stdlib.h>
#include <stdio.h>

int numitor(fractie *a, int nrStari)
{
    int count = 0;
    for(int i = 0; i < nrStari; i++)
    {
        count += a[i].numarator;
    }
    return count;
}

void markov(fractie a[][100], int N, fractie probStare[], int nrStari, int K, int zi, int target, FILE *file1)
{
    if(zi > K) return;

    afisareFractie(probStare[target], file1);
    if(zi != K)
    {
        fprintf(file1, "\n");
    }

    int i, j;
    fractie nextProbStare[100];

    for(i = 0; i < 100; i++)
    {
        nextProbStare[i].numarator = 0;
        nextProbStare[i].numitor = 1;
    }


    for(i = 0; i < nrStari; i++)
    {
            fractie p;
            p.numarator = 0;
            p.numitor = 1;
            for(j = 0; j < nrStari; j++)
            {
                if(probStare[j].numarator != 0 && a[j][i].numarator != 0)
                {
                    p = adunare(p, (inmultire(a[j][i], probStare[j])));
                }
            }
            nextProbStare[i] = p;
    }
    for(i = 0; i < nrStari; i++)
    {
        probStare[i] = nextProbStare[i];
    }

    markov(a, N, probStare, nrStari, K, zi + 1, target, file1);
}

void ireductibil(fractie *x)
{
    int div = cmmdc(x->numarator, x->numitor);
    x->numarator /= div;
    x->numitor /= div;
}

int cmmdc(int a, int b)
{
    while(b)
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

fractie adunare(fractie x, fractie y)
{
    fractie s;
    s.numarator = (x.numarator * y.numitor) + (y.numarator * x.numitor);
    s.numitor = x.numitor * y.numitor;
    ireductibil(&s);
    return s;
}

fractie inmultire(fractie x, fractie y)
{
    fractie p;
    p.numarator = x.numarator * y.numarator;
    p.numitor = x.numitor * y.numitor;
    ireductibil(&p);
    return p;
}

void afisareFractie(fractie x, FILE* file1)
{
    if(x.numarator == 0)
    {
        fprintf(file1, "0");
    }
    else if(x.numitor == 1)
    {
        fprintf(file1, "%d", x.numarator);
    }
    else
    {
        fprintf(file1, "%d/%d", x.numarator, x.numitor);
    }
}