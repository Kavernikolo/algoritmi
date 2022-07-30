#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
   
#include "ordered_array.h"

#define INITIAL_CAPACITY 2

#define TRUE 1
#define FALSE 0

static size_t binarySearch(OrderedArray *ordered_array, size_t low, size_t high, void *item);
static void insertionSort(OrderedArray *ordered_array, size_t low, size_t high);
void quick_sort(OrderedArray *orderedArray, size_t init, size_t end);
static size_t partition(OrderedArray *orderedArray, size_t init, size_t end);
static void swap(OrderedArray *array, int x, int y);

void print_array(OrderedArray *array, int index);

OrderedArray *ordered_array_create(int (*precedes)(void *, void *))
{
    if(precedes == NULL)
    {
        fprintf(stderr, "ordered_array_create: precedes parameter cannot be NULL");
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
    ordered_array->precedes = precedes;

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

static size_t binarySearch(OrderedArray *ordered_array, size_t low, size_t high, void *item)
{
    size_t mid;

    if(low == high){ return low; }

    mid = low + ((high - low) / 2);

    if((*(ordered_array->precedes))((ordered_array->array)[mid], item)){ return binarySearch(ordered_array, mid + 1, high, item); }
    if((*(ordered_array->precedes))(item, (ordered_array->array)[mid])){ return binarySearch(ordered_array, low, mid, item); }

    return mid;
}

static void insertionSort(OrderedArray *ordered_array, size_t low, size_t high)
{
    size_t index = 0, i = 0;
    void *tmp;

    for (i = low + 1; i <= high; i++)
    {
        tmp = (ordered_array->array)[i];
        index = binarySearch(ordered_array, low, i, tmp);

        if (index > high)
        {
        fprintf(stderr, "insertion_sort: index out of bounds of the array");
        exit(EXIT_FAILURE);
        }

        if (index < i)
        {
            memmove((ordered_array->array) + index + 1, (ordered_array->array) + index, sizeof(void *) * (i - index));
            (ordered_array->array)[index] = tmp;
        }
    }	
}

void quick_binary_insertion_sort(OrderedArray *ordered_array)
{
    if(ordered_array == NULL)
    {
        fprintf(stderr, "merge_binary_insertion_sort: ordered_array parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }

    if((ordered_array->size) <= K){ quick_sort(ordered_array, 0, (ordered_array->size) - 1); }
    else{ quick_sort(ordered_array, 0, (ordered_array->size) - 1); }
}

void quick_sort(OrderedArray *orderedArray, size_t init, size_t end)
{
    if(init < end)
    {
        //if(((end - init) + 1) <= K){ insertionSort(orderedArray, init, end); }
        //else
        //{
            size_t p = partition(orderedArray, init, end);

            quick_sort(orderedArray, init, p);
            quick_sort(orderedArray, p + 1, end);
        //}
    }
}

size_t median(OrderedArray *orderedArray, size_t from, size_t to)
{
    //printf("From :%li\n", from);
    //printf("To :%li\n", to);
    size_t med = from + ((to - from) / 2);
    //printf("Median :%li\n", med);

    if((((*(orderedArray->precedes))((orderedArray->array)[from], (orderedArray->array)[med]) <= 0) && ((*(orderedArray->precedes))((orderedArray->array)[med], (orderedArray->array)[to]) <= 0)) || (((*(orderedArray->precedes))((orderedArray->array)[to], (orderedArray->array)[med]) <= 0) && ((*(orderedArray->precedes))((orderedArray->array)[med], (orderedArray->array)[from]) <= 0))){ return med; }
    else if((((*(orderedArray->precedes))((orderedArray->array)[med], (orderedArray->array)[from]) <= 0) && ((*(orderedArray->precedes))((orderedArray->array)[from], (orderedArray->array)[to]) <= 0)) || (((*(orderedArray->precedes))((orderedArray->array)[to], (orderedArray->array)[from]) <= 0) && ((*(orderedArray->precedes))((orderedArray->array)[from], (orderedArray->array)[med]) <= 0))){ return from; }
    else if((((*(orderedArray->precedes))((orderedArray->array)[med], (orderedArray->array)[to]) <= 0) && ((*(orderedArray->precedes))((orderedArray->array)[to], (orderedArray->array)[from]) <= 0)) || (((*(orderedArray->precedes))((orderedArray->array)[from], (orderedArray->array)[to]) <= 0) && ((*(orderedArray->precedes))((orderedArray->array)[to], (orderedArray->array)[med]) <= 0))){ return to; }
}

static size_t partition(OrderedArray *orderedArray, size_t init, size_t end)
{
    printf("Init :%li\n", init);
    printf("End :%li\n", end);

    size_t pivot = (init / 2) + (end / 2); 
    printf("Pivot :%li\n", pivot);

    void *value = ordered_array_get(orderedArray, pivot);

    while(init < end)
    {
        do{ init++; }while((*(orderedArray->precedes))(ordered_array_get(orderedArray, init), value) < 0);
        do{ end--; }while((*(orderedArray->precedes))(ordered_array_get(orderedArray, end), value) > 0);
        
        swap(orderedArray, init, end);
    }
    return init;
}

static void swap(OrderedArray *array, int x, int y)
{
    void *tmp = ordered_array_get(array, x);
    (array->array)[x] = ordered_array_get(array, y);
    (array->array)[y] = tmp;
}