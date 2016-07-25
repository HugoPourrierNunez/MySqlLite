#ifndef DEF_MYSQLLITE

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "HashMap.h"
#include "MyString.h"

t_hashmap* JSON_parse(char* string);
char* JSON_stringify(t_hashmap* map) ;

int analyseJSON(char *text);


#endif // DEF_MYSQLLITE
