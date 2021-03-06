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
    tmp->last = NULL; //Defaulting the last inserted node to NULL, reserved for head node
    tmp->last_r = NULL; //Defaulting the last removed node to NULL, reserved for head node
    tmp->last_i = 0; //Defaulting last known insert index to 0, valgrind doesn't like it unitialized
    tmp->last_ri= 0; //Defaulting last known removed index to 0, valgrind doesn't like it unitialized
    return tmp; //Returning the instantiated lynk
}

lynk *lynkint(int ival)
{ //Creating a head lynk, while instantiating it's int value
    return lynkall(ival, "", '\0', false);
}

lynk *lynkstr(char sval[])
{ //Creating a head lynk, while instantiating it's string value
    return lynkall(0, sval, '\0', false);
}

lynk *lynkchar(char cval)
{ //Creating a head lynk, while instantiating it's char value
    return lynkall(0, "", cval, false);
}

lynk *lynkbool(bool bval)
{ //Creating a head lynk, while instantiating it's bool value
    return lynkall(0, "", '\0', bval);
}

lynk *lynkempty(void)
{ //Creating a head lynk, nothing is instantiated
    return lynkall(0, "", '\0', false);
}

int lynkcount(lynk *start) //FOR DEBUG ONLY
{ //Manually count each lynk attached to a head lynk, slow and used for debugging.
    if (start == NULL) //If pointer is NULL, returns a size of 0
    {
        return 0;
    }
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
    if (start == NULL) //If pointer is NULL, returns a size of 0
    {
        return 0;
    }
    return start->size;
}

