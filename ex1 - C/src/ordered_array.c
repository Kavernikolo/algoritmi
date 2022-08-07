#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
   
#include "ordered_array.h"


#define INITIAL_CAPACITY 2

static size_t binarySearch(OrderedArray *ordered_array, void *element, size_t init, size_t end, int (*compare)(void *, void *));
static void insertionSort(OrderedArray *ordered_array, size_t init, size_t end, int (*compare)(void *, void *));
void quick_sort(OrderedArray *orderedArray, size_t init, size_t end, int (*compare)(void *, void *));
static size_t partition(OrderedArray *orderedArray, size_t init, size_t end, int (*compare)(void *, void *));
static void swap(OrderedArray *array, int x, int y);

void print_array(OrderedArray *array, int index);

OrderedArray *ordered_array_create(int (*compare)(void *, void *))
{
    if(compare == NULL)
    {
        fprintf(stderr, "ordered_array_create: compare parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }
    
    OrderedArray *ordered_array = (OrderedArray *)malloc(sizeof(OrderedArray));
    if(ordered_array == NULL)
    {
        fprintf(stderr, "ordered_array_create: unable to allocate memory for the ordered array");
            exit(EXIT_FAILURE);
    }
    
    ordered_array->array = (void **)malloc(INITIAL_CAPACITY * sizeof(void *));
    if(ordered_array->array == NULL)
    {
        fprintf(stderr, "ordered_array_create: unable to allocate memory for the internal array");
            exit(EXIT_FAILURE);
    }
    ordered_array->size = 0;
    ordered_array->capacity = INITIAL_CAPACITY;

    return (ordered_array);
}

int ordered_array_is_empty(OrderedArray *ordered_array)
{
    if(ordered_array == NULL)
    {
        fprintf(stderr, "ordered_array_is_empty: ordered_array parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }
    if(ordered_array->size == 0){ return TRUE; }
  
    return FALSE;
}

size_t ordered_array_size(OrderedArray *ordered_array)
{
    if(ordered_array == NULL)
    {
        fprintf(stderr, "ordered_array_size: ordered_array parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }
    
    return (ordered_array->size);
}

void ordered_array_add(OrderedArray *ordered_array, void *element)
{
    if(ordered_array == NULL)
    {
        fprintf(stderr, "add_ordered_array_element: ordered_array parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }

    if(element == NULL)
    {
        fprintf(stderr, "add_ordered_array_element: element parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }

    if(ordered_array->size >= ordered_array->capacity)
    {
        ordered_array->array = (void **)realloc(ordered_array->array, 2 * (ordered_array->capacity) * sizeof(void *));
        if(ordered_array->array == NULL)
        {
            fprintf(stderr, "ordered_array_add: unable to reallocate memory to host the new element");
                exit(EXIT_FAILURE);
        }
        
        ordered_array->capacity = 2 * ordered_array->capacity;
    }

    (ordered_array->array)[ordered_array->size] = element;
    (ordered_array->size)++;
}

void *ordered_array_get(OrderedArray *ordered_array, size_t i)
{
    if(ordered_array == NULL)
    {
        fprintf(stderr, "ordered_array_get: ordered_array parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }
    
    if(i >= ordered_array->size)
    {
        fprintf(stderr, "ordered_array_get: Index %lu is out of the array bounds", i);
            exit(EXIT_FAILURE);
    }
    
    return (ordered_array->array)[i];
}

void ordered_array_set(OrderedArray *ordered_array, size_t to, void *element)
{
    ordered_array->array[to] = element;
}

void ordered_array_free_memory(OrderedArray *ordered_array)
{
    if(ordered_array == NULL)
    {
        fprintf(stderr, "ordered_array_free_memory: ordered_array parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }
  
    free(ordered_array->array);
    free(ordered_array);
}

void quick_binary_insertion_sort(OrderedArray *ordered_array, int (*compare)(void *, void *))
{
    if(ordered_array == NULL)
    {
        fprintf(stderr, "merge_binary_insertion_sort: ordered_array parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }

    if((ordered_array->size) <= K){ insertionSort(ordered_array, 0, (ordered_array->size) - 1, compare); }
    else{ quick_sort(ordered_array, 0, (ordered_array->size) - 1, compare); }
}

void quick_sort(OrderedArray *ordered_array, size_t init, size_t end, int (*compare)(void *, void *))
{
    if(((end - init) + 1) <= K){ insertionSort(ordered_array, init, end, compare); }

    if(init < end)
    {
            size_t p = partition(ordered_array, init, end, compare);

            quick_sort(ordered_array, init, p, compare);
            quick_sort(ordered_array, p + 1, end, compare);
    }
}

static size_t partition(OrderedArray *ordered_array, size_t init, size_t end, int (*compare)(void *, void *))
{
    size_t pivot = (init / 2) + (end / 2);
    
    void *element = ordered_array_get(ordered_array, pivot);

    init--;
    end++;

    while(TRUE)
    {
        do init++; while((*compare)(ordered_array_get(ordered_array, init), element) < 0);
        do end--; while((*compare)(ordered_array_get(ordered_array, end), element) > 0);
        
        if(init >= end){ return end; }
        swap(ordered_array, init, end);
    }
}

static size_t binarySearch(OrderedArray *ordered_array, void *element, size_t init, size_t end, int (*compare)(void *, void *))
{
    if(end <= init)
    {
        if((*compare)(ordered_array_get(ordered_array, init), element) < 0){ return init; }
        else{ return init + 1; }
    }

    size_t middle = (init / 2) + (end /2);

    size_t compare_element = (*compare)(ordered_array_get(ordered_array, middle), element);

    if(compare_element < 0){ return binarySearch(ordered_array, element, init, middle - 1, compare); }
    else if(compare_element > 0){ return binarySearch(ordered_array, element, middle + 1, end, compare); }
    else return middle;
}

static void insertionSort(OrderedArray *ordered_array, size_t init, size_t end, int (*compare)(void *, void *))
{
    for (size_t i = init + 1; i < end; i++)
    {
        size_t j = i - 1;

        void *element = ordered_array_get(ordered_array, i);

        size_t gps = binarySearch(ordered_array, element, init, j, compare);

        while(j >= gps && ((*compare)(ordered_array_get(ordered_array, j), element) > 0))
        {
            ordered_array_set(ordered_array, j+1, ordered_array_get(ordered_array, j));
            j--;
        }
        ordered_array_set(ordered_array, j + 1, element);
    }
    
}

static void swap(OrderedArray *array, int x, int y)
{
    void *tmp = ordered_array_get(array, x);
    (array->array)[x] = ordered_array_get(array, y);
    (array->array)[y] = tmp;
}