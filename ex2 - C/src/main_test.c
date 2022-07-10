#include<stdio.h>
#include<stdlib.h>

#include<limits.h>

#define MAX_LEVEL 6

typedef struct skiplist
{
    size_t list_level;

    struct node *head;

}skiplist;

typedef struct node
{
    size_t level;

    size_t key;
    void *value;

    struct node **up;
    //struct node **down;
    struct node **next;
    //struct node **previous;
}node;

static int rand_level()
{
    int level = 1;

    while(rand() < 0.5 && level < MAX_LEVEL){ level += 1; }

    return level;
}

skiplist *init(skiplist *list)
{
    node *head = (node*)malloc(sizeof(struct node));

    list->head = head;
    head->key = INT_MAX;
    head->up = (node**)malloc(sizeof(node) * (MAX_LEVEL + 1));

    int i = 0;
    while(i < MAX_LEVEL)
    {
        head->up[i] = list->head;
    
        i++;
    }

    list->list_level = 1;

    return list;
}

void insert(skiplist *list, size_t key, size_t value)
{
    int level = rand_level();

    node *x = list->head;

    node *new_head[MAX_LEVEL + 1];

    int i;
    for(i = list->list_level; i >= 1; i--)
    {
        while(x->up[i]->key < key){ x = x->up[i];}
        
        new_head[i] = x;
    }
    x = x->up[1];

    if(key == x->key)
    {
        x->value = value;
        
        return 0;
    }
    else
    {
        if(level > list->list_level)
        { 
            for (i = list->list_level + 1; i <= level; i++)
            {
                new_head[i] = list->head;
            }
            list->list_level = level;
        }

        x = (node*)malloc(sizeof(node));
            x->key = key;
            x->value = value;
            x->up = (node**)malloc(sizeof(node) * (level + 1));
    
        for(i = 1; i < level; i++)
        {
            x->up[i] = new_head[i]->up[i];
            new_head[i]->up[i] = x;
        }
    }
    return 0;
}

node *find(skiplist *list, size_t key)
{
    node *x = list->head;

    int i;
    for(i = list->list_level; i >= 1; i--)
    {
        while(i < x->up[i]->key < key){ x = x->up[i]; }
    }

    if(x->up[1]->key == key){ return x->up[1]; }
    else{ return NULL; } 

    return NULL;
}

int delete(skiplist *list, size_t key)
{
    node *x = list->head;
    node *new_node[MAX_LEVEL + 1];

    int i;
    for(i = list->list_level; i >= 1; i--)
    {
        while(x->up[i]->key < key){ x = x->up[i]; }
        new_node[i] = x;
    }

    x = x->up[1];
    if(x->key == key)
    {
        for(i = 1; i < list->list_level; i++)
        {
            if(new_node[i]->up[i] != x){ break; }
            
            new_node[i]->up[1] = x->up[i];
        }
        node_free(x);

        while(list->list_level > 1 && (list->head->up[list->list_level] == list->list_level)){ list->list_level--; }

        return 0;
    }
}

static void node_free(node *x)
{
    if(x)
    {
        free(x->up);
        free(x);
    }
}