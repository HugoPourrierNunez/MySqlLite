#ifndef DEF_HASHMAP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"


typedef enum {HASHMAP_TYPE_INT, HASHMAP_TYPE_DOUBLE, HASHMAP_TYPE_STRING, HASHMAP_TYPE_MAP_LIST} t_hashmap_type;

typedef struct s_hashmap t_hashmap;

typedef union
{
    int integer;
    double flottant;
    char* text;
    t_list_chain *linked_list;
} t_hashmap_union;

typedef struct s_hashmap_data
{
    t_hashmap_union value;
    t_hashmap_type type;
} t_hashmap_data;


typedef struct s_map_entry
{
    char* key;
    t_hashmap_data data;
    struct s_map_entry *next;
} t_map_entry;

typedef struct s_hashmap
{
    t_map_entry **entres;
    int size;
    int slots;
    float load_factor;
    float grow_factor;
} t_hashmap;

t_hashmap* map_create(int slots, float load_factor,float grow_factor);
int map_hash(char *key);
void map_put(t_hashmap *map, char* key, t_hashmap_data value, int multipleKey);
void map_put_string(t_hashmap *map, char* key,char* value, int multipleKey);
void map_put_double(t_hashmap *map, char* key, double value, int multipleKey);
void map_put_int(t_hashmap *map, char* key, int value, int multipleKey);
void map_put_map(t_hashmap *map, char* key, void* value, int multipleKey);
t_hashmap_data* map_get_collection(t_hashmap *map, char* key);
t_hashmap_data* map_get_list_map_contain_value(t_hashmap *map, char* key1, char* key2);
t_hashmap_data* map_get(t_hashmap *map, char* key);
t_map_entry* map_entry_create(char* key, t_hashmap_data data);
t_hashmap* map_resize(t_hashmap *map);

#endif // DEF_HASHMAP
