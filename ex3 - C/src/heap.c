#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"heap.h"


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

void array_list_set(arrayList *array_list, size_t to, void *element)
{
    array_list->array[to] = element;
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


void bubbleUp(arrayList *array_list)
{
    size_t index = array_list_size(array_list) - 1;

    while(hasParent(index) == TRUE && (array_list->compare(array_list_get(array_list, getParentIndex(index)), array_list_get(array_list, index)) > 0))
    {
        swap(array_list, index, getParentIndex(index));

        index = getParentIndex(index);
    }

}

int getParentIndex(int i){ return (i/2); }
//void getParentElement(arrayList *array_list, int i){ return array_list_get(array_list, i); }
int hasParent(int i){ return i > 1;}

int getLeftIndex(int i){ return (2 * i); }
//void getLeftElement(arrayList *array_list, int i){ return array_list_get(array_list, i); }
int hasLeftChild(arrayList *array_list, int i){ return getLeftIndex(i) < array_list_size(array_list) - 1; }

int getRightIndex(int i){ return (2*1) + 1; }
//void getRightElement(arrayList *array_list, int i){ return array_list_get(array_list, i); }
int hasRightChild(arrayList *array_list, int i){ return getLeftIndex(i) <= array_list_size(array_list) - 1; }

void extractMin(arrayList *array_list)
{
    size_t size = array_list_size(array_list);
    array_list->array[ROOT] = array_list->array[size - 1];

    array_list->size = size - 1;

    bubbleDown(array_list);
}

void bubbleDown(arrayList *array_list)
{
    size_t size = array_list_size(array_list);
    size_t index = ROOT;

    size_t leftChild;
    size_t rightChild;

    size_t minIndex;

    void *element;

    while(TRUE)
    {
        leftChild = getLeftIndex(index);
        rightChild = getRightIndex(index);

        minIndex = index;

        if(size > leftChild && (array_list->compare(array_list_get(array_list, minIndex), array_list_get(array_list, leftChild)) > 0))
        {
            minIndex = leftChild;
        }

        if(size > rightChild && (array_list->compare(array_list_get(array_list, minIndex), array_list_get(array_list, rightChild)) > 0))
        {
            minIndex = rightChild;
        }

        if(index != minIndex){ swap(array_list, index, minIndex); }
        else{ return; }
    }
    
}

static void swap(arrayList *array_list, int x, int y)
{
    void *tmp = array_list_get(array_list, x);
    (array_list->array)[x] = array_list_get(array_list, y);
    (array_list->array)[y] = tmp;
}

void decreaseElement(arrayList *array_list, void *source, void *destination)
{
    size_t size = array_list_size(array_list);

    size_t gps = binary_search(array_list, source, 0, size);
    
    if(gps == ROOT && (array_list->compare(destination, array_list_get(array_list, gps)) < 0))
    {
        array_list->array[gps] = destination;
        bubbleDown(array_list);
    }
    else if(array_list->compare(destination, array_list_get(array_list, gps)) < 0)
    {
            array_list->array[gps] = destination;
            bubbleUp(array_list);
    }
    else{ return; }
}

static size_t binary_search(arrayList *array_list, void *element, size_t init, size_t end)
{
    if(end <= init)
    {   
        if((array_list->compare(element, array_list_get(array_list, init)) < 0)){ return init; }
        else{ return init + 1; }
    }

    size_t middle = (init + ((end - init) / 2));
        
    size_t compare_element = ((array_list->compare(element, array_list_get(array_list, middle))));

    if(compare_element < 0){ return binary_search(array_list, element, init, middle - 1); }
    else if(compare_element > 0){ return binary_search(array_list, element, middle + 1, end); }
    else return middle;
}