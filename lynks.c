#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <strings.h>

#include "lynks.h"

lynk *lynkall(int ival, char sval[], char cval, bool bval)
{ //Creating a head lynk, while instantiating it's int, string, char, and bool values
    lynk *tmp = malloc(sizeof(lynk)); //Allocating memory for a new lynk
    tmp->intval = ival; //Changing the lynks intval to the passed in integer
    strcpy(tmp->strval, sval); //Changing the lynks strval to the passed in string
    tmp->charval = cval; //Changing the lynks charval to the passed in character
    tmp->boolval = bval; //Changing the lynks boolval to the passed in boolean
    tmp->size = 1; //Defaulting the size of the lynks lynk list to 1
    tmp->next = NULL; //Defaulting the next lynk to NULL
    tmp->prev = NULL; //Defaulting the previous lynk to NULL
    tmp->end = tmp; //Defaulting the end lynk to be self-referential
    return tmp; //Returning the instantiated lynk
}

lynk *lynkint(int ival)
{ //Creating a head lynk, while instantiating it's int value
    lynk *tmp = malloc(sizeof(lynk)); //Allocating memory for a new lynk
    tmp->intval = ival; //Changing the lynks intval to the passed in integer
    tmp->size = 1; //Defaulting the size of the lynks lynk list to 1
    tmp->next = NULL; //Defaulting the next lynk to NULL
    tmp->prev = NULL; //Defaulting the previous lynk to NULL
    tmp->end = tmp; //Defaulting the end lynk to be self-referential
    return tmp; //Returning the instantiated lynk
}

lynk *lynkstr(char sval[])
{ //Creating a head lynk, while instantiating it's string value
    lynk *tmp = malloc(sizeof(lynk)); //Allocating memory for a new lynk
    strcpy(tmp->strval, sval); //Changing the lynks strval to the passed in string
    tmp->size = 1; //Defaulting the size of the lynks lynk list to 1
    tmp->next = NULL; //Defaulting the next lynk to NULL
    tmp->prev = NULL; //Defaulting the previous lynk to NULL
    tmp->end = tmp; //Defaulting the end lynk to be self-referential
    return tmp; //Returning the instantiated lynk
}

lynk *lynkchar(char cval)
{ //Creating a head lynk, while instantiating it's char value
    lynk *tmp = malloc(sizeof(lynk)); //Allocating memory for a new lynk
    tmp->charval = cval; //Changing the lynks charval to the passed in character
    tmp->size = 1; //Defaulting the size of the lynks lynk list to 1
    tmp->next = NULL; //Defaulting the next lynk to NULL
    tmp->prev = NULL; //Defaulting the previous lynk to NULL
    tmp->end = tmp; //Defaulting the end lynk to be self-referential
    return tmp; //Returning the instantiated lynk
}

lynk *lynkbool(bool bval)
{ //Creating a head lynk, while instantiating it's bool value
    lynk *tmp = malloc(sizeof(lynk)); //Allocating memory for a new lynk
    tmp->boolval = bval; //Changing the lynks boolval to the passed in boolean
    tmp->size = 1; //Defaulting the size of the lynks lynk list to 1
    tmp->next = NULL; //Defaulting the next lynk to NULL
    tmp->prev = NULL; //Defaulting the previous lynk to NULL
    tmp->end = tmp; //Defaulting the end lynk to be self-referential
    return tmp; //Returning the instantiated lynk
}

lynk *lynkempty(void)
{ //Creating a head lynk, nothing is instantiated
    lynk *tmp = malloc(sizeof(lynk)); //Allocating memory for a new lynk
    tmp->size = 1; //Defaulting the size of the lynks lynk list to 1
    tmp->next = NULL; //Defaulting the next lynk to NULL
    tmp->prev = NULL; //Defaulting the previous lynk to NULL
    tmp->end = tmp; //Defaulting the end lynk to be self-referential
    return tmp; //Returning the instantiated lynk
}

int lynkcount(lynk *start)
{ //Manually count each lynk attached to a head lynk, slow and used for debugging
    int count = 0; //Instantiating count int
    while (start) //While lynk is not NULL, loop through each attached lynk
    {
        start = start->next; //Save next lynk as current lynk
        count++; //Increment count once
    }
    return count; //Return completed count
}

