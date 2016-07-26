#ifndef DEF_MYSQLLITE

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "HashMap.h"
#include "MyString.h"

typedef enum {ARG_TYPE_COLLECTION,
            ARG_TYPE_INSERT,
            ARG_TYPE_SET,
            ARG_TYPE_WHERE,
            ARG_TYPE_FIND,
            ARG_TYPE_PROJECTION,
            ARG_TYPE_SORT,
            ARG_TYPE_REMOVE} t_arg_type;


typedef struct s_arg
{
    t_arg_type type;
    char* value;
} t_arg;


t_hashmap* JSON_full_parse(char* string);
char* JSON_stringify(t_hashmap* map) ;
int analyseJSON(char *text);
t_arg parseArg(char* arg);


#endif // DEF_MYSQLLITE
