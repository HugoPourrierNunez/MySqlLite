#include "HashMap.h"

t_map_entry *map_entry_create(char* key, t_hashmap_data data)
{
    t_map_entry *new_entry=malloc(sizeof(t_map_entry));
    new_entry->data=data;
    new_entry->key=key;
    new_entry->next=0;
    return new_entry;
}


t_hashmap_data* map_get_list_map_contain_value(t_hashmap *map, char* key1, char* key2)
{
    t_hashmap_data *result = map_get_collection(map,key1);
    if(result && result->type==HASHMAP_TYPE_MAP_LIST)
    {
        t_list_chain *list_result=0;

        t_list_chain *list = result->value.linked_list;

        while(list)
        {
            t_hashmap_data *data = 0;
            data = map_get(list->value,key2);
            if(data)
            {
                list_append2(&list_result, list->value);
            }
            list=list->next;
        }
        return list_result;
    }
    return NULL;
}

t_hashmap_data* map_get(t_hashmap *map, char* key)
{
    if(!map)
        return NULL;
    int indice = map_hash(key)%map->slots;
    if(map->entres[indice]==0)
        return NULL;
    t_map_entry *entry=map->entres[indice];
    while(strcmp(entry->key,key)!=0 && entry->next!=0)
        entry=entry->next;
    if(strcmp(entry->key,key)!=0)
        return NULL;
    return &entry->data;
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


void map_put_string(t_hashmap *map, char* key,char* value, int multipleKey)
{
    t_hashmap_data data;
    data.value.text=value;
    data.type=HASHMAP_TYPE_STRING;
    map_put(map,key,data,0);
}

void map_put_double(t_hashmap *map, char* key, double value, int multipleKey)
{
    t_hashmap_data data;
    data.value.flottant=value;
    data.type=HASHMAP_TYPE_DOUBLE;
    map_put(map,key,data,0);
}

void map_put_int(t_hashmap *map, char* key, int value, int multipleKey)
{
    t_hashmap_data data;
    data.value.integer=value;
    data.type=HASHMAP_TYPE_INT;
    map_put(map,key,data,0);
}


void map_put_map(t_hashmap *map, char* key, void *value, int multipleKey)
{
    t_hashmap_data *result = map_get_collection(map,key);
    if(result && result->type==HASHMAP_TYPE_MAP_LIST)
    {
        list_append2(&result->value.linked_list, value);

    }
    else{
        t_hashmap_data data;
        data.value.linked_list = list_append(0, value);
        data.type=HASHMAP_TYPE_MAP_LIST;
        map_put(map,key,data,0);
    }
}

void map_put(t_hashmap *map, char* key, t_hashmap_data value, int multipleKey)
{
    if(!map)
        return;
    int indice = map_hash(key)%map->slots;

    t_map_entry **entry=&(map->entres[indice]);
    while(*entry)
    {
        if(multipleKey && strcmp((*entry)->key,key)==0)
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




t_hashmap_data* map_get_collection(t_hashmap *map, char* key)
{
    if(!map)
        return NULL;
    int indice = map_hash(key)%map->slots;
    if(map->entres[indice]==0)
        return NULL;
    t_map_entry *entry=map->entres[indice];
    while(strcmp(entry->key,key)!=0 && entry->next!=0)
        entry=entry->next;
    if(strcmp(entry->key,key)!=0)
        return NULL ;
    return &entry->data;
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
            free(tmp->key);
            free(tmp);
            map->size--;
            return;
        }
        entry = &(*entry)->next;
    }
}

//void map_put_resize(t_hashmap* mapHash, char* key, void* value)
//{
//    if(!mapHash) return;
//
//    if(mapHash->slots > (mapHash->load_factor * mapHash->slots))
//    {
//       // printf("%d\n", mapHash->slots);
//        t_hashmap* map = map_create(mapHash->slots*mapHash->grow_factor, mapHash->load_factor, mapHash->grow_factor);
//        int i;
//        for(i=0; i<mapHash->slots;i++)
//        {
//            t_map_entry** map_entry = &(mapHash->entres[i]);
//            while(*map_entry)
//            {
//                char* key_entry = (*map_entry)->key;
//                t_hashmap_data value_entry = (*map_entry)->data;
//                map_put(map, key_entry, value_entry);
//                map_entry = &(*map_entry)->next;
//            }
//        }
//        free(mapHash->entres);
//        *mapHash = *map;
//    }
//    map_put(mapHash, key, value);
//}
