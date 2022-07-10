#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include"ordered_array.h"

static void insertion_sort(orderedArray *orderedArray, size_t init, size_t end);
static size_t binary_search(orderedArray *orderedArray, int init, int end, void *element);
void quick_sort(orderedArray *orderedArray, size_t init, size_t end);
static size_t partition(orderedArray *orderedArray, size_t init, size_t end);
static void swap(orderedArray *array, int x, int y);

orderedArray *ordered_array_create(int (*compare)(void *, void *))
{
    if (compare == NULL)
    {
        fprintf(stderr, "ordered_array_create: compare parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    orderedArray *ordered_array = (orderedArray *)malloc(sizeof(orderedArray));
    if (ordered_array == NULL)
    {
        fprintf(stderr, "ordered_array_create: unable to allocate memory for the ordered array");
        exit(EXIT_FAILURE);
    }
    ordered_array->array = (void **)malloc(INITIAL_CAPACITY * sizeof(void *));
    if (ordered_array->array == NULL)
    {
        fprintf(stderr, "ordered_array_create: unable to allocate memory for the internal array");
        exit(EXIT_FAILURE);
    }
    ordered_array->size = 0;
    ordered_array->capacity = INITIAL_CAPACITY;

    return (ordered_array);
}

int ordered_array_is_empty(orderedArray *ordered_array)
{
    if (ordered_array == NULL)
    {
        fprintf(stderr, "ordered_array_is_empty: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    if (ordered_array->size == 0)
        return (1);
    return (0);
}

size_t ordered_array_size(orderedArray *ordered_array)
{
    if (ordered_array == NULL)
    {
        fprintf(stderr, "ordered_array_size: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    return (ordered_array->size);
}

void ordered_array_add(orderedArray *ordered_array, void *element)
{
    if (ordered_array == NULL)
    {
        fprintf(stderr, "add_ordered_array_element: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }

    if (element == NULL)
    {
        fprintf(stderr, "add_ordered_array_element: element parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }

    if (ordered_array->size >= ordered_array->capacity)
    {
        ordered_array->array = (void **)realloc(ordered_array->array, 2 * (ordered_array->capacity) * sizeof(void *));
        if (ordered_array->array == NULL)
        {
        fprintf(stderr, "ordered_array_add: unable to reallocate memory to host the new element");
        exit(EXIT_FAILURE);
        }
        ordered_array->capacity = 2 * ordered_array->capacity;
    }

    (ordered_array->array)[ordered_array->size] = element;
    (ordered_array->size)++;
}

void *ordered_array_get(orderedArray *ordered_array, size_t i)
{
    if (ordered_array == NULL)
    {
        fprintf(stderr, "ordered_array_get: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    if (i >= ordered_array->size)
    {
        fprintf(stderr, "ordered_array_get: Index %lu is out of the array bounds", i);
        exit(EXIT_FAILURE);
    }
    return (ordered_array->array)[i];
}

void ordered_array_free_memory(orderedArray *ordered_array)
{
    if (ordered_array == NULL)
    {
        fprintf(stderr, "ordered_array_free_memory: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    free(ordered_array->array);
    free(ordered_array);
}

void quick_binary_insertion_sort(orderedArray *ordered_array)
{
    if(ordered_array == NULL)
    {
        fprintf(stderr, "quick_binary_insertion_sort: ordered_array parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }

    if(ordered_array->size <= K){ insertion_sort(ordered_array, 0, (ordered_array->size) - 1); }
    else{ quick_sort(ordered_array, 0, (ordered_array->size) - 1); }
}

static void insertion_sort(orderedArray *orderedArray, size_t init, size_t end)
{
    size_t i = init +1;
    while (i <= end)
    {
        size_t j = i - 1;

        void *tmp = (orderedArray->array)[i];

        int index = binary_search(orderedArray, 0, j, tmp);

        while (j >= index)
        {
            memmove((orderedArray->array) + index + 1, (orderedArray->array) + index, sizeof(void *) * (j - index));
            (orderedArray->array)[index] = tmp;
        }

        if(index > end)
        {
            fprintf(stderr, "insertion_sort: index out of bounds of the array");
            exit(EXIT_FAILURE);
        }
    }
}

static size_t binary_search(orderedArray *orderedArray, int init, int end, void *element)
{
    if(init <= end)
    {
        int middle = init + (end - init) / 2;

        if((*(orderedArray->compare))((orderedArray->array)[middle], element)){ return binary_search(orderedArray, middle + 1, end, element); }
        else if((*(orderedArray->compare))(element, (orderedArray->array)[middle])){ return binary_search(orderedArray, init, middle - 1, element);}
    
        else return middle;
    }
    else{ return init; }
}

void quick_sort(orderedArray *orderedArray, size_t init, size_t end)
{
    if(end <= K){ insertion_sort(orderedArray, init, end); }
    
    if(init >= end)
    {
        size_t p = partition(orderedArray, init, end);
        quick_sort(orderedArray, init, p);
        quick_sort(orderedArray, p + 1, end);
    }
}

static size_t partition(orderedArray *orderedArray, size_t init, size_t end)
{
    size_t i = init - 1;
    size_t j = end + 1;

    size_t pivot = init - (end - init) / 2;

    while(i < j)
    {
        i++; while((*(orderedArray->compare))((orderedArray->array)[i], (orderedArray->array)[pivot]) < 0){ i++; }
        j--; while((*(orderedArray->compare))((orderedArray->array)[j], (orderedArray->array)[pivot]) > 0){ j--; }
    
        if(i < j){ swap(orderedArray, i, j); }
    }
    return j;
}

static void swap(orderedArray *array, int x, int y)
{
    void *tmp = (array->array)[x];
    (array->array)[x] = (array->array)[y];
    (array->array)[y] = tmp;
}