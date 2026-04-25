typedef double Data;

struct Elem
{
    Data valoare;
    Data randament;
    struct Elem *next;
};
typedef struct Elem Node;

double addAtEnd(Node **head, Data v);
void trunk(double *x, int nrZecimaleExacte);