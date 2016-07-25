#include <stdio.h>
#include <stdlib.h>
#include "MySqlLite.h"

int main (int argc, char *argv[])
{
//    testHashMap();

    t_hashmap *map1 = map_create(6,.7,2);
    map_put(map1,"age", "21");
    map_put(map1, "poid", "69");

    t_hashmap *map2 = map_create(6,.7,2);
    map_put(map2,"name", "hugo");
    map_put(map2, "note", "18");

    t_hashmap *map = map_create(6,.7,2);
    map_put(map,"info1", map1);
    map_put(map,"info2", map2);

    printf("%s", JSON_stringify(map));

    return 0;
}

void testHashMap()
{
    t_hashmap *map = map_create(4,.7,2);
    map_put(map,"age", 2);
    map_put(map, "poid", 60);
    map_put(map,"agea", 4);
    //map_remove(map, "age");
    printf("%i\n",(int) map_get(map,"age"));
    printf("%i\n",(int) map_get(map,"poid"));
}
