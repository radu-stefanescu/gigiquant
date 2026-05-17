/*

Programul primeste un fisier de intrare si unul de iesire si ruleaza
3 tipuri de task-uri in functiee de indexul testului extras din argumente:
- Task 1 (Teste 1-5): Calcul Sharpe Ratio folosind Liste Simplu Inlantuite.
- Task 2 (Teste 6-10): Analiza de tranzactionare folosind Stive si Cozi.
- Task 3 (Teste 11-15): Diversificare portofoliu gasind actiuni "in oglinda" 
folosind Arbori Binari.

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "liste.h"
#include "stive.h"
#include "cozi.h"
#include "arbori.h"
#include "task4.h"

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
    
    //Extragem numarul testului (ex: 12 din data12.in sii data12.ref)
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
    

    // Verificam ca fisierle input si output corespund aceluiasi test
    if(n1 != n2)
    {
        printf("Eroare la comparatie (in si ref diferite)!\n");
        return 1;
    }
    
    //printf("%d %d!\n", n1, n2);
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
        TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
        root->stocks = NULL;
        root->left = NULL;
        root->right = NULL;

        char buffer[10000];
        int day = 0, n = 0;
        tabel t[100];

        while(fgets(buffer, sizeof(buffer), fIn) != NULL) 
        {
            const char *token = strtok(buffer, ",\n\r");
    
            if(token != NULL && token[0] >= 'A' && token[0] <= 'Z') 
            {
                while(token != NULL) {
                    t[n].stockName = strdup(token);
                    n++;
                    token = strtok(NULL, ",\n\r");
                }
            } 
            else 
            {
                int k = 0;
                while(token != NULL && k < n) {
                    t[k].priceHistory[day] = atof(token);
                    k++;
                    token = strtok(NULL, ",\n\r");
                }
                day++;
            }
        }


        createEmptyTree(&(root->left), day - 1);
        createEmptyTree(&(root->right), day - 1);
        for(i = 0; i < n; i++)
        {
            insertStock(&root, t[i].stockName, t[i].priceHistory, day - 1, 0);
        }

        //afis(root);

        //printf("%p", &root);
        int switchAfisare = 0;
        for(i = 0; i < n; i++)
        {
            findMirroredStock(&root, day - 1, 0, t, n, i, &switchAfisare, fOut);
        }

        freeTree(&root);

        for(i = 0; i < n; i++)
        {
            free(t[i].stockName); // Eliberarea memorie alocate de strdup pt nume
        }
    }
    else if(n1 >= 16 && n1 <= 20)
    {
        int N, K, i, j, k;
        float d, P_start, P_target;

        fscanf(fIn, "%d%f%d%f%f", &N, &d, &K, &P_start, &P_target);
        
        float observatii[100], vMin = 9999.0f, vMax = -1.0f, pretMin = 0.0f, pretMax = 0.0f;
        for(i = 0; i < N; i++)
        {
            fscanf(fIn, "%f", &observatii[i]);
            if(observatii[i] < vMin)
            {
                vMin = observatii[i];
            }
            if(observatii[i] > vMax)
            {
                vMax = observatii[i];
            }
        }

        while(pretMin < vMin)
        {
            pretMin += d;
        } 
        pretMin -= d;
        while(pretMax < vMax)
        {
            pretMax += d;
        }
        //fprintf(stdout, "%.1f %.1f", pretMin, pretMax);

        fractie a[100][100];
        for(i = 0; i < 100; i++)
        {
            for(j = 0; j < 100; j++)
            {
                a[i][j].numarator = 0;
                a[i][j].numitor = 1;
            }
        }
        int nrStari = -1;
        for(i = 0; i < N - 1; i++)
        {
            j = (int)((observatii[i] - pretMin) / d);
            k = (int)((observatii[i + 1] - pretMin) / d);
            
            a[j][k].numarator++;
            a[j][k].numitor = 1;
            if(j > nrStari)
            {
                nrStari = j;
            }
            if(k > nrStari)
            {
                nrStari = k;
            }
        }
        nrStari++;

        for(i = 0; i < nrStari; i++)
        {
            int num = numitor(a[i], nrStari);
            if(num > 0)
            {
                for(j = 0; j < nrStari; j++)
                {
                    a[i][j].numitor = num;
                }
            }
        }

        int target = (int)((P_target - pretMin) / d);
        fractie probStare[100];

        int start = (int)((P_start - pretMin) / d);
        for(i = 0; i < 100; i++)
        {
            probStare[i].numarator = 0;
            probStare[i].numitor = 1;
        }
        probStare[start].numarator = 1;
        probStare[start].numitor = 1;

        fprintf(stdout, "0\n");
        f(a, N, probStare, nrStari, K, 2, target);

    }

    fclose(fIn);
    fclose(fOut);

    return 0;
}