lynk *lynkgoto(lynk *start, int index)
{ //Traverses through the passed in lynked list until the passed in index is reached, returns lynk at index
    int len = lynksize(start);
    if (index > len - 1 || index < 0)
    {
        printf("Index out of range, return NULL pointer\n");
        return NULL;
    }
    else if (start == NULL)
    { //If requested index is larger than lynk list or smaller than zero, return NULL
        return NULL;
    }
    else if (index <= (len/2)) //If requested index is in the left half of lynk list
    {
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
    else //If requested index is in the right half
    {
        int count = 0; //Instantiating count int, amount of spaces needed to move to the left from the last index
        start = start->end;
        lynk *x = start; //Saving passed in lynk as x
        while (start) //While lynk is not NULL, loop through each attached lynk
        {
            x = start; //Reassigning x as current start iteration
            if (count++ == len - index - 1) //If current count is equal to the amount of spaces needed to move to the left
            {
                break; //Break out of loop
            }
            start = start->prev; //Moving to the next lynk
        }
        return x; //Returning lynk at index
    }
}

void lynkinsert(lynk **start, int index, lynk *l)
{ //Inserts provided lynk at specified index, of provided head lynk's attached lynks
    int length = lynksize(*start);
    if (*start == NULL) //If there is no head lynk, simply assigns the lynk as the head
    {
        *start = l; //Points the NULL pointer to the inserted lynk
        return;
    }
    else if (index == 0) //Insertion is at the first element, or lynkfront() was called
    {
        lynk *tmp = *start; //Beginning of lynk list
        l->next = *start; //Inserted lynk's next is set to beginning or head lynk
        l->size = tmp->size + 1; //Inserted lynk's size is set to that of the previous head lynk, plus one
        tmp->size = 1; //Setting size of previous head lynk to default, as it's no longer head lynk
        tmp->prev = l; //Setting prev of previous head lynk to newly inserted lynk
        l->end = tmp->end; //Setting new end of list to the end that was stored at previous head lynk
        l->prev = NULL; //Since nothing before newly inserted lynk, set prev to NULL
        l->last = l; //Setting last known insert to self
        l->last_i = index; //Setting last know insert index to 0
        l->last_r = tmp->last_r; //Setting last know removed lynk to previously known, at head lynk
        l->last_ri = tmp->last_ri; //Setting last know removed lynk index to previously known, at head lynk
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
        tmp_2->last = l; //Setting head lynk's last known insert to inserted lynk
        tmp_2->last_i = index; //Setting last inserted index as the last index

    }
    else if (index > 0 && index < length) //Inserting between index 0 and end of list, pushing elements to right
    {
        lynk *tmp = *start; //Beginning of lynk list
        lynk *tmp_2; //Declaring lynk we will be inserting after
        if (tmp->last_i == index - 1)
        { //If the last known inserted lynk was previous to the passed in index, ie: looping +1
            tmp_2 = tmp->last; //Initializing above lynk to the last known inserted lynk
        }
        else if(tmp->last_i == index + 1)
        { //If the last known inserted lynk was following the passed in index. ie: looping -1
            tmp_2 = tmp->last->prev;
        }
        else
        {
            tmp_2 = lynkgoto(*start, index - 1); //Lynk we will be inserting our lynk after
        }
        lynk *tmp_3 = tmp_2->next; //Lynk we will be inserting our lynk before, pushing to right
        tmp->size = tmp->size + 1; //Incrementing the size stored at the head by +1
        tmp_2->next = l; //Setting previous lynk's next lynk to inserted lynk
        l->prev = tmp_2; //Setting inserted lynk's prev lynk to previous lynk
        l->next = tmp_3; //Setting inserted lynk's next lynk to following lynk, pushing to right
        tmp_3->prev = l; //Setting pushed lynk's prev to inserted lynk
        tmp->last = l; //Setting head lynk's last known insert to inserted lynk
        tmp->last_i = index; //Incrementing head lynk's last known inserted index + 1
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
        tmp->last = s->last; //Setting new head lynk's last inserted property to the same as previous head lynk
        tmp->last_i = s->last_i - 1; //Setting new head lynk's last inserted index to the previous's - 1, as the list has moved one to the left
        tmp->last_r = NULL; //Setting last removed lynk to NULL, prev lynk does not exist
        tmp->last_ri = 0; //Setting last removed index to 0;
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
        tmp->last_r = tmp->last_r->prev; //Setting last removed as the lynk next to last removed, to potentially be removed on next iteration
        tmp->last_ri = index; //Setting last removed index to passed in index
        free(tmp_2); //Freeing the previous end lynk
        tmp->size = tmp->size - 1; //Decrementing the size down by 1.
    }

    else //Index to be removed is between 0 and size - 1
    {
        lynk *tmp = *start; //Head of lynk list
        lynk *tmp_2; //Declaring *lynk to be removed
        if (index == tmp->last_ri + 1)
        { //If lynk to be removed is the lynk following the previously removed lynk, ie: looping +1
            tmp_2 = tmp->last_r->next;
        }
        else if (index == tmp->last_ri - 1)
        { //If lynk to be removed is the lynk previous to the previously removed lynk, ie: looping -1
            tmp_2 = tmp->last_r;
        }
        else
        { //Must index to first location for each loop with lynkgoto(), or if lynk tbr isnt last_ri - 1 or + 1
            tmp_2 = lynkgoto(*start, index); //Lynk to be removed
        }
        lynk *tmp_3 = tmp_2->prev; //Lynk prev to lynk being removed
        lynk *tmp_4 = tmp_2->next; //Lynk following lynk being removed
        if (index < tmp->last_i)
        { //If the removed index is below the previously inserted i, adjust overall index
            tmp->last_i -= 1;
        }
        else if (index == tmp->last_i)
        { //If the previously inserted lynk is the lynk to be removed, reset previously inserted data at head to default
            tmp->last = tmp;
            tmp->last_i = 0;
        }
        tmp->last_r = tmp_2->prev; //Setting head lynk's last known removal to the lynk previous to the removed lynk
        tmp->last_ri = index; //Setting head lynk's lkr index to the current index of removal
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

lynk *lynksort(lynk *l, char type, char arg)
{ //Takes lynk*, type argument ('i' for int, 'c' for char, etc.), and order arg ('f' for forward, 'r' for reverse)
    lynk *tmp = NULL;
    switch(type)
    {
        case 'i':
        { //If passed in type is 'i', sort ints
            tmp = int_sorter(l, arg);
            break;
        }
        case 's':
        { //If passed in type is 's', sort strings
           tmp = str_sorter(l, arg);
           break;
        }
        case 'c':
        { //If passed in type is 'c', sort characters
            tmp = char_sorter(l, arg);
            break;
        }
        case 'b':
        { //If passed in type is 'b', sort booleans
            tmp = bool_sorter(l, arg);
            break;
        }
    }
    return tmp;
}

lynk *int_sorter(lynk *l, char arg)
{ //Sorts lynks in ascending ('f') or descending ('r') order
    int len = lynksize(l); //Length of passed in head lynk's list
    lynk **arr = malloc(sizeof(lynk*)*len); //Temporary array
    int ind = 0; //Index for below while loop
    while (l)
    { //Appends all lynk values to array of lynks
        arr[ind] = lynkall(l->intval, l->strval, l->charval, l->boolval); //Copies all lynk values to new lynk
        l = l->next; //Changes to next lynk
        ind++; //Increments index in temp array
    }
    for (int i = 1; i < len; i++) //For each in size of lynk list
    {
        int key = arr[i]->intval; //Current index
        int j = i - 1; //Comparing with previous index

        while (j >= 0 && arr[j]->intval > key)
        { //While j is not less than zero and value at j index is greater than the value to the right of it
            arr[j + 1]->intval = arr[j]->intval; //changing index after j to j
            j = j - 1; //Iterating backwards
        }
        arr[j + 1]->intval = key; //Index after j to key
    }

    lynk *tmp = NULL;
    for (int i = 0; i < len; i++)
    { //Appending the array back to the null lynks, order depending on provided arg
        if (arg == 'f')
        { //If forward, appending to the back of the lynk list
            lynkback(&tmp, arr[i]);
        }
        else if (arg == 'r')
        { //If reverse, appending to the front of the lynk list
            lynkfront(&tmp, arr[i]);
        }
    }
    free(arr); //Frees temp array
    return tmp; //Returning new lynk list
}

lynk *str_sorter(lynk *l, char arg)
{ //Sorts strings lexicographically (i vs i + 1), dismisses case
    int num_of_strings = lynksize(l); //Number of strings being sorted
    lynk **arr = malloc(sizeof(lynk*)*num_of_strings); //Creating a temp string buffer, and a buffer array to sort strings
    //Size of character pointer * number of strings. Dynamically allocated, stack overflows if not
    int ind = 0; //Index for below while loop
    while (l)
    { //Appending strings to array of lynks
        arr[ind] = lynkall(l->intval, l->strval, l->charval, l->boolval);
        l = l->next;
        ind++;
    }
    int i, j;
    for (i = 0; i < num_of_strings; i++) //first string
    {
        for (j = i + 1; j < num_of_strings; j++) //second string
        {
            lynk *temp = malloc(sizeof(lynk));
            if (strcasecmp(arr[i]->strval, arr[j]->strval) > 0) //Comparing first str to second str
            { //If second string is sorted to before first string
                strcpy(temp->strval, arr[i]->strval); //Copy first string to buffer var
                strcpy(arr[i]->strval, arr[j]->strval); //Replace first string with second string
                strcpy(arr[j]->strval, temp->strval); //Replace second string with first string (from buffer)
            }
            free(temp);
        }
    }
    lynk *tmp = NULL; //Creating lynk set to NULL, to be filled
    for (int x = 0; x < num_of_strings; x++)
    {
        if (arg == 'f')
        { //Appending strings to the back of the lynk list, sorted order
            lynkback(&tmp, arr[x]);
        }
        else if (arg == 'r')
        { //Appending strings to the front of the lynk list, reverse-sorted order
            lynkfront(&tmp, arr[x]);
        }
    }
    free(arr); //Frees temp array
    return tmp; //Returning new lynk list
}

lynk *char_sorter(lynk *l, char arg)
{ //Sorts alphabetically, disregards case on sort, preserves case on output
    int len = lynksize(l); //Length of passed in head lynk's list
    lynk **arr = malloc(sizeof(lynk*)*len); //Temporary array
    bool is_cap[len]; //Buffer array for capital preservation
    int ind = 0; //Index for below while loop
    while (l)
    { //Appends all lynk values to array of lynks
        char letter = l->charval;
        is_cap[ind] = isupper(letter); //Checking if letter is upper, saving state to bool array
        arr[ind] = lynkall(l->intval, l->strval, tolower(letter), l->boolval);
        l = l->next;
        ind++;
    }
    for (int key, j, b_key, i = 1; i < len; i++)
    { //Iterating through letters and cap state array
        key = arr[i]->charval; //Saving currently indexed letter to key
        b_key = is_cap[i]; //Saving currently indexed bool to b_key
        j = i - 1; //Comparing with previous index

        while (j >= 0 && (int)arr[j]->charval > key)
        { //While j is not less than zero and value at j index is greater than the value to the right of it
            arr[j + 1]->charval = arr[j]->charval; //Changing index j + 1 to j
            is_cap[j + 1] = is_cap[j]; //Appling same logic to companion array
            j = j - 1; //Iterating backwards
        }
        arr[j + 1]->charval = key;
        is_cap[j + 1] = b_key;
    }
    lynk *tmp = NULL; //Creating new lynk that will be provided sorted chars
    for (int i = 0; i < len; i++)
    {
        if (arg == 'f')
        { //If arg is 'f', appening to back of lynk, sorted order
            if (is_cap[i])
            {
                arr[i]->charval = toupper(arr[i]->charval);
                lynkback(&tmp, arr[i]);
            }
            else
            {
                lynkback(&tmp, arr[i]);
            }
        }
        else if (arg == 'r')
        { //If arg is 'r', appending to front of lynk, reverse-sorted order
            if (is_cap[i])
            {
                arr[i]->charval = toupper(arr[i]->charval);
                lynkfront(&tmp, arr[i]);
            }
            else
            {
                lynkfront(&tmp, arr[i]);
            }
        }
    }
    free(arr);
    return tmp;
}

lynk *bool_sorter(lynk *l, char arg)
{ //Sorts true / false for sorted order, false / true for reverse-order
    lynk *tmp = NULL;
    while (l)
    { //Appending all letters to array as lower case, remembering case state
        if (l->boolval)
        {
            if (arg == 'f')
            {
                lynkfront(&tmp, lynkall(l->intval, l->strval, l->charval, l->boolval));
            }
            else if (arg == 'r')
            {
                lynkback(&tmp, lynkall(l->intval, l->strval, l->charval, l->boolval));
            }
        }
        else
        {
            if (arg == 'f')
            {
                lynkback(&tmp, lynkall(l->intval, l->strval, l->charval, l->boolval));
            }
            else if (arg == 'r')
            {
                lynkfront(&tmp, lynkall(l->intval, l->strval, l->charval, l->boolval));
            }
        }
        l = l->next;
    }
    return tmp;
}