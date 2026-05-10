#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "liste.h"
#include "stive.h"
#include "cozi.h"
#include "arbori.h"

#define PRECIZIE 3

int main(int argc, const char *argv[])
{

    if(argc != 3)
    {
        fprintf(stdout, "Eroare! Numar gresit de fisiere!\n");
        return 1;
    }
    
    int n1 = 0, n2 = 0, i;
    char s[10];
    
    for(i = 1; i <= 2; i++)
    {
        int j = 0, k = -5;

        while(argv[i][j] != '\0')
        {
            if(argv[i][j] == '/')
            {
                k = j;
            }
            j++;
        }
        
        strcpy(s, argv[i] + k + 5);
        
        if(s[1] >= '0' && s[1] <= '9')
        {   
            s[2] = '\0';
        }
        else
        {
            s[1] = '\0';
        }

        if(i == 1)
        {
            n1 = atoi(s);
        }
        else
        {
            n2 = atoi(s); 
        }
    }
    
    if(n1 != n2)
    {
        printf("Eroare la comparatie (in si ref diferite)!\n");
        return 1;
    }
    
    printf("%d %d!\n", n1, n2);
    FILE* fIn = fopen(argv[1], "rt");
    if(fIn == NULL)
    {
        printf("Eroare! Nu s a putut deshide fisierul Input!\n");
        return 1;
    }
    
    FILE* fOut = fopen(argv[2], "wt");
    if(fOut == NULL)
    {
        printf("Eroare! Nu s a putut deshide fisierul Output!\n");
        return 1;
    }

    if(n1 >= 1 && n1 <= 5)
    {
        printf("Hello1\n");
        Node *head = NULL;
        int nrObs = 0;
        double x, sharpeRatio = 0.0f, sum = 0.0f, randamentMediu = 0.0f, volatilitate = 0.0f;
        
        if (fscanf(fIn, "%d", &nrObs) == 1) 
        {
            for(i = 0 ; i < nrObs; i++)
            {
                fscanf(fIn, "%lf", &x);
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
        
        fprintf(fOut, "%.3lf\n", randamentMediu);
        fprintf(fOut, "%.3lf\n", volatilitate);
        fprintf(fOut, "%.3lf\n", sharpeRatio);
        
        while(head != NULL)
        {
            iter = head;
            head = head->next;
            free(iter);
        }
    }
    else if(n1 >= 6 && n1 <= 10)
    {
        printf("Hello2222\n");
        
        char numePiata[3][30], buffer[30];
        stackNode* stackTop[3] = {NULL};
        int nrPiata = -1;

        while(fgets(buffer, sizeof(buffer), fIn) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            
            if(buffer[0] == '-' || (buffer[0] >= '0' && buffer[0] <= '9'))
            {
                if(nrPiata >= 0 && nrPiata <= 2)
                {
                    double val = atof(buffer);
                    push(&stackTop[nrPiata], val);
                }
            }
            else
            {   
                nrPiata++;
                strcpy(numePiata[nrPiata], buffer);
                //fprintf(stdout, "%s\n\n", numePiata[nrPiata]);
            }
        }

        Queue* q = createQueue();
        int zi = 0;
        
        while(!isStackEmpty(stackTop[0]) && !isStackEmpty(stackTop[1]) && !isStackEmpty(stackTop[2]))
        {
            zi++;
            if(stackTop[0]->pretPiata == stackTop[1]->pretPiata && stackTop[0]->pretPiata == stackTop[2]->pretPiata)
            {
            }
            else if(stackTop[0]->pretPiata != stackTop[1]->pretPiata && stackTop[0]->pretPiata != stackTop[2]->pretPiata && stackTop[1]->pretPiata != stackTop[2]->pretPiata)
            {
            }
            else
            {
                if(stackTop[0]->pretPiata == stackTop[1]->pretPiata)
                {
                    enQueue(q, zi, fabs(stackTop[0]->pretPiata - stackTop[2]->pretPiata), numePiata[2]);
                }
                else if(stackTop[0]->pretPiata == stackTop[2]->pretPiata)
                {
                    enQueue(q, zi, fabs(stackTop[0]->pretPiata - stackTop[1]->pretPiata), numePiata[1]);
                }
                else if(stackTop[1]->pretPiata == stackTop[2]->pretPiata)
                {
                    enQueue(q, zi, fabs(stackTop[1]->pretPiata - stackTop[0]->pretPiata), numePiata[0]);
                }
            }
            
            pop(&stackTop[0]);
            pop(&stackTop[1]);
            pop(&stackTop[2]);
        }

        while(!isQueueEmpty(q))
        {
            fprintf(fOut, "ziua %d - %.2lf - %s\n", q->front->zi, q->front->diferentaAbs, q->front->numePiata);
            deQueue(q);
        }

        deleteQueue(q);
        deleteStack(&stackTop[0]);
        deleteStack(&stackTop[1]);
        deleteStack(&stackTop[2]); 
    }
    else if(n1 >= 11 && n1 <= 15)
    {
        printf("Hello333\n");
        
        TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
        root->stocks = (StockNode*)malloc(sizeof(StockNode));
        root->left = NULL;
        root->right = NULL;
        root->depth = 0;

        char buffer[10000];
        while(fgets(buffer, sizeof(buffer), fIn) != NULL)
        {
            char *token;
            tabel t[100];
            int n = 0; 
            //char s[2] = {',', '\n'};  //nu merge sar si peste "1"?!
            token = strtok(buffer, ",\n");
            TreeNode *current = root->stocks;
            while(token != NULL && token[0] >= 'A' && token[0] <= 'Z')
            {
                //printf("%s ", token);
                addAtEndStock(&root->stocks, token);
                t[n++].stockName = token;
                token = strtok(NULL, ",\n");
            }

            

            int day = 1, k = 0;
            while(token != NULL)
            {
                if(token == '\n')
                {
                    day++;
                    k = 0;
                    token = strtok(NULL, ",");
                }
                t[k++].priceHistory[day] = atof(token);
                token = strtok(NULL, ",");
            }
            f(&(root->left), day - 1);
            f(&(root->right), day - 1);
            //printf("\n");
        }
    }
    

    fclose(fIn);
    fclose(fOut);

    return 0;
}