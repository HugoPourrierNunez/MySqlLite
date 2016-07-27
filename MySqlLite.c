#include "MySqlLite.h"


char* JSON_stringify(t_hashmap* map)
{
    if(!map)
        return NULL;

    t_mystr *result = mystr_create(1000);
    int i,j;

    mystr_add(result, "{");

    for(i=0; i<map->slots; i++)
    {
        t_map_entry **entry=&(map->entres[i]);
        while(*entry)
        {
            mystr_add(result, "\"");
            mystr_add(result, (*entry)->key);
            mystr_add(result, "\":[");
            if((*entry)->data.type!=HASHMAP_TYPE_MAP)
                return NULL;
            t_hashmap *map2 = (t_hashmap*) (*entry)->data.value;

            for(j=0; j<map2->slots; j++)
            {
                t_map_entry **entry2=&(map2->entres[j]);
                if(*entry2)
                {
                    mystr_add(result, "{");
                    while(*entry2)
                    {
                        mystr_add(result, "\"");
                        mystr_add(result, (*entry2)->key);
                        mystr_add(result, "\":");
                        if((*entry2)->data.type==HASHMAP_TYPE_STRING)
                        {
                            mystr_add(result,"\"");
                            mystr_add(result, (*entry2)->data.value);
                            mystr_add(result, "\"");
                        }
                        else if((*entry2)->data.type==HASHMAP_TYPE_INT)
                        {
                            mystr_add(result," ");
                            char nb[100];
                            sprintf(nb,"%i",(int) (*entry2)->data.value);
                            mystr_add(result, nb);
                            mystr_add(result, " ");
                        }
                        else if((*entry2)->data.type==HASHMAP_TYPE_FLOAT)
                        {
                            printf("in\n\n");
                            mystr_add(result," ");
                            char nb[100];
                            sprintf(nb,"%f",(*entry2)->data.value);
                            mystr_add(result, nb);
                            mystr_add(result, " ");
                        }

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



t_arg* create_arg(t_arg_type type, char* value)
{
    t_arg *arg = malloc(sizeof(t_arg));
    arg->type=type;
    arg->value=value;

    return arg;
}

t_arg* parseArg(char* arg)
{
    t_mystr *text=mystr_create(100);
    t_arg *argument = create_arg(ARG_TYPE_DEFAULT,NULL);
    int len = strlen(arg),i;
    if(len==0 || arg[0]!='-')
        return NULL;
    i=1;
    while(i<len && arg[i]!='=')
    {
        mystr_add_char(text,arg[i]);
        i++;
    }
    if(i>=len && text->length==1)
        return NULL;
    if(strcmp("collection",text->text)==0)
        argument->type=ARG_TYPE_COLLECTION;
    else if(strcmp("find",text->text)==0)
        argument->type=ARG_TYPE_FIND;
    else if(strcmp("insert",text->text)==0)
        argument->type=ARG_TYPE_INSERT;
    else if(strcmp("projection",text->text)==0)
        argument->type=ARG_TYPE_PROJECTION;
    else if(strcmp("remove",text->text)==0)
        argument->type=ARG_TYPE_REMOVE;
    else if(strcmp("set",text->text)==0)
        argument->type=ARG_TYPE_SET;
    else if(strcmp("sort",text->text)==0)
        argument->type=ARG_TYPE_SORT;
    else if(strcmp("where",text->text)==0)
        argument->type=ARG_TYPE_WHERE;
    else
        return NULL;
    mystr_flush(text);
    i++;
    while(i<len)
    {
        mystr_add_char(text,arg[i]);
        i++;
    }
    if(text->length==1)
        return NULL;
    argument->value=mystr_copy(text);

    return argument;
}

t_hashmap* JSON_full_parse(char* text)
{
    t_hashmap *map = map_create(100,.7,2);
    t_hashmap *subMap=NULL;

    int i=0, len=strlen(text), nbAccolade=0, nbCrochet=0, nbGuillemets=0,niveau=0,
        startTextValue=0, nbVal=0, sortieAccolade=0,virgule=0,deuxPoint=0,point=0;

    t_mystr *value = mystr_create(100);
    t_mystr *key = mystr_create(100);
    t_mystr *collection = mystr_create(100);

    if(len==0)
    {
        printf("1");
        return NULL;
    }
    for(i=0; i<len; i++)
    {
        while((text[i]==' ' || text[i]=='\n' || text[i]=='\t') && i<len && startTextValue==0)
        {
            i++;
            if(value->length>1)
            {
                if(point)
                {
                    map_put(subMap,mystr_copy(key),atoi(value->text),HASHMAP_TYPE_INT,0);
                }
                else
                    map_put(subMap,mystr_copy(key), atoi(value->text),HASHMAP_TYPE_INT,0);
                nbVal++;
                point=0;
                mystr_flush(value);
                mystr_flush(key);
            }
        }
        char c = text[i];
        if(startTextValue && c!='\"')
        {
            if(niveau==1)
            {
                mystr_add_char(collection,c);
            }
            else if(niveau==2)
            {
                if(nbVal%2==0)
                    mystr_add_char(key,c);
                else
                {
                    mystr_add_char(value,c);
                }

            }
        }
        if(c=='{')
        {
            if(sortieAccolade && !virgule)
            {
                printf("2");
                return NULL;
            }
            nbAccolade++;
            niveau++;
            sortieAccolade=0;
            virgule=0;

            if(niveau==2)
            {
                subMap = map_create(100,.7,2);
            }

        }
        else if(c=='}')
        {
            if(virgule)
            {
                printf("3");
                return NULL;
            }
            if(niveau==2 && nbVal%2!=0)
            {
                printf("4");
                return NULL;
            }
            nbAccolade--;
            niveau--;
            sortieAccolade=1;

            if(niveau==1)
            {
                map_put(map,mystr_copy(collection),subMap,HASHMAP_TYPE_MAP,0);
            }
        }
        else if(c=='[')
        {
            if(niveau!=1)
            {
                printf("5");
                return NULL;
            }
            if(!deuxPoint)
            {
                printf("6");
                return NULL;
            }
            deuxPoint=0;
            nbCrochet++;
            sortieAccolade=0;
            virgule=0;
        }
        else if(c==']')
        {
            if(virgule)
            {
                printf("7");
                return NULL;
            }
            nbCrochet--;
            mystr_flush(collection);
        }
        else if(c==':')
        {
            if(deuxPoint)
            {
                printf("8");
                return NULL;
            }
            if(nbVal%2==0 && niveau==2)
            {
                printf("9");
                return NULL;
            }
            deuxPoint=1;
        }
        else if(isdigit(c) && startTextValue==0)
        {
            if(niveau==2 && nbVal%2==1 && deuxPoint)
            {
                deuxPoint=0;
                mystr_add_char(value,c);
            }
            else if(value->length>1)
            {
                mystr_add_char(value,c);
            }
            else if(startTextValue==0)
            {
                printf("10");
                return NULL;
            }
        }
        else if(c=='.')
        {
            if(point && value->length==1)
            {
                printf("11");
                return NULL;
            }
            if(value->length>1)
            {
                mystr_add_char(value,c);
                point=1;
            }
        }
        else if(c=='\"')
        {
            nbGuillemets++;
            if(nbGuillemets%2==1)
            {
                deuxPoint=0;
                startTextValue=1;
            }
            else
            {
                startTextValue=0;
                if(niveau==2)
                {
                    nbVal++;
                    if(nbVal%2==0)
                    {
                        if(value->length==1)
                        {
                            printf("12");
                            return NULL;
                        }
                        map_put(subMap,mystr_copy(key),mystr_copy(value),HASHMAP_TYPE_STRING,0);
                        mystr_flush(value);
                        mystr_flush(key);
                    }
                    else if(key->length==1)
                    {
                        printf("16");
                        return NULL;
                    }
                }
            }

        }
        else if(c==',')
        {
            if(virgule)
            {
                printf("13");
                return NULL;
            }
            virgule=1;
        }
        else if(!startTextValue)
        {
            printf("14");
            return NULL;
        }
    }
    if(nbAccolade || nbCrochet || nbGuillemets%2)
    {
        printf("15");
        return NULL;
    }

    return map;
}


t_hashmap* JSON_parse(char* text)
{

    t_hashmap *map = map_create(100,.7,2);

    int i=0, len=strlen(text), nbAccolade=0,niveau=0,nbGuillemets=0,
        startTextValue=0, nbVal=0,virgule=0,deuxPoint=0,point=0,sortieAccolade=0;

    t_mystr *value = mystr_create(100);
    t_mystr *key = mystr_create(100);

    if(len==0)
        return NULL;
    for(i=0; i<len; i++)
    {
        while((text[i]==' ' || text[i]=='\n' || text[i]=='\t') && i<len && startTextValue==0)
        {
            i++;
            if(value->length>1)
            {
                nbVal++;
                point=0;
                map_put(map,mystr_copy(key),mystr_copy(value),HASHMAP_TYPE_STRING,0);
                mystr_flush(key);
                mystr_flush(value);
            }
        }
        char c = text[i];
        if(startTextValue && c!='\'' )
        {
            if(niveau==2)
            {
                if(nbVal%2==0)
                    mystr_add_char(key,c);
                else
                    mystr_add_char(value,c);
            }
        }

        if(c=='{')
        {
            if(sortieAccolade && !virgule)
                return NULL;
            nbAccolade++;
            niveau++;
            sortieAccolade=0;
            virgule=0;
        }
        else if(c=='}')
        {
            if(virgule)
                return NULL;
            if(niveau==2 && nbVal%2!=0)
                return NULL;
            nbAccolade--;
            niveau--;
            sortieAccolade=1;
        }
        else if(c==':')
        {
            if(deuxPoint)
                return NULL;
            if(nbVal%2==0 && niveau==1)
                return NULL;
            deuxPoint=1;
        }
        else if(isdigit(c) && startTextValue==0)
        {
            if(niveau==1 && nbVal%2==1 && deuxPoint)
            {
                deuxPoint=0;
                mystr_add_char(value,c);
            }
            else if(value->length>1)
            {
                mystr_add_char(value,c);
            }
            else if(startTextValue==0)
                return NULL;
        }
        else if(c=='.')
        {
            if(point && value->length==1)
                return NULL;
            if(value->length>1)
            {
                mystr_add_char(value,c);
                point=1;
            }
        }
        else if(c=='\'')
        {
            nbGuillemets++;
            if(nbGuillemets%2==1)
            {
                deuxPoint=0;
                startTextValue=1;
            }
            else
            {
                startTextValue=0;
                if(value->length==1)
                    return NULL;
                if(niveau==1)
                {
                    nbVal++;
                    if(nbVal%2==0)
                    {
                        map_put(map,mystr_copy(key),mystr_copy(value),HASHMAP_TYPE_STRING,0);
                        mystr_flush(key);
                        mystr_flush(value);
                    }
                }

                mystr_flush(value);
            }
        }
        else if(c==',')
        {
            if(virgule)
                return NULL;
            virgule=1;
        }
        else if(!startTextValue)
            return NULL;
    }
    if(nbAccolade || nbGuillemets%2)
        return NULL;

    return map;
}

int analyseJSON(char *text)
{
    int i=0, len=strlen(text), nbAccolade=0, nbCrochet=0, nbGuillemets=0,niveau=0,
        startTextValue=0, nbVal=0, sortieAccolade=0,virgule=0,deuxPoint=0,point=0;
    t_mystr *value = mystr_create(100);
    if(len==0)
        return -1;
    for(i=0; i<len; i++)
    {

        printf("%c",text[i]);
        while((text[i]==' ' || text[i]=='\n' || text[i]=='\t') && i<len && startTextValue==0)
        {
            i++;
            printf("%c",text[i]);
            if(value->length>1)
            {
                nbVal++;
                point=0;
                mystr_flush(value);
            }
        }
        char c = text[i];
        if(startTextValue && c!='\"')
        {
            mystr_add_char(value,c);
        }

        if(c=='{')
        {
            if(sortieAccolade && !virgule)
                return -2;
            nbAccolade++;
            niveau++;
            sortieAccolade=0;
            virgule=0;
        }
        else if(c=='}')
        {
            if(virgule)
                return -3;
            if(niveau==2 && nbVal%2!=0)
                return -4;
            nbAccolade--;
            niveau--;
            sortieAccolade=1;
        }
        else if(c=='[')
        {
            if(niveau!=1)
                return -5;
            if(!deuxPoint)
                return -6;
            deuxPoint=0;
            nbCrochet++;
            sortieAccolade=0;
            virgule=0;
        }
        else if(c==']')
        {
            if(virgule)
                return -7;
            nbCrochet--;
        }
        else if(c==':')
        {
            if(deuxPoint)
                return -8;
            if(nbVal%2==0 && niveau==2)
                return -9;
            deuxPoint=1;
        }
        else if(isdigit(c) && startTextValue==0)
        {
            if(niveau==2 && nbVal%2==1 && deuxPoint)
            {
                deuxPoint=0;
                mystr_add_char(value,c);
            }
            else if(value->length>1)
            {
                mystr_add_char(value,c);
            }
            else if(startTextValue==0)
                return -10;
        }
        else if(c=='.')
        {
            if(point && value->length==1)
                return -11;
            if(value->length>1)
            {
                mystr_add_char(value,c);
                point=1;
            }
        }
        else if(c=='\"')
        {
            nbGuillemets++;
            if(nbGuillemets%2==1)
            {
                deuxPoint=0;
                startTextValue=1;
            }
            else
            {
                startTextValue=0;
                if(value->length==1)
                    return -12;
                if(niveau==2)
                    nbVal++;
//                printf("key=%s\n",value->text);
                mystr_flush(value);
            }

        }
        else if(c==',')
        {
            if(virgule)
                return -13;
            virgule=1;
        }
        else if(!startTextValue)
            return -14;
    }
    if(nbAccolade || nbCrochet || nbGuillemets%2)
        return -15;

    return 0;
}
