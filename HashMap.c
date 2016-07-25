#include "HashMap.h"

t_map_entry *map_entry_create(char* key, t_hashmap_data data)
{
    t_map_entry *new_entry=malloc(sizeof(t_map_entry));
    new_entry->data=data;
    new_entry->key=key;
    new_entry->next=0;
    return new_entry;
}




t_hashmap* map_create(int slots, float load_factor,float grow_factor)
{
    t_hashmap *map = (t_hashmap*) malloc(sizeof(t_hashmap));

    map->load_factor=load_factor;
    map->grow_factor=grow_factor;
    map->size=0;
    map->slots=slots;

    map->entres = (t_map_entry**) malloc(slots*sizeof(t_map_entry*));
    int i;
    for(i=0;i<map->slots;i++)
    {
        map->entres[i]=0;
    }

    return map;
}

int map_hash(char *key)
{
    int total = 0,i=0;
    while(key[i]!='\0')
    {
        total+=key[i];
        total = total <<1;
        i++;
    }
    return total;
}


void map_put_string(t_hashmap *map, char* key,char* value)
{
    t_hashmap_data data;
    data.value.text=value;
    data.type=HASHMAP_TYPE_STRING;
    map_put(map,key,data);
}

void map_put_double(t_hashmap *map, char* key, double value)
{
    t_hashmap_data data;
    data.value.flottant=value;
    data.type=HASHMAP_TYPE_DOUBLE;
    map_put(map,key,data);
}

void map_put_int(t_hashmap *map, char* key, int value)
{
    t_hashmap_data data;
    data.value.integer=value;
    data.type=HASHMAP_TYPE_INT;
    map_put(map,key,data);
}


void map_put_map(t_hashmap *map, char* key, t_hashmap *value)
{
    t_hashmap_data data;
    data.value.hashmap=value;
    data.type=HASHMAP_TYPE_MAP;
    map_put(map,key,data);
}

void map_put(t_hashmap *map, char* key, t_hashmap_data value)
{
    if(!map)
        return;
    int indice = map_hash(key)%map->slots;

    t_map_entry **entry=&(map->entres[indice]);
    while(*entry)
    {
        if(strcmp((*entry)->key,key)==0)
        {
            (*entry)->data=value;
            return;
        }
        entry=&(*entry)->next;
    }
    *entry=map_entry_create(key,value);
    map->size++;

//    if(map->size>=map->slots*map->load_factor)
//        map_resize(map);
}




t_hashmap_data map_get(t_hashmap *map, char* key)
{
    if(!map)
        return;
    int indice = map_hash(key)%map->slots;
    if(map->entres[indice]==0)
        return;
    t_map_entry *entry=map->entres[indice];
    while(strcmp(entry->key,key)!=0 && entry->next!=0)
        entry=entry->next;
    if(strcmp(entry->key,key)!=0)
        return ;
    return entry->data;
}

void map_remove(t_hashmap *map, char* key)
{
    int indice = map_hash(key)%map->slots;
    if(map->entres[indice]==0)
        return;
    t_map_entry **entry=&(map->entres[indice]);

    while(*entry)
    {
        if(strcmp((*entry)->key,key)==0)
        {
            t_map_entry* tmp = (*entry);
            (*entry)=(*entry)->next;
            free(tmp);
            map->size--;
            return;
        }
        entry = &(*entry)->next;
    }
}

t_hashmap* map_resize(t_hashmap* map)
{
    if(!map)
    {
        return;
    }
    // Sauvegarde le début de la map en parametre
    t_hashmap* stockPremiere = map;

    // Initialisation de la map résultat
    t_hashmap* newMap = (t_hashmap*)calloc(map->slots * map->grow_factor, sizeof(t_hashmap));

    newMap->grow_factor = map->grow_factor;
    newMap->size = map->size;
    newMap->slots = map->slots * 2;
    newMap->load_factor = map->load_factor;

    // On remplit la nouvelle map
    int i = 0;

    for(; i < map->size; i++)
    {
        map_put(newMap,map->entres[i]->key, map->entres[i]->data);
    }

    return newMap;
}
