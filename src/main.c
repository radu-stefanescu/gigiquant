// Tema1
// Stefanescu Radu Stefan 312AA

#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PRECIZIE 3

int main(int argc, const char *argv[])
{
    if(argc < 3)
    {
        printf("Eroare!\n");
        return 1;
    }
    
    FILE* fileIn = fopen(argv[1], "rt");
    FILE* fileOut = fopen(argv[2], "wt");

    if(fileIn == NULL || fileOut == NULL)
    {
        printf("Nu s-au putut deschide fisierele!\n");
        return 1;
    }
    
    Node *head = NULL;
    int nrObs = 0;
    double x, sharpeRatio = 0.0f, sum = 0.0f, randamentMediu = 0.0f, volatilitate = 0.0f;
    
    if (fscanf(fileIn, "%d", &nrObs) == 1) 
    {
        int i;
        for(i = 0 ; i < nrObs; i++)
        {
            fscanf(fileIn, "%lf", &x);
            sum += addAtEnd(&head, x);
        }
    }
    
    int nrRandamente = nrObs - 1;
    if (nrRandamente > 0) 
    {
        randamentMediu = sum / nrRandamente;
    }

    Node* iter;
    if (head != NULL && head->next != NULL) 
    {
       
       for(iter = head->next; iter != NULL ; iter = iter->next)
       {
            volatilitate += pow((iter->randament - randamentMediu), 2.0);
       }
    }

    if(nrRandamente != 0)
    {
        volatilitate = sqrt(volatilitate / nrRandamente);
    }
    if(volatilitate != 0)
    {
        sharpeRatio = (randamentMediu - 0) / volatilitate;
    }
    
    trunk(&randamentMediu, PRECIZIE);
    trunk(&volatilitate, PRECIZIE);
    trunk(&sharpeRatio, PRECIZIE);

    
    fprintf(fileOut, "%.3lf\n", randamentMediu);
    fprintf(fileOut, "%.3lf\n", volatilitate);
    fprintf(fileOut, "%.3lf\n", sharpeRatio);

    
    while(head != NULL)
    {
        iter = head;
        head = head->next;
        free(iter);
    }

    fclose(fileIn);
    fclose(fileOut);

    return 0;
}
