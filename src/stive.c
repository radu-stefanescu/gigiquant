#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "stive.h"

int isStackEmpty(const stackNode* top)
{
    return (top == NULL);
}

void push(stackNode** top, Data v)
{
    stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));
    if(newNode == NULL)
    {
        printf("Eroare la alocarea memoriei!\n");
        return;
    }

    newNode->pretPiata = v;
    newNode->next = *top;
    *top = newNode;
    //printf("Am adaugat %d in stiva!\n", v); 
}

Data pop(stackNode** top)
{
    if(isStackEmpty(*top))
    {
        printf("Stiva este goala, nu avem ce elimina.\n");
        return INT_MIN;
    }

    stackNode *temp = *top;
    Data aux = temp->pretPiata;

    *top = (*top)->next;

    free(temp);
    return aux;

}
  
void deleteStack(stackNode** top)
{
    while(!isStackEmpty(*top))
    {
        stackNode* temp = *top;
        *top = (*top)->next;
        free(temp);
    }
    //printf("Stiva a fost stearsa complet din memorie.\n");
}