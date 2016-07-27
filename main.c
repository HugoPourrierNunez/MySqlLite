#include <stdio.h>
#include <stdlib.h>
#include "MySqlLite.h"

int main (int argc, char *argv[])
{
//    testHashMap();
    testMySqlLite();
//    if(argc<2)
//        return 0;
//    int i=1, nbArg=argc-1;
//    t_arg **listArg = malloc((nbArg)*sizeof(t_arg*));
//    for(i=0;i<argc-1;i++)
//        listArg[i]=NULL;
//    for(i=1;i<argc;i++)
//    {
//        printf("arg='%s'\n",argv[i]);
//        listArg[i-1] = parseArg(argv[i]);
//        if(listArg[i-1]==NULL)
//        {
//            printf("argument invalide %s",argv[i]);
//            return 0;
//        }
//        printf("value=%s\n",listArg[i-1]->value);
//    }
//
//    for(i=0; i<nbArg;i++ )
//    {
//        if(listArg[i]->type==ARG_TYPE_COLLECTION)
//        {
//            printf("collection : value=%s\n",listArg[i]->value);
//        }
//    }

    return 0;
}



void testHashMap()
{
//    t_hashmap *map = map_create(4,.7,2);
//    map_put(map,"age", 2, HASHMAP_TYPE_INT);
//    map_put(map, "poid", 60,HASHMAP_TYPE_INT);
//    map_put(map,"agea", 4,HASHMAP_TYPE_INT);
//    //map_remove(map, "age");
//    printf("%i\n",(int) map_get(map,"age"));
//    printf("%i\n",(int) map_get(map,"poid"));
}

void testMySqlLite()
{
    t_hashmap *map1 = map_create(6,.7,2);
    map_put(map1,"age", 21555,HASHMAP_TYPE_INT,0);
    map_put(map1, "poid", "69",HASHMAP_TYPE_STRING,0);

    t_hashmap *map2 = map_create(6,.7,2);
    map_put(map2,"name", "hugo",HASHMAP_TYPE_STRING,0);
    map_put(map2,"name2", "test",HASHMAP_TYPE_STRING,0);
    float f = 17.2f;
    map_put(map2, "note", f, HASHMAP_TYPE_FLOAT,0);

    t_hashmap *map = map_create(6,.7,2);
    map_put(map,"info1", map1,HASHMAP_TYPE_MAP,0);
    map_put(map,"info2", map2,HASHMAP_TYPE_MAP,0);

//    printf("age=%i\n",map_get(map1,"age"));



    char *text = JSON_stringify(map);
    printf("%s\n", text);
//    printf("analyse=%i",analyseJSON(text));

//    printf("%s\n", text);

    t_hashmap *test = JSON_full_parse(text);

    if(test!=NULL)
    {
        printf("OK\n");
        char *text2 = JSON_stringify(test);
        printf("%s\n", text2);
    }
//        printf("analyse=%i",analyseJSON(text));

//

}
