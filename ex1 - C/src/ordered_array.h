#include <stdlib.h>
#include <stdio.h>

#define INITIAL_CAPACITY 2

#define K 0

#define TRUE 1
#define FALSE 0

typedef struct _orderedArray
{
    void **array;

    int size;
    int capacity;

    int (*compare)(void*, void*);
}orderedArray;

orderedArray *ordered_array_create(int (*compare)(void *, void *));

int ordered_array_is_empty(orderedArray *);

size_t ordered_array_size(orderedArray *);

void ordered_array_add(orderedArray *, void *);
void *ordered_array_get(orderedArray *, size_t);
void ordered_array_free_memory(orderedArray *);

void quick_binary_insertion_sort(orderedArray *);