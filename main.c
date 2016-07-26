#include <stdio.h>
#include <stdlib.h>
#include "MySqlLite.h"

int main (int argc, char *argv[])
{
//    testHashMap();
//    testMySqlLite();
    int i=1;
    for(;i<argc;i++)
    {
        printf("arg='%s'\n",argv[i]);
        parseArg(argv[i]);
    }

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
    map_put_int(map1,"age", 21555);
    map_put_string(map1, "poid", "69");

    t_hashmap *map2 = map_create(6,.7,2);
    map_put_string(map2,"name", "hugo");
    map_put_double(map2, "note", 17.2 );

    t_hashmap *map = map_create(6,.7,2);
    map_put_map(map,"info1", map1);
    map_put_map(map,"info2", map2);

    char *text = JSON_stringify(map);

    printf("%s\n", text);

    t_hashmap *test = JSON_full_parse(text);
    char *text2 = JSON_stringify(map);

    printf("%s\n", text2);

}
