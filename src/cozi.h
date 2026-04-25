typedef double Data;
struct queueElem
{
    int zi;
    Data diferentaAbs;
    char *numePiata;
    struct queueElem *next;
};
typedef struct queueElem queueNode;

struct Q
{
    queueNode *front, *rear;
};
typedef struct Q Queue;

Queue* createQueue();
int isQueueEmpty(const Queue* q);
void enQueue(Queue* q, int zi, Data diferentaAbs,char *numePiata);
void deQueue(Queue* q);
void deleteQueue(Queue* q);