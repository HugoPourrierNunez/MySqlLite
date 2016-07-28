#include <stdio.h>
#include <stdlib.h>
#include "MySqlLite.h"

void recognizeArg(int argc, char *argv[])
{
    if(argc<2)
        return 0;
    int i=1, nbArg=argc-1;
    t_arg **listArg = malloc((nbArg)*sizeof(t_arg*));
    for(i=0;i<argc-1;i++)
        listArg[i]=NULL;
    for(i=1;i<argc;i++)
    {
        printf("arg='%s'\n",argv[i]);
        listArg[i-1] = parseArg(argv[i]);
        if(listArg[i-1]==NULL)
        {
            printf("argument invalide %s",argv[i]);
            return 0;
        }
        printf("value=%s\n",listArg[i-1]->value);
    }

    for(i=0; i<nbArg;i++ )
    {
        if(listArg[i]->type==ARG_TYPE_COLLECTION)
        {
            printf("collection : value=%s\n",listArg[i]->value);
        }
    }
}

void testMySqlLite()
{
    int i=0,j;

    t_hashmap *map1 = map_create(100,.7,2);
    map_put_int(map1,"age", 21555,0);
    map_put_string(map1, "poid", "69",0);

    t_hashmap *map2 = map_create(100,.7,2);
    map_put_string(map2,"name", "hugo",0);
    map_put_string(map2,"name2", "test",0);
    map_put_double(map2, "note", 17.2,0);

    t_hashmap *map = map_create(100,.7,2);
    map_put_map(map,"info1", map1,0);
    map_put_map(map,"info1", map2,0);
    map_put_map(map,"info2", map2,0);

    t_list_chain *list = map_get_list_map_contain_value(map,"info1","age");


    char *text = JSON_stringify(map);
    printf("%s\n", text);

}


int main (int argc, char *argv[])
{

    testMySqlLite();
    return 0;
}

