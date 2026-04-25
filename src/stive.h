typedef double Data;
struct stackElem
{
    Data pretPiata;
    struct stackElem *next;
};
typedef struct stackElem stackNode;

int isStackEmpty(const stackNode* top);
void push(stackNode** top, Data v);
Data pop(stackNode** top);
Data top(const stackNode* top);
void deleteStack(stackNode** top);