#include "cozi.h"
#include <stdio.h>
#include <stdlib.h>

Queue* createQueue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    if(q == NULL)
    {
        printf("Eroare la alocarea memoriei.\n");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int isQueueEmpty(const Queue* q)
{
    return (q->front == NULL);
}

void enQueue(Queue* q, int zi, Data diferentaAbs,char *numePiata)
{
    if(q == NULL)
    {
        return;
    }

    queueNode* newNode = (queueNode*)malloc(sizeof(queueNode));
    if(newNode == NULL)
    {
        printf("Eroare la alocarea memoriei!\n");
        return;
    }
    newNode->zi = zi;
    newNode->diferentaAbs = diferentaAbs;
    newNode->numePiata = numePiata;
    newNode->next = NULL;

    if(q->front == NULL)
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    //printf("Adaugare cu succes in coada!\n");
}

void deQueue(Queue* q)
{
    if(q->front == NULL)
    {
        printf("Coada este goala, nu avem ce sa scoatem!\n");
        return;
    }
    queueNode* temp = q->front;
    q->front = q->front->next;
    free(temp);

    if(q->front == NULL)
    {
        q->rear = NULL;
    }

}

void deleteQueue(Queue* q)
{
    if(q == NULL) 
    {
        return; 
    }
    while(q->front != NULL)
    {
        queueNode* temp = q->front;
        q->front = q->front->next;
        
        free(temp);
    }
    free(q);
}
