#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double addAtEnd(Node **head, Data v) 
{   
    Node *aux = *head;
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->valoare = v;

    if (*head == NULL) 
    {
        newNode->randament = 0.0f;
        newNode->next = NULL;
        *head = newNode;
        return 0.0f;
    }
    else 
    {
        while (aux->next != NULL) 
            aux = aux->next;

        //Calcul randament
        newNode->randament = (newNode->valoare - aux->valoare) / aux->valoare;

        aux->next = newNode;
        newNode->next = NULL; 
    }
    return newNode->randament;
}

void trunk(double *x, int nrZecimaleExacte)
{
    double p = pow(10.0f, nrZecimaleExacte);
    (*x) = trunc((*x) * p) / p;
}