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
            t_hashmap *map2 = (t_hashmap*) (*entry)->data.value.hashmap;

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
                        mystr_add(result, "\":");
                        if((*entry2)->data.type==HASHMAP_TYPE_STRING)
                        {
                            mystr_add(result,"\"");
                            mystr_add(result, (*entry2)->data.value.text);
                            mystr_add(result, "\"");
                        }
                        else if((*entry2)->data.type==HASHMAP_TYPE_INT)
                        {
                            mystr_add(result," ");
                            char nb[100];
                            sprintf(nb,"%i",(*entry2)->data.value.integer);
                            mystr_add(result, nb);
                            mystr_add(result, " ");
                        }
                        else if((*entry2)->data.type==HASHMAP_TYPE_DOUBLE)
                        {
                            mystr_add(result," ");
                            char nb[100];
                            sprintf(nb,"%lf",(*entry2)->data.value.flottant);
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

t_hashmap* JSON_parse(char* text)
{
    int i=0,len=strlen(text);

    for(;i<len;i++)
    {

    }
}

int analyseJSON(char *text)
{
    int i=0,indiceNb=0, len=strlen(text), nbAccolade=0, nbCrochet=0, nbGuillemets=0,niveau=0,
        startValue=0,lenValue=0, nbVal=0, sortieAccolade=0,virgule=0,deuxPoint=0,point=1;
    char nb[100];
    for(;i<99;i++)
        nb[i]=' ';
    nb[99]='\0';
    if(len==0)
        return -1;
    for(i=0;i<len;i++)
    {
        while((text[i]==' ' || text[i]=='\n' || text[i]=='\t') && i<len && startValue==0)
        {
            i++;
            if(indiceNb)
            {
                indiceNb =0;
                nbVal++;
            }
        }
        char c = text[i];
        if(startValue)
            lenValue++;
        if(c=='{')
        {
            if(sortieAccolade && !virgule)
                return -1;
            nbAccolade++;
            niveau++;
            sortieAccolade=0;
            virgule=0;
        }
        else if(c=='}')
        {
            if(virgule)
                return -1;
            if(niveau==2 && nbVal%2!=0)
                return -1;
            nbAccolade--;
            niveau--;
            sortieAccolade=1;
        }
        else if(c=='[')
        {
            if(niveau!=1)
                return -1;
            if(!deuxPoint)
               return -1;
            deuxPoint=0;
            nbCrochet++;
            sortieAccolade=0;
            virgule=0;
        }
        else if(c==']')
        {
            if(virgule)
                return -1;
            nbCrochet--;
        }
        else if(c==':')
        {
            if(deuxPoint)
                return -1;
            if(nbVal%2==0 && niveau==2)
                return -1;
            deuxPoint=1;
        }
        else if(isdigit(c))
        {
            if(niveau==2 && nbVal%2==1 && deuxPoint)
            {
                deuxPoint=0;
                nb[indiceNb]=c;
                indiceNb++;
            }
            else if(indiceNb!=0)
            {
                nb[indiceNb]=c;
                indiceNb++;
            }
            else if(startValue==0)
                return -1;
        }
        else if(c=='.')
        {
            if(point && indiceNb)
                return -1;
            if(indiceNb!=0)
            {
                nb[indiceNb]=c;
                indiceNb++;
                point=1;
            }
        }
        else if(c=='\"')
        {
            nbGuillemets++;
            if(nbGuillemets%2==1)
            {
                deuxPoint=0;
                startValue=1;
                lenValue=0;
            }
            else
            {
                startValue=0;
                if(lenValue==0)
                    return -1;
                if(niveau==2)
                    nbVal++;
            }

        }
        else if(c==',')
        {
            if(virgule)
                return -1;
            virgule=1;
        }
        else if(!startValue)
            return -1;
    }
    if(nbAccolade || nbCrochet || nbGuillemets%2)
        return -1;

    return 0;
}
