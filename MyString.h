#ifndef DEF_MYSTRING

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct s_mystr
{
    char* text;
    int length;
    int maxSize;

} t_mystr;

void mystr_add(t_mystr *mystr, const char* text);
t_mystr* mystr_create(int maxSize);
void mystr_delete(t_mystr* mystr);
void mystr_remove(t_mystr* mystr, unsigned int nb);

#endif // DEF_MYSTRING
