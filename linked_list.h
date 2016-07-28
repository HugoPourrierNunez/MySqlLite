struct s_list_chain
{
    void* value;
    struct s_list_chain *next;
};

typedef struct s_list_chain t_list_chain;

t_list_chain* list_chain_create(void* value);

unsigned int list_chain_length(t_list_chain* maillon);

void list_display(t_list_chain* maillon);

void list_free(t_list_chain* maillon);

t_list_chain* list_append(t_list_chain* list, void* value);
t_list_chain* list_insert(t_list_chain* list, unsigned int index, void* value);
void list_update(t_list_chain* list, unsigned int index, void* value);
t_list_chain* list_remove(t_list_chain* list, unsigned int index);
void list_revert_inside(t_list_chain** list);

void list_insert2(t_list_chain** list, unsigned int index, void* value);
void list_append2(t_list_chain** list, void* value);

t_list_chain* list_chain_create_with_next(void* value, t_list_chain *n);

void linked_stack_push(t_list_chain **stack, void* value);
void* linked_stack_pop(t_list_chain **stack);
void* linked_stack_peek(t_list_chain **stack);

/*
// Return -1 if not found.
int linked_list_get_by_value(t_list_chain* maillon, int value);
// Return value, set found to 0 if not found, another value if found.
int linked_list_get_by_position(t_list_chain* maillon, unsigned int index, int* found);
//Add an s_list_chain at the end of the linked_list
void linked_list_append(t_list_chain** list, int value);
//Insert at any place between 0 and linked_list_size()
void linked_list_insert(t_list_chain** list, int index, int value);
// Remove the s_list_chain at index position, if index is in [0, linked_list_size()]
void linked_list_remove_indice(t_list_chain** list, unsigned int index);
//Remove first s_list_chain containing the value value.
void linked_list_remove_value(t_list_chain** list, int value);
// Remove all s_list_chain containing the value value.
void linked_list_remove_all(t_list_chain** list, int value);
*/
