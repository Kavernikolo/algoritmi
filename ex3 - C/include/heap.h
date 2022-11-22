#include<stdio.h>
#include<stdlib.h>

#define INITIAL_CAPACITY 2

#define FALSE 0
#define TRUE 1

#define ROOT 1

typedef struct _arrayList
{
    void **array;

    int size;
    int capacity;

    int(*compare)(void *, void *);
}arrayList;

arrayList *array_list_create(int (*compare)(void *, void *));

int array_list_is_empty(arrayList *);

size_t array_list_size(arrayList *);

void array_list_add(arrayList *, void *);

void *array_list_get(arrayList *, size_t);

void array_list_free_memory(arrayList *);