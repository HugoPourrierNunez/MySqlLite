#ifndef DEF_HASHMAP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct s_map_entry
{
    char* key;
    void* data;
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
void map_put(t_hashmap *map, char* key, void *value);
void* map_get(t_hashmap *map, char* key);
t_map_entry *map_entry_create(char* key, char* data);
t_hashmap* map_resize(t_hashmap *map);

#endif // DEF_HASHMAP
