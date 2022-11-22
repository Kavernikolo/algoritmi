#include<stdio.h>
#include<stdlib.h>

#include"../include/heap.h"

int compare_int(void *element_1, void *element_2)
{
    int *a = (int *)element_1;
    int *b = (int *)element_2;
  
    return (*a) - (*b);
}

int compare_string(void *element_1, void *element_2)
{
    char *a = (char *)element_1;
    char *b = (char *)element_2;
  
    return strcmp(a, b);
}

int compare_float(void *element_1, void *element_2)
{
    float *a = (float *)element_1;
    float *b = (float *)element_2;
  
    if (*a > *b)
    {
        return 1;
    }
    else if (*a < *b)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

arrayList *array_list_create(int (*compare)(void *, void *))
{
    if(compare == NULL)
    {
        fprintf(stderr, "array_list_create: compare parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }
    
    arrayList *array_list = (arrayList *)malloc(sizeof(arrayList));
    if(array_list == NULL)
    {
        fprintf(stderr, "array_list_create: unable to allocate memory for the array array");
            exit(EXIT_FAILURE);
    }
    
    array_list->array = (void **)malloc(INITIAL_CAPACITY * sizeof(void *));
    if(array_list->array == NULL)
    {
        fprintf(stderr, "array_list_create: unable to allocate memory for the internal array");
            exit(EXIT_FAILURE);
    }
    array_list->size = ROOT;
    array_list->capacity = INITIAL_CAPACITY;

    return (array_list);
}

int array_list_is_empty(arrayList *array_list)
{
    if(array_list == NULL)
    {
        fprintf(stderr, "array_list_is_empty: array_list parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }
    if(array_list->size == 0){ return TRUE; }
  
    return FALSE;
}

size_t array_list_size(arrayList *array_list)
{
    if(array_list == NULL)
    {
        fprintf(stderr, "array_list_size: array_list parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }
    
    return (array_list->size);
}

void array_list_add(arrayList *array_list, void *element)
{
    if(array_list == NULL)
    {
        fprintf(stderr, "add_list_list_element: array_list parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }

    if(element == NULL)
    {
        fprintf(stderr, "add_list_list_element: element parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }

    if(array_list->size >= array_list->capacity)
    {
        array_list->array = (void **)realloc(array_list->array, 2 * (array_list->capacity) * sizeof(void *));
        if(array_list->array == NULL)
        {
            fprintf(stderr, "array_list_add: unable to reallocate memory to host the new element");
                exit(EXIT_FAILURE);
        }
        
        array_list->capacity = 2 * array_list->capacity;
    }

    (array_list->array)[array_list->size] = element;
    (array_list->size)++;

    bubbleUp(array_list);
}

void *array_list_get(arrayList *array_list, size_t i)
{
    if(array_list == NULL)
    {
        fprintf(stderr, "array_list_get: array_list parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }
    
    if(i >= array_list->size)
    {
        fprintf(stderr, "array_list_get: Index %lu is out of the array bounds", i);
            exit(EXIT_FAILURE);
    }
    
    return (array_list->array)[i];
}

void array_list_free_memory(arrayList *array_list)
{
    if(array_list == NULL)
    {
        fprintf(stderr, "array_list_free_memory: array_list parameter cannot be NULL");
            exit(EXIT_FAILURE);
    }
  
    free(array_list->array);
    free(array_list);
}

/* --- MIN HEAP --- */

//Creazione di uno heap minimo vuoto - O(1) -> fatto;

//Inserimento di un elemento - O(log n) -> fatto;

//Restituzione della dimensione dello heap - O(1) - fatto;

//Restituzione del genitore di un elemento - O(1);
int getParentIndex(int i){ return (i/2); }
int getParentElement(arrayList *array_list, int i){ return array_list_get(array_list, getParentIndex(i)); }

//Restituzione del figlio sinistro di un elemento - O(1);
int getLeftIndex(int i){ return (i * 2); }
int getLeftElement(arrayList *array_list, int i){ return array_list_get(array_list, getLeftIndex(i)); }


//Restituzione del figlio destro di un elemento - O(1);
int getRightIndex(int i){ return (i * 2) + 1; }
int getRightElement(arrayList *array_list, int i){ return array_list_get(array_list, getRightIndex(i)); }


//Estrazione dell'elemento con valore minimo - O(log n);
void extractMin(arrayList *array_list)
{
    void *minElement = array_list_get(array_list, ROOT);

    size_t size = array_list_size(array_list);

    array_list->array[ROOT] = array_list->array[size - 1];
    array_list->size = size - 1;

    bubbleDown(array_list);
}

void bubbleUp(arrayList *array_list)
{
    size_t size = array_list_size(array_list);

    while(size > 1 && array_list->compare(getParentElement(array_list, size), array_list_get(array_list, size)) > 0)
    {
        swap(array_list, size, getParentIndex(size));
        size = getParentIndex(size);
    }
}

void bubbleDown(arrayList *array_list)
{
    size_t index = ROOT;

    size_t leftIndex;
    size_t rightIndex;
    
    size_t min;

    while(TRUE)
    {
        leftIndex = getLeftIndex(index);
        rightIndex = getRightIndex(index);

        min = index;

        if(array_list_size(array_list) > leftIndex && (array_list->compare(array_list_get(array_list, index), array_list_get(array_list, leftIndex) > 0)))
        {
            min = leftIndex;
        }

        if(array_list_size(array_list) > rightIndex && (array_list->compare(array_list_get(array_list, index), array_list_get(array_list, rightIndex) > 0)))
        {
            min = rightIndex;
        }

        if(index != min){ swap(array_list, index, min); }
        else{ return; }
    }
    
}

static void swap(arrayList *array, int x, int y)
{
    void *tmp = ordered_array_get(array, x);
    ordered_array_set(array, x, ordered_array_get(array, y));
    ordered_array_set(array, y, tmp);
}

//Diminuzione del valore di un elemento - O(log n).