#include <stdio.h>
#include <stdlib.h>
#include "HashMap.h"

int main (int argc, char *argv[])
{
    t_map *map = map_create(6,.7,2);
    map_put(map,"age", 2);
    map_put(map, "poid", 60);
    map_put(map,"agea", 4);
    //map_remove(map, "age");
    printf("%i\n",(int) map_get(map,"age"));
    printf("%i\n",(int) map_get(map,"poid"));
    return 0;
}
