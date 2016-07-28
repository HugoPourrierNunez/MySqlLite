#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

t_list_chain* list_chain_create(void* value)
{
    t_list_chain *s = (t_list_chain*) malloc(sizeof(t_list_chain));
    s->value=value;
    s->next=0;
    return s;
}


t_list_chain* list_chain_create_with_next(void* value, t_list_chain *n)
{
    t_list_chain *s = (t_list_chain*) malloc(sizeof(t_list_chain));
    s->value=value;
    s->next=n;
    return s;
}

unsigned int list_chain_length(t_list_chain* maillon)
{
    unsigned int i=1;
    t_list_chain m = {0,maillon->next};
    while(m.next!=0)
    {
        m = *(m.next);
        i++;
    }
    return i;
}


void list_display(t_list_chain* maillon)
{
	while(maillon)
    {
        printf("%d ",maillon->value);
        maillon=maillon->next;
    }
    printf("\n");
}

void list_free(t_list_chain* head)
{
	t_list_chain *curr = 0;

	while ((curr = head) != 0) {
			head = head->next;
			free(curr);
	}
}

t_list_chain* list_append(t_list_chain* list, void* value)
{
    if(!list)
        return list_chain_create(value);
    t_list_chain *t=list;
    while(t->next!=0)
        t = t->next;
    t->next=list_chain_create(value);
    return list;
}

t_list_chain* list_insert(t_list_chain* list, unsigned int index, void* value)
{
    if(index==0)
    {
        t_list_chain *m = (t_list_chain*)malloc(sizeof(t_list_chain));
        m->next = list;
        m->value = value;
        return m;
    }
    t_list_chain *prev = list;
    while(index-1 && prev)
    {
        prev=prev->next;
        index--;
    }
    if(!(index-1))
    {
        t_list_chain *result = (t_list_chain*)malloc(sizeof(t_list_chain));
        result->next = prev->next;
        result->value = value;
        prev->next=result;
    }
    return list;
}

void list_append2(t_list_chain** list, void* value)
{
    while(*list)
        list = &(*list)->next;
    *list=list_chain_create(value);
}

void list_insert2(t_list_chain** list, unsigned int index, void* value)
{
    while(*list && index)
    {
        index--;
        list = &(*list)->next;
    }
    if(!index)
    {
        t_list_chain* l = list_chain_create(value);
        l->next=(*list);
        (*list)=l;
    }
}

void list_remove2(t_list_chain** list, unsigned int index)
{
    while(*list && index)
    {
        index--;
        list = &(*list)->next;
    }
    if(!index)
    {
        t_list_chain* l = (*list);
        (*list)=(*list)->next;
        free(l);
    }
}

void list_update(t_list_chain* list, unsigned int index, void* value)
{
    while(index && list)
    {
        list=list->next;
        index--;
    }
    if(!(index))
         list->value=value;
}

t_list_chain* list_remove(t_list_chain* list, unsigned int index)
{
    t_list_chain* list2=list;
    if(index==0)
    {
        t_list_chain *rm = list;
        list = list->next;
        free(rm);
        return list;
    }
    int i=0;
    while(i<index-1 && list)
    {
        list=list->next;
        i++;
    }
    if(i==index && list->next)
    {
        t_list_chain *rm = list->next;
        list->next=list->next->next;
        free(rm);
    }
    return list2;
}


void linked_stack_push(t_list_chain **stack, void* value)
{
    t_list_chain* l = list_chain_create_with_next(value,*stack);
    (*stack) = l;
}

void* linked_stack_pop(t_list_chain **stack)
{
    if(!*stack)
        return -1;
    t_list_chain* l = (*stack);
    void* value = l->value;
    (*stack)=(*stack)->next;
    free(l);
    return value;
}

void* linked_stack_peek(t_list_chain **stack)
{
    if(!*stack)
        return -1;
    return (*stack)->value;
}

void linked_file_push(t_list_chain **stack, void* value)
{
    t_list_chain* l = list_chain_create_with_next(value,*stack);
    (*stack) = l;
}

void* linked_file_pop(t_list_chain **stack)
{
    if(!*stack)
        return -1;
    t_list_chain* l = (*stack);
    void* value = l->value;
    (*stack)=(*stack)->next;
    free(l);
    return value;
}

void* linked_file_peek(t_list_chain **stack)
{
    if(!*stack)
        return -1;
    return (*stack)->value;
}


/*void list_revert_inside(t_list_chain** list)
{
    t_list_chain *cp = *list;
    if(cp->next)
    {
        t_list_chain *l = cp;
        list_revert_inside(&l2);
        l2->next=l;
    }
    else
    {
        //l2->next=l;
    }
}*/



/*void list_revert_inside2(t_list_chain* list)
{
    t_list_chain *cp = *list;
    if(cp->next)
    {
        t_list_chain *l = cp;
        t_list_chain *l2 = cp->next;
        list_revert_inside(&(l2));
        l2->next=l;

    }
    else
    {
        //(*list)=list_chain_create(1);
    }
    else
    {
        t_list_chain *l = cp;
        t_list_chain *l2 = cp->next;
        l2->next=l;
        list=&l2;
    }
*/

/*
int linked_list_get_by_position(t_list_chain* maillon, unsigned int index, int* found)
{
    int i;
    t_list_chain m = {maillon->value,maillon->next};
    for(i=0;m.next!=0 && i<index;i++)
    {
        m = *(m.next);
    }
    if(i==index)
    {
        *found=1;
        return m.value;
    }
    *found = 0;
    return 0;
}

int linked_list_get_by_value(t_list_chain* maillon, int value)
{
    int i;
    t_list_chain m = {maillon->value,maillon->next};
    for(i=0;m.next!=0;i++)
    {
        if(m.value == value)
            return i;
        m = *(m.next);
    }
    return -1;
}

void linked_list_remove_value(t_list_chain** list, int value)
{
    int i;
    t_list_chain *m = *list;
    for(i=0;m->next!=0 && m->value!=value;i++)
    {
        m = m->next;
    }
    if(m->value==value)
    {
        linked_list_remove_indice(list, i);
    }
}

void linked_list_remove_all(t_list_chain** list, int value)
{
    int i;
    t_list_chain *m = *list;
    for(i=0;m->next!=0;i++)
    {
        if(m->next!=0)
        {
            linked_list_remove_indice(list, i);
        }
        m = m->next;
    }
}*/
