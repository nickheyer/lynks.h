#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <strings.h>

#include "lynks.h"


lynk *lynkall(int ival, char sval[], char cval, bool bval)
{
    lynk *tmp = malloc(sizeof(lynk));
    tmp->intval = ival;
    strcpy(tmp->strval, sval);
    tmp->charval = cval;
    tmp->boolval = bval;
    tmp->size = 1;
    tmp->next = NULL;
    return tmp;
}

lynk *lynkint(int ival)
{
    lynk *tmp = malloc(sizeof(lynk));
    tmp->intval = ival;
    tmp->size = 1;
    tmp->next = NULL;
    return tmp;
}

lynk *lynkstr(char sval[])
{
    lynk *tmp = malloc(sizeof(lynk));
    strcpy(tmp->strval, sval);
    tmp->size = 1;
    tmp->next = NULL;
    return tmp;
}

lynk *lynkchar(char cval)
{
    lynk *tmp = malloc(sizeof(lynk));
    tmp->charval = cval;
    tmp->size = 1;
    tmp->next = NULL;
    return tmp;
}

lynk *lynkbool(bool bval)
{
    lynk *tmp = malloc(sizeof(lynk));
    tmp->boolval = bval;
    tmp->size = 1;
    tmp->next = NULL;
    return tmp;
}

lynk *lynkempty(void)
{
    lynk *tmp = malloc(sizeof(lynk));
    tmp->size = 1;
    tmp->next = NULL;
    return tmp;
}

int lynkcount(lynk *start)
{
    int count = 0;
    counter(start, &count);
    return count;
}

void counter(lynk *node, int *c)
{
    (*c)++;
    if (node->next != NULL)
    {
        counter(node->next, c);
    }
}

int lynksize(lynk *start)
{
    return start->size;
}

lynk *lynkgoto(lynk *start, int index)
{
    if (index > lynksize(start) - 1)
    {
        return NULL;
    }
    int count = 0;
    return traverse(start, &count, index);
}

lynk *traverse(lynk *node, int *c, int index)
{
    if ((*c) == index)
    {
        return node;
    }
    else if (node->next != NULL)
    {
        (*c)++;
        return traverse(node->next, c, index);
    }
    else
    {
        return NULL;
    }
}

void lynkinsert(lynk **start, int index, lynk *l)
{

    int length = lynksize(*start);
    if (index == 0)
    {
        l->next = *start; //Inserted lynk's next is set to start
        lynk *tmp = *start; //Start is saved as tmp

        l->size = ++tmp->size;
        tmp->size = 1;
        *start = l;
        return;
    }
    else if (index > 0 && index <= length)
    {
        lynk *tmp = lynkgoto(*start, index - 1);
        lynk *tmp_2 = *start;
        if (index == length)
        {
            l->next = NULL;
        }
        else
        {
            l->next = lynkgoto(*start, index);
        }
        tmp->next = l;
        tmp_2->size++;
    }
    else
    {
        printf("Index not within range: 0 - %i\n", length - 1);
    }
}

void lynkback(lynk **start, lynk *l)
{
    lynkinsert(start, lynksize(*start), l);
}

void lynkfront(lynk **start, lynk *l)
{
    lynkinsert(start, 0, l);
}

void lynkprint(lynk *start, char arg)
{
    int length = lynksize(start);


    if (arg == 'i')
    {
        for (int x = 0; x < length; x++)
        {
            printf("Int value at index %i: %i\n", x, lynkgoto(start, x)->intval);
        }
    }
    else if (arg == 's')
    {
        for (int x = 0; x < length; x++)
        {
            printf("String value at index %i: %s\n", x, lynkgoto(start, x)->strval);
        }
    }
    else if (arg == 'c')
    {
        for (int x = 0; x < length; x++)
        {
            printf("Char value at index %i: %c\n", x, lynkgoto(start, x)->charval);
        }
    }
    else if (arg == 'b')
    {
        for (int x = 0; x < length; x++)
        {
            if (lynkgoto(start, x)->boolval)
            {
                printf("Boolean value at index %i: true\n", x);
            }
            else
            {
                printf("Boolean value at index %i: false\n", x);
            }
        }
    }
}

//Creates lynk list with empty lynks, to the size specified. Returns first lynk in that list.
lynk *lynkarr(int size)
{
    lynk *tmp = lynkempty();
    for (int x = 1; x < size; x++)
    {
        lynkfront(&tmp, lynkempty());
    }
    return tmp;
}

void lynkpop(lynk **start, int index)
{
    int length = lynksize(*start);

    if (index >= length || index < 0 || length == 1)
    {
        printf("Lynk out of range.");
        return;
    }

    else if (index == 0)
    {
        lynk *s = *start;
        lynk *tmp = s->next;
        lynk *tmp_2 = *start;
        tmp->size = tmp_2->size--;
        free(*start);
        *start = tmp;
    }

    else if (index == length - 1)
    {
        lynk *tmp = lynkgoto(*start, index);
        lynk *tmp_2 = *start;
        lynkgoto(*start, index - 1)->next = NULL;
        free(tmp);
        tmp_2->size--;
    }

    else
    {
        lynk *tmp = lynkgoto(*start, index);
        lynk *tmp_2 = lynkgoto(*start, index - 1);
        lynk *tmp_3 = tmp->next;
        lynk *tmp_4 = *start;
        free(tmp);
        tmp_2->next = tmp_3;
        tmp_4->size--;
    }
}

void lynkpopfront(lynk **start)
{
    lynkpop(start, 0);
}

void lynkpopback(lynk **start)
{
    lynkpop(start, lynksize(*start) - 1);
}

void lynkunload(lynk *n)
{
    if (n->next != NULL) //If there is another node next in the linked list
    {
        lynkunload(n->next, count);
    }
    free(n);
}
