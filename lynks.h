#ifndef LYNKS_H
#define LYNKS_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <strings.h>

#define MAX_STRING_LENGTH 100

// Lynk Struct
typedef struct lynk {

    int intval;
    char strval[MAX_STRING_LENGTH];
    char charval;
    bool boolval;

    int size;

    struct lynk *prev;
    struct lynk *end;
    struct lynk *next;

} lynk;

lynk *lynkempty(void);
lynk *lynkall(int ival, char sval[], char cval, bool bval);
lynk *lynkint(int ival);
lynk *lynkstr(char sval[]);
lynk *lynkchar(char cval);
lynk *lynkbool(bool bval);
int lynkcount(lynk *start);
int lynksize(lynk *start);
lynk *lynkgoto(lynk *start, int index);
void lynkinsert(lynk **start, int index, lynk *l);
void lynkback(lynk **start, lynk *l);
void lynkfront(lynk **start, lynk *l);
void lynkprint(lynk *start, char arg);
lynk *lynkarr(int size);
void lynkpop(lynk **start, int index);
void lynkpopfront(lynk **start);
void lynkpopback(lynk **start);
void lynkunload(lynk *start);



#endif