int lynksize(lynk *start)
{ //Returns size integer store at head lynk, should always be used over lynkcount when available
    return start->size;
}


lynk *lynkgoto(lynk *start, int index)
{ //Traverses through the passed in lynked list until the passed in index is reached, returns lynk at index
    if (index > lynksize(start) - 1 || index < 0)
    { //If requested index is larger than lynk list or smaller than zero, return NULL
        return NULL;
    }
    int count = 0; //Instantiating count int
    lynk *x = start; //Saving passed in lynk as x
    while (start) //While lynk is not NULL, loop through each attached lynk
    {
        x = start; //Reassigning x as current start iteration
        if (count++ == index) //If current count is equal to the passed in index
        {
            break; //Break out of loop
        }
        start = start->next; //Moving to the next lynk
    }
    return x; //Returning lynk at index

}

void lynkinsert(lynk **start, int index, lynk *l)
{ //Inserts provided lynk at specified index, of provided head lynk's attached lynks
    
    if (*start == NULL) //If there is no head lynk, simply assigns the lynk as the head
    {
        *start = l; //Points the NULL pointer to the inserted lynk
        return;
    }
    
    int length = lynksize(*start);
    if (index == 0) //Insertion is at the first element, or lynkfront() was called
    {
        lynk *tmp = *start; //Beginning of lynk list
        l->next = *start; //Inserted lynk's next is set to beginning or head lynk
        l->size = tmp->size + 1; //Inserted lynk's size is set to that of the previous head lynk, plus one
        tmp->size = 1; //Setting size of previous head lynk to default, as it's no longer head lynk
        tmp->prev = l; //Setting prev of previous head lynk to newly inserted lynk
        l->end = tmp->end; //Setting new end of lyst to the end that was stored at previous head lynk
        l->prev = NULL; //Since nothing before newly inserted lynk, set prev to NULL
        *start = l; //Changing pointer to now point to newly inserted lynk
        return;
    }
    else if (index == length) //Inserting at last element, or lynkback() was called
    {
        lynk *tmp_2 = *start; //Beginning of lynk list
        lynk *tmp = tmp_2->end; //End of lynk list - Pre insertion
        l->next = NULL; //Setting inserted lynk's next to null, since its at end of list
        tmp->next = l; //Setting previous end lynk's next to inserted lynk
        l->prev = tmp; //Setting inserted lynk prev to previous end lynk
        tmp_2->size += 1; //Incrementing total size stored at head lynk
        tmp_2->end = l; //Changing end of lynk list to the newly inserted lynk

    }
    else if (index > 0 && index < length) //Inserting between index 0 and end of list, pushing elements to right
    {
        lynk *tmp = *start; //Beginning of lynk list
        lynk *tmp_2 = lynkgoto(*start, index - 1); //Lynk we will be inserting our lynk after
        lynk *tmp_3 = tmp_2->next; //Lynk we will be inserting our lynk before, pushing to right
        tmp->size = tmp->size + 1; //Incrementing the size stored at the head by +1
        tmp_2->next = l; //Setting previous lynk's next lynk to inserted lynk
        l->prev = tmp_2; //Setting inserted lynk's prev lynk to previous lynk
        l->next = tmp_3; //Setting inserted lynk's next lynk to following lynk, pushing to right
        tmp_3->prev = l; //Setting pushed lynk's prev to inserted lynk
    }
    else //If index is not within the above ranges
    {
        printf("Index not within range: 0 - %i\n", length - 1);
    }
}

void lynkback(lynk **start, lynk *l)
{ //Calls lynkinsert() with the passed in head lynk, adding specified lynk to end of lynk list
    lynkinsert(start, lynksize(*start), l);
}

void lynkfront(lynk **start, lynk *l)
{ //Calls lynkinsert() with the passed in head lynk, adding specified lynk to beginning of lynk list
    lynkinsert(start, 0, l);
}

