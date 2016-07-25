#ifndef DEF_HASHMAP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct s_map_entry
{
    char* key;
    char* data;
    struct s_map_entry *next;
} t_map_entry;

typedef struct s_map
{
    t_map_entry **entres;
    int size;
    int slots;
    float load_factor;
    float grow_factor;
} t_map;

t_map* map_create(int slots, float load_factor,float grow_factor);
int map_hash(char *key);
void map_put(t_map *map, char* key, void *value);
void* map_get(t_map *map, char* key);
t_map_entry *map_entry_create(char* key, char* data);
t_map* map_resize(t_map *map);

#endif // DEF_HASHMAP
