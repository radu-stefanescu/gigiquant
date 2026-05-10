#define MAX_SYM 5

struct StockNode
{
    char *symbol;
    float pretCurent;
    struct StockNode *next;
};
typedef struct StockNode StockNode;

struct TreeNode 
{
    StockNode *stocks;
    struct TreeNode *left;
    struct TreeNode *right;
    int depth;
};
typedef struct TreeNode TreeNode;

struct tabel
{
    char *stockName;
    float currentPrice;
};
typedef struct tabel tabel;

void addAtEndStock(StockNode **head, char* numeStock    );
StockNode* createNode(char *symbol, float pretCurent);
void addTreeNode(TreeNode **root, TreeNode* node);



TreeNode* createTreeNode(char *symbol, float pretCurent);
StockNode* createStockNode(char *symbol, float pretCurent);
void insert(TreeNode* root, char *symbol, float pretCurent, float pretReferinta);
void add2Lists(TreeNode* root, char *symbol, float pretCurent);