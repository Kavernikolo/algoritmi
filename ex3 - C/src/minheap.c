#include<stdio.h>
#include<stdlib.h>

#include"minheap.h"

#define ROOT 0

#define PARENT(i) (i / 2)

#define LEFT_CHILD(i) (i * 2)
#define RIGHT_CHILD(i) ((i * 2) + 1)

#define TRUE 1
#define FALSE 0

minHeap *heap_create(int (*compare)(void *, void *), int maxSize)
{
    if (compare == NULL)
    {
        fprintf(stderr, "heap_create: compare parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }

    minHeap *heap = (minHeap *)malloc(sizeof(minHeap));

    if (heap == NULL)
    {
        fprintf(stderr, "heap_create: unable to allocate memory for the ordered array");
            exit(EXIT_FAILURE);
    }

    heap->array = (void **)malloc(maxSize * sizeof(void *));

    if (heap->array == NULL)
    {
        fprintf(stderr, "heap_create: unable to allocate memory for the internal array");
            exit(EXIT_FAILURE);
    }
    heap->size = 0;
    heap->capacity = maxSize + 1;

    return (heap);
}

void heap_free_memory(minHeap *heap)
{
    if (heap == NULL)
    {
        fprintf(stderr, "heap_free_memory: heap parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    free(heap->array);
    free(heap);
}

void heap_add(minHeap *heap, void *element)
{
    if(heap->size + 1 >= heap->capacity){ return 1; }

    heap->size += 1;

    int i = heap->size;

    heap->array[i] = element;

    int parent = (i % 2 == 0) ? (i / 2) : (i - 1) / 2;
    while(parent > 0 && heap->compare(heap->array[parent], heap->array[i]) > 0)
    {
        swap(heap, parent, i);

        i == parent;

        parent = (i % 2 == 0) ? (i / 2) : (i - 1) / 2; 
    }
}

void* heap_remove(minHeap* heap) 
{
    void* min;

    if(heap->size <= 0){ return NULL; }
    else{ min = heap->array[1]; }

    /* swap replace min with last element */
    heap->array[1] = heap->array[heap->size];
    heap->size -= 1;

    /* trickle down */
    int i = 1;
    int left = i * 2;
    int right = left + 1;
    while(left <= heap->size && right <= heap->size && (heap->compare(heap->array[i], heap->array[left]) > 0 || heap->compare(heap->array[i], heap->array[right]) > 0)) 
    {
        int minChild;
        if(heap->compare(heap->array[right],  heap->array[left]) < 0){ minChild = right; }
        else{ minChild = left; }
        
        /* swap min child with parent */
        void* temp = heap->array[minChild];
        heap->array[minChild] = heap->array[i];
        heap->array[i] = temp;
        
        /* reset variables */
        i = minChild;
        left = i * 2;    
        right = left + 1;
    }

    /* in case the tree is odd */
    if(left <= heap->size && heap->compare(heap->array[i], heap->array[left]) > 0) {
        /* swap min child with parent */
        void* temp = heap->array[left];
        heap->array[left] = heap->array[i];
        heap->array[i] = temp;
    }
    return min;
}

int heap_empty(minHeap *heap){ return heap->size == 0; }
int heap_size(minHeap *heap){ return heap->size; }

static void swap(minHeap *heap, int x, int y)
{
    void *tmp = (heap->array)[x];
    (heap->array)[x] = (heap->array)[y];
    (heap->array)[y] = tmp;
}