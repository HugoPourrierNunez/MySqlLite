#ifndef DEF_MYSQLLITE

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "HashMap.h"
#include "MyString.h"

t_hashmap* JSON_parse(char* string);
// Convert a JSON String to a HashMap representation.
char* JSON_stringify(t_hashmap* map) ;
// Convert a HashMap to a JSON String representation.
void* hashmap_traverse(t_hashmap* map, char* path) ;
// Traverse a HashMap according to the given path
// Ex : hashmap_traverse(map, 'student.rate')
void hashmap_put(t_hashmap* map, char* path, void* value) ;
// Traverse a HashMap according to the given path
// Ex : hashmap_put(map, 'student.rate', 56);
// hashmap_traverse(map, 'student.rate')
//56
int analyseJSON(char *text);


#endif // DEF_MYSQLLITE
