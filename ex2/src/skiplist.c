#include"../header/skip_list.h"

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

size_t randomLevel()
{
    size_t level = 1;

    srand(time(NULL));
    while((rand() % 2) == 0 && level < MAX_HEIGHT){ level += 1; }

    return level;
}

Node* create_head_node()
{
    Node *head_node = (Node*)malloc(sizeof(Node));

    head_node->next = (Node**)malloc(sizeof(Node*));
    head_node->size = 1;
    head_node->item = NULL;

    return head_node;
}

void extended_head_node(Node *head, size_t size)
{
    Node** new_node = (Node**)realloc(head->next, sizeof(Node*) * size);
    
    head->next = new_node;
}

Node* create_node(void *element, size_t random_level)
{
    Node *new_node = (Node*)malloc(sizeof(Node));

    new_node->next = (Node**)malloc(sizeof(Node*));
    new_node->size = random_level;
    new_node->item = element;

    return new_node;
}

SkipList* create_skip_list(comparator compare)
{
    SkipList *skip_list = (SkipList*)malloc(sizeof(SkipList));

    skip_list->head = create_head_node();
    skip_list->compare = compare;
    skip_list->max_level = 1;

    return skip_list;
}

void insert_skip_list(SkipList* list, void *element)
{
    Node* new_node = (element, randomLevel());
    if(new_node->size > list->max_level)
    { 
        list->max_level = new_node->size; 
        extended_head_node(list->head, new_node->size + 1);
    }

    Node* x = list->head;
    for(size_t i = list->max_level; i >= 0; i--)
    {
        if(x->next[i] == NULL || list->compare(element, x->next[i]->item))
        {
            if(i < new_node->size)
            {
                new_node->next[i] = x->next[i];
                x->next[i] = new_node;
            }
        }
        else
        {
            x = x->next[i];
            i++;
        }
    }
}

void* search_skip_list(SkipList* list, void *element)
{
    Node *x = list->head;
    for(size_t i = list->max_level; i >= 0; i--)
    {
        while(x->next[i] != NULL && list->compare(x->next[i]->item, element) < 0)
        {
            x = x->next[i];
        }
    }
    
    x = x->next[0];
    if(x != NULL && list->compare(x->item, element) == 0){ return x->item; }
    
    return NULL;
}

void delete_skip_list(SkipList* list)
{
    Node *current_node = list->head;
    Node *next_node;

    while(current_node->next[0] != NULL)
    {
        next_node = current_node->next[0];

        free(current_node);
        current_node = next_node;
    }
}