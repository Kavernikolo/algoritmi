#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
 
#define MAX_HEIGHT 6
 
typedef struct Node 
{
    int key;
    int value;
    struct Node **forward;
} Node;
 
typedef struct SkipList 
{
    int level;
    unsigned int size;
    struct Node *header;
} SkipList;
 
SkipList *SkipList_init(SkipList *list) 
{
    int i;
    Node *header = (Node *) malloc(sizeof(struct Node));
    list->header = header;
    header->key = INT_MAX;
    header->forward = (Node **) malloc(sizeof(Node*) * (MAX_HEIGHT + 1));
    for (i = 0; i <= MAX_HEIGHT; i++){ header->forward[i] = list->header; }
 
    list->level = 1;
    list->size = 0;
 
    return list;
}
 
static int rand_level() 
{
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < MAX_HEIGHT){ level++; }
    return level;
}
 
int SkipList_insert(SkipList *list, int key, int value) 
{
    Node *update[MAX_HEIGHT + 1];
    Node *x = list->header;
    int i, level;
    for (i = list->level; i >= 1; i--) 
	{
        while (x->forward[i]->key < key){ x = x->forward[i]; }
        update[i] = x;
    }
    x = x->forward[1];
 
    if (key == x->key) 
	{
        x->value = value;
        return 0;
    } 
	else 
	{
        level = rand_level();
        if (level > list->level) 
		{
            for (i = list->level + 1; i <= level; i++){ update[i] = list->header; }
            list->level = level;
        }
 
        x = (Node *) malloc(sizeof(Node));
        x->key = key;
        x->value = value;
        x->forward = (Node **) malloc(sizeof(Node*) * (level + 1));
        for (i = 1; i <= level; i++) 
		{
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
    return 0;
}
 
Node *SkipList_search(SkipList *list, int key) 
{
    Node *x = list->header;
    int i;
    for (i = list->level; i >= 1; i--) 
	{
        while (x->forward[i]->key < key){ x = x->forward[i]; }
    }
    if (x->forward[1]->key == key){ return x->forward[1]; } 
	else{ return NULL; }
    return NULL;
}
 
static void SkipList_node_free(Node *x) 
{
    if (x) 
	{
        free(x->forward);
        free(x);
    }
}
 
int SkipList_delete(SkipList *list, int key) 
{
    int i;
    Node *update[MAX_HEIGHT + 1];
    Node *x = list->header;
    for (i = list->level; i >= 1; i--) 
	{
        while (x->forward[i]->key < key){ x = x->forward[i]; }
        update[i] = x;
    }
 
    x = x->forward[1];
    if (x->key == key) 
	{
        for (i = 1; i <= list->level; i++) 
		{
            if (update[i]->forward[i] != x){ break; }
            update[i]->forward[1] = x->forward[i];
        }
        SkipList_node_free(x);
 
        while (list->level > 1 && list->header->forward[list->level] == list->header){ list->level--; }
        return 0;
    }
    return 1;
}
 
static void SkipList_dump(SkipList *list) 
{
    Node *x = list->header;
    while (x && x->forward[1] != list->header)
	{
		printf("%d[%d]->", x->forward[1]->key, x->forward[1]->value);
        x = x->forward[1];
    }
    printf("NIL\n");
}
 
int main() 
{
    int arr[] = { 3, 6, 9, 2, 11, 1, 4 }, i;
    SkipList list;
    SkipList_init(&list);
 
    printf("Insert:--------------------\n");
    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++){ SkipList_insert(&list, arr[i], arr[i]); }
    SkipList_dump(&list);
 
    printf("Search:--------------------\n");
    int keys[] = { 3, 4, 7, 10, 111 };
 
    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) 
	{
        Node *x = SkipList_search(&list, keys[i]);
        if (x){ printf("key = %d, value = %d\n", keys[i], x->value); } 
		else { printf("key = %d, not fuound\n", keys[i]); }
    }
 
    printf("Search:--------------------\n");
    SkipList_delete(&list, 3);
    SkipList_delete(&list, 9);
    SkipList_dump(&list);
 
    return 0;
}