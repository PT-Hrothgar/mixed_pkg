#include <stdbool.h>

typedef struct node
{
    long num;
    struct node *next;
}
node;

node *factor(long num);
void freelist(node *list, bool print_contents, const char *sep);
long get_one_factor(long num);
long gcf(long x, long y);
long sigma(long x);
