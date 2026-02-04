#include <stdbool.h>

typedef struct node
{
    long long num;
    struct node *next;
}
node;

node *factor(long long num);
void freelist(node *list, bool print_contents, const char *sep);
long long get_one_factor(long long num);