void lynkprint(lynk *start, char arg)
{ //Iterates through every lynk attached to provided lynk, prints the value corresponding to char arg
    int count = 0;
    while (start)
    {
        switch(arg)
        {
            case 'i': // 'i' prints the integer value of the lynks
            printf("Int value at index %i: %i\n", count++, start->intval);
            break;

            case 's': // 's' prints the string value of the lynks
            printf("String value at index %i: %s\n", count++, start->strval);
            break;

            case 'c': // 'c' prints the char value of the lynks
            printf("Char value at index %i: %c\n", count++, start->charval);
            break;

            case 'b': // 'b' prints the boolean value of the lynks
                if (start->boolval)
                {
                    printf("Boolean value at index %i: true\n", count++);
                }
                else
                {
                    printf("Boolean value at index %i: false\n", count++);
                }
        }
        start = start->next; //Sets passed in lynk to the next lynk, restarts loop
    }
}

lynk *lynkarr(int size)
{ //Creates lynk list with empty lynks, to the size specified. Returns first lynk in that list.
    lynk *tmp = lynkempty(); //Creating head/first lynk
    for (int x = 1; x < size; x++)
    {
        lynkfront(&tmp, lynkempty()); //Adding lynks to the front of head lynk
    }   //Changes head lynk on every iteration | Newly added lynk becomes head lynk
    return tmp; //Return head lynk
}

void lynkpop(lynk **start, int index)
{ //Removes lynk at specified index in lynks attached to head lynk
    int length = lynksize(*start);


    if (index >= length || index < 0 || length == 1)
    { //If attempting to remove lynk outside of range, or if list only has one lynk
        printf("Lynk out of range.\n");
        return;
    }

    else if (index == 0) //If lynk being removed is the head lynk, or lynkpopfront() was called
    {
        lynk *s = *start; //Head of lynk list, lynk to be removed
        lynk *tmp = s->next; //Second lynk in lynk list, lynk to be replacing head
        tmp->size = s->size - 1; //Setting size at second lynk to be size at head lynk being removed - 1.
        tmp->prev = NULL; // Setting new head lynk (second lynk) prev to NULL
        tmp->end = s->end; //Setting new head lynk (second lynk) end to previous head lynks end lynk.
        free(*start); //Freeing the previous head lynk, releasing it's memory to be allocated elsewhere
        *start = tmp; //Setting the pointer for the passed in lynk to now be pointing to the new head lynk
    }

    else if (index == length - 1) //If lynk being removed is at the end of lynk list, or lynkpopback() was called
    {
        lynk *tmp = *start; //Head of lynk list
        lynk *tmp_2 = tmp->end; //Last lynk of lynk list, lynk being removed
        lynk *tmp_3 = tmp_2->prev; //Second to last lynk in lynk list
        tmp->end = tmp_3; //Setting end lynk (stored at head) to be second to last lynk
        tmp_3->next = NULL; //Setting new end lynk's next to be NULL, as it's now last in lynk list
        free(tmp_2); //Freeing the previous end lynk
        tmp->size = tmp->size - 1; //Decrementing the size down by 1.
    }

    else //Index to be removed is between 0 and size - 1
    {
        lynk *tmp = *start; //Head of lynk list
        lynk *tmp_2 = lynkgoto(*start, index); //Lynk to be removed
        lynk *tmp_3 = tmp_2->prev; //Lynk prev to lynk being removed
        lynk *tmp_4 = tmp_2->next; //Lynk following lynk being removed
        free(tmp_2); //Freeing lynk to be removed
        tmp_3->next = tmp_4; //Changing previous lynk's next to following lynk
        tmp_4->prev = tmp_3; //Changing following lynk's prev to previous lynk
        tmp->size = tmp->size - 1; //Decrementing the size down by 1
    }
}

void lynkpopfront(lynk **start) //Calling lynkpop to remove first lynk
{
    lynkpop(start, 0);
}

void lynkpopback(lynk **start) //Calling lynkpop to remove last lynk
{
    lynkpop(start, lynksize(*start) - 1);
}

void lynkunload(lynk *start) //Unloads all lynks, provided head lynk
{
    while (start) //Null pointer equivalent to false, loops till NULL is reached
    {
        lynk *x = start; //Sets x as head lynk
        start = start->next; //Changes start lynk to next lynk
        free(x); //free's previous lynk
    }
}
