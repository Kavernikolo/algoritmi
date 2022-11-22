#include<stdio.h>
#include<stdlib.h>

#define MAX_HEIGHT 2

typedef size_t (*comparator)(const void*, const void*);

typedef struct _SkipList SkipList;
typedef struct _Node Node;

struct _SkipList
{
    Node *head;
    
    size_t max_level;

    //int (*compare)(void *, void *);
    comparator compare;
};

struct _Node
{
    Node **next;
    
    size_t size;
    void *item;
};

SkipList* create_skip_list(comparator compare);

void insert_skip_list(SkipList* list, void *element);
void* search_skip_list(SkipList* list, void *element);
void delete_skip_list(SkipList* list);
