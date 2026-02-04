#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "factors.h"

node *factor(long long num)
{
    node *result = NULL;
    node *thisnode, *lastnode;
    long long factor;

    while (true)
    {
        factor = get_one_factor(num);
        num /= factor;
        thisnode = malloc(sizeof(node));

        if (thisnode == NULL)
        {
            if (result != NULL)
            {
                lastnode->next = NULL;
            }
            freelist(result, false, "");
            return NULL;
        }

        thisnode->num = factor;
        thisnode->next = NULL;

        if (result == NULL)
        {
            result = thisnode;
        }
        else
        {
            lastnode->next = thisnode;
        }
        lastnode = thisnode;

        if (num == 1)
        {
            return result;
        }
    }
}

void freelist(node *list, bool print_contents, const char *sep)
{
    bool first = true;
    node *next;

    while (list != NULL)
    {
        if (first)
        {
            first = false;
        }
        else if (print_contents)
        {
            printf("%s", sep);
        }

        if (print_contents)
        {
            printf("%lli", list->num);
        }
        next = list->next;
        free(list);
        list = next;
    }
}

long long get_one_factor(long long num)
{
    long double max = sqrt(num);

    for (long long y = 2; y <= (long long) max; y ++)
    {
        if (!(num % y))
        {
            return y;
        }
    }
    return num;
}

