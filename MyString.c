#include "MyString.h"

void mystr_add(t_mystr *mystr, const char* text)
{
    if(!mystr || !text || strlen(text)==0)
        return;
    int i,len=strlen(text);
    if(len+mystr->length>=mystr->maxSize)
    {
        char *new_str = malloc(len+mystr->maxSize);
        for(i=0;i<mystr->length;i++)
        {
            new_str[i]=mystr->text[i];
        }
        free(mystr->text);
        mystr->text=new_str;
    }
    mystr->length--;
    for(i=0;i<len;i++)
    {
        mystr->text[mystr->length+i]=text[i];
    }
    mystr->length+=len+1;
    mystr->text[mystr->length-1]='\0';

}

t_mystr* mystr_create(int maxSize)
{
    if(maxSize<1)
        return NULL;
    t_mystr *mystr = malloc(sizeof(t_mystr));
    mystr->length=1;
    mystr->maxSize=maxSize;
    mystr->text= malloc(maxSize*sizeof(char));
    mystr->text[0]='\0';
    return mystr;
}

void mystr_delete(t_mystr* mystr)
{
    free(mystr->text);
    free(mystr);
}

void mystr_remove(t_mystr* mystr, unsigned int nb)
{
    if(mystr->length<nb+1 || nb==0)
        return;
    mystr->text[mystr->length-nb-1]='\0';
    mystr->length-=nb;
}
