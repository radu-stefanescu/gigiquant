#include <stdio.h>

#define MAX_SYM 5

struct StockNode
{
    char *symbol;
    struct StockNode *next;
};
typedef struct StockNode StockNode;

struct TreeNode 
{
    StockNode *stocks;
    struct TreeNode *left;
    struct TreeNode *right;
};
typedef struct TreeNode TreeNode;

struct tabel
{
    char *stockName;
    float priceHistory[50];
};
typedef struct tabel tabel;

void addAtEndStock(StockNode **head, const char* numeStock);
void createEmptyTree(TreeNode** root, int day);
void insertStock(TreeNode** root, char* stockName, float v[], int day, int current);
void afis(TreeNode* root);
void findMirroredStock(TreeNode** root, int day, int current, struct tabel t[], int n, int myIndex, int* switchAfisare, FILE* outputFILE);
void freeTree(TreeNode** root);