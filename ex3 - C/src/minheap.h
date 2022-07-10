#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <assert.h>

typedef struct _minHeap
{
    void **array;

    int size;
    int capacity;

    int(*compare)(void*, void*);
}minHeap;

minHeap *heap_create(int (*compare)(void *, void *), int maxSize);
void heap_free_memory(minHeap *heap);
void heap_add(minHeap *heap, void *element);
void* heap_remove(minHeap* heap); 
int heap_empty(minHeap *heap);
int heap_size(minHeap *heap);
static void swap(minHeap *heap, int x, int y);