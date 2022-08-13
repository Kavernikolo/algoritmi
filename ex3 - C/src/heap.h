#include<stdio.h>
#include<stdlib.h>

#define FALSE 0
#define TRUE 1

#define INITIAL_CAPACITY 2

#define ROOT 1

typedef struct _arrayList
{
    void **array;

    int size;
    int capacity;

    int (*compare)(void *, void *);
}arrayList;

arrayList *array_list_create(int (*compare)(void *, void *));

int array_list_is_empty(arrayList *);

size_t array_list_size(arrayList *);

void array_list_add(arrayList *, void *);

void *array_list_get(arrayList *, size_t);

void array_list_free_memory(arrayList *);

void bubbleUp(arrayList *);

int getParentIndex(int);
void getParentElement(arrayList *, int);
int hasParent(int);

int getLeftIndex(int);
void getLeftElement(arrayList *, int);
int hasLeftChild(arrayList *, int);

int getRightIndex(int);
void getRightElement(arrayList *, int);
int hasRightChild(arrayList *, int);

void extractMin(arrayList *);

void bubbleDown(arrayList *);

static void swap(arrayList *, int, int);

void decreaseElement(arrayList *, void *, void *);

static size_t binary_search(arrayList *, void *, size_t , size_t);
