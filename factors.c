#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "factors.h"

node *factor(long num)
{
    node *result = NULL;
    node *thisnode, *lastnode;
    long factor;

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
            printf("%li", list->num);
        }
        next = list->next;
        free(list);
        list = next;
    }
}

long get_one_factor(long num)
{
    long double max = sqrt(num);

    for (long y = 2; y <= (long) max; y ++)
    {
        if (!(num % y))
        {
            return y;
        }
    }
    return num;
}

long gcf(long x, long y)
{
    long q, r;

    while (true)
    {
        q = x / y;
        r = x - y * q;

        if (r == 0)
        {
            return y;
        }
        x = y;
        y = r;
    }
}

long sigma(long x)
{
    if (x == 0 || x == 1)
    {
        return x;
    }

    long
        result = 0,
        prev_result = 0,
        i = 1,
        sqrt_floor = (long) floor(sqrt(x));
    long j;
    double q;

    while (1)
    {
        q = x / (double) i;
        j = (long) q;

        if (q == j)
        {
            result += i + (i == j ? 0 : j);

            if (result < prev_result)
            {
                return -1;
            }

            prev_result = result;
        }

        if (i >= sqrt_floor)
        {
            return result;
        }
        i++;
    }
}
