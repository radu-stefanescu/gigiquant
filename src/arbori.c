#include "arbori.h"
#include <stdlib.h>
#include <stdio.h>

void addAtEnd(StockNode **head, char* numeStock)
{
    StockNode *aux = *head;
    StockNode *newNode = (StockNode*)malloc(sizeof(StockNode));
    newNode->symbol = numeStock;

    if (*head == NULL) 
    {
        newNode->symbol = NULL;
        newNode->next = NULL;
        *head = newNode;
        return;
    }
    else 
    {
        while (aux->next != NULL) 
            aux = aux->next;

        aux->next = newNode;
        newNode->next = NULL; 
        return;
    }
}

void addTreeNode(TreeNode **root, char* numeStock, float pretCurent)
{
    if(*root == NULL)   return;

}

TreeNode* createTreeNode(char *symbol, float pretCurent)
{
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) 
    {
        printf("Eroare la alocarea memoriei!\n");
        exit(1);
    }
    newNode->stocks = createStockNode(symbol, pretCurent);
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

StockNode* createStockNode(char *symbol, float pretCurent)
{
    StockNode *newNode = (StockNode*)malloc(sizeof(StockNode));
    if (newNode == NULL) 
    {
        printf("Eroare la alocarea memoriei!\n");
        exit(1);
    }
    newNode->symbol = symbol;
    newNode->pretCurent = pretCurent;
    return newNode;
}

void insert(TreeNode* root, char *symbol, float pretCurent, float pretReferinta)
{
    if(root == NULL) return createTreeNode(symbol, pretCurent);

    if(pretCurent < pretReferinta)
    {
        insert(root->left, symbol, pretCurent, pretReferinta);
    }
    else if(pretCurent > pretReferinta)
    {
        insert(root->right, symbol, pretCurent, pretReferinta);
    }
    else if(pretCurent == pretReferinta)
    {
        insert(root->left, symbol, pretCurent, pretReferinta);
        insert(root->right, symbol, pretCurent, pretReferinta);
    }
}

void f(TreeNode** root, int day)
{
    if(day == 0)
    {
        return;
    }
    *root = (TreeNode*)malloc(sizeof(TreeNode));
    (*root)->stocks = (StockNode*)malloc(sizeof(StockNode));
    (*root)->left = NULL;
    (*root)->right = NULL;
    f(&(*root)->left, day - 1);
    f(&(*root)->right, day - 1);
}