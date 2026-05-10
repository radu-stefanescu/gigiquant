#include "arbori.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void addAtEndStock(StockNode **head, const char* numeStock)
{
    StockNode *aux = *head;
    StockNode *newNode = (StockNode*)malloc(sizeof(StockNode));
    newNode->symbol = strdup(numeStock);

    if (*head == NULL) 
    {
        newNode->next = NULL;
        *head = newNode;
    }
    else 
    {
        while (aux->next != NULL) 
            aux = aux->next;


        aux->next = newNode;
        newNode->next = NULL; 
    }
}

void createEmptyTree(TreeNode** root, int day)
{
    if(day == 0)
    {
        return;
    }
    *root = (TreeNode*)malloc(sizeof(TreeNode));
    if (*root == NULL) 
    {
        printf("Eroare la alocarea memoriei!\n");
        exit(1);
    }
    (*root)->stocks = NULL;
    (*root)->left = NULL;
    (*root)->right = NULL;
    createEmptyTree(&(*root)->left, day - 1);
    createEmptyTree(&(*root)->right, day - 1);
}

void insertStock(TreeNode** root, char* stockName, float v[], int day, int current)
{
    addAtEndStock(&(*root)->stocks, stockName);
    if(current == day)
    {
        return;
    }
    if(v[current] < v[current + 1])
    {
        insertStock(&(*root)->right, stockName, v, day, current + 1);
    }
    else
    {
        insertStock(&(*root)->left, stockName, v, day, current + 1);
    }
}

void afis(TreeNode* root)  
{
    if(root == NULL) return;
    
    StockNode* current = root->stocks;
    while(current != NULL)
    {
        printf("%s ", current->symbol);
        current = current->next;
    }
    printf("\n");

    afis(root->left);
    afis(root->right);
}

void findMirroredStock(TreeNode** root, int day, int current, struct tabel t[], int n, int myIndex, int* switchAfisare, FILE* outputFILE)
{
    if(*root == NULL)
    {
        return;
    }
    
    if(current == day)
    {
        StockNode* iter = (*root)->stocks;
        while(iter != NULL)
        {
            int iterIndex = -1;
            for(int i = 0; i < n; i++)
            {
                if(strcmp(iter->symbol, t[i].stockName) == 0)
                {
                    iterIndex = i;
                    break;
                }
            }
            
            if (myIndex < iterIndex && strcmp(t[myIndex].stockName, iter->symbol)) 
            {
                if(*switchAfisare == 1)
                {
                    fprintf(outputFILE, "\n%s-%s", t[myIndex].stockName, iter->symbol);
                }
                else if(*switchAfisare == 0)
                {
                    fprintf(outputFILE, "%s-%s", t[myIndex].stockName, iter->symbol);
                    *switchAfisare = 1;
                }
            }

            iter = iter->next;
        }
        return;
    }
    if(t[myIndex].priceHistory[current] <= t[myIndex].priceHistory[current + 1])
    {
        findMirroredStock(&(*root)->left, day, current + 1, t, n, myIndex, switchAfisare, outputFILE);
    }
    else
    {
        findMirroredStock(&(*root)->right, day, current + 1, t, n, myIndex, switchAfisare, outputFILE);
    }
}

void freeTree(TreeNode** root)
{
    if(*root == NULL) return;

    freeTree(&(*root)->left);
    freeTree(&(*root)->right); 

    StockNode* currentStock = (*root)->stocks;
    while(currentStock != NULL)
    {
        StockNode* temp = currentStock;
        currentStock = currentStock->next;
        free(temp->symbol);
        free(temp);
    }
    free(*root);
    *root = NULL;
}