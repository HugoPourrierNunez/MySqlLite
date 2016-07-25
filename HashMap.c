#include "HashMap.h"

t_map_entry *map_entry_create(char* key, char* data)
{
    t_map_entry *new_entry=malloc(sizeof(t_map_entry));
    new_entry->data=data;
    new_entry->key=key;
    new_entry->next=0;
    return new_entry;
}


t_map* map_create(int slots, float load_factor,float grow_factor)
{
    t_map *map = (t_map*) malloc(sizeof(t_map));

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

void map_put(t_map *map, char* key, void *value)
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

    if(map->size>=map->slots*map->load_factor)
        map_resize(map);
}




void* map_get(t_map *map, char* key)
{
    if(!map)
        return;
    int indice = map_hash(key)%map->slots;
    if(map->entres[indice]==0)
        return 0;
    t_map_entry *entry=map->entres[indice];
    while(strcmp(entry->key,key)!=0 && entry->next!=0)
        entry=entry->next;
    if(strcmp(entry->key,key)!=0)
        return 0;
    return entry->data;
}

void map_remove(t_map *map, char* key)
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

t_map* map_resize(t_map *map)
{
    int i;

    int slots = map->slots;
    map->slots*=map->grow_factor;
    map->size=0;
    t_map_entry **entry = malloc(slots*sizeof(t_map_entry*));
    for(i=0;i<map->slots;i++)
    {
        map->entres[i]=0;
    }


    for(i=0;i<slots;i++)
    {
        t_map_entry **map_entry = & (map->entres[i]);
        while(*map_entry)
        {
//            printf("%s\n",(*map_entry)->key);
            map_put(map,(*map_entry)->key,(*map_entry)->data);
            map_entry=&(*map_entry)->next;
        }
    }

    t_map_entry *tmp = map->entres;
    map->entres=entry;
    free(tmp);

    return map;
}
