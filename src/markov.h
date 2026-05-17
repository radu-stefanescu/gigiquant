#include <stdlib.h>
#include <stdio.h>

struct Fractie
{
    int numarator;
    int numitor;
};
typedef struct Fractie fractie;

int numitor(fractie *a, int nrStari);
void markov(fractie a[][100], int N, fractie probStare[], int nrStari, int K, int zi, int target, FILE *file1);
void ireductibil(fractie *x);
int cmmdc(int a, int b);
fractie adunare(fractie x, fractie y);
fractie inmultire(fractie x, fractie y);
void afisareFractie(fractie x, FILE* file1);