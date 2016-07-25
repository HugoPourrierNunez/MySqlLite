#include "MySqlLite.h"


char* JSON_stringify(t_hashmap* map)
{
    if(!map)
        return NULL;

    t_mystr *result = mystr_create(1000);
    int i,j;

    mystr_add(result, "{");

    for(i=0;i<map->slots;i++)
    {
        t_map_entry **entry=&(map->entres[i]);
        while(*entry)
        {
            mystr_add(result, "\"");
            mystr_add(result, (*entry)->key);
            mystr_add(result, "\":[");
            t_hashmap *map2 = (t_hashmap*) (*entry)->data;

            for(j=0;j<map2->slots;j++)
            {
                t_map_entry **entry2=&(map2->entres[j]);
                if(*entry2)
                {
                    mystr_add(result, "{");
                    while(*entry2)
                    {
                        mystr_add(result, "\"");
                        mystr_add(result, (*entry2)->key);
                        mystr_add(result, "\":\"");
                        mystr_add(result, (*entry2)->data);
                        mystr_add(result, "\"");

                        entry2=&(*entry2)->next;
                    }
                    mystr_add(result, "},\n");
                }

            }
            mystr_remove(result,2);
            mystr_add(result, "\n");
            entry = &(*entry)->next;
            mystr_add(result, "],\n");
        }
    }
    mystr_remove(result,2);
    mystr_add(result, "\n");
    mystr_add(result, "}");

    char *text = result->text;
    free(result);
    return text;
}
