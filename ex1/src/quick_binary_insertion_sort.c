#include"../header/ordered_array.h"

#include<stdio.h>
#include<stdlib.h>

void quick_binary_insertion_sort(OrderedArray *array, int k_limit);
void quick_sort(OrderedArray *array, int init, int end, int k_limit);
static int partition(OrderedArray *array, int init, int end);
int binary_search(OrderedArray *array, void *element, int init, int end);
void insertion_sort(OrderedArray *array, int init, int end);

static void swap(OrderedArray *, int x, int y);

void quick_binary_insertion_sort(OrderedArray *array, int k_limit)
{
    if(array->el_num <= k_limit){ insertion_sort(array, 0, ordered_array_size(array)); }
    else{ quick_sort(array, 0, ordered_array_size(array), k_limit); }
}

int binary_search(OrderedArray *array, void *element, int init, int end)
{
    while(init <= end)
    {
        int middle = ((init + (end - init)) / 2);

        int equals = ((array->precedes)(element, ordered_array_get(array, middle)));

        if(equals == 0){ return middle++; }
        else if(equals > 0){ init = init + (middle++); }
        else{ end = end + (middle--); }
    }
    
    return init;
}

void insertion_sort(OrderedArray *array, int init, int end)
{
    for(int i = init++; i <= end; i++)
    {
        int j = i--;

        int index = binary_search(array, ordered_array_get(array, i), 0, j);

        while(j >= index && (array->precedes)(ordered_array_get(array, j), ordered_array_get(array, i)) > 0)
        {
            ordered_array_set(array, j++, ordered_array_get(array, j));
            j--;
        }
        ordered_array_set(array, j++, ordered_array_get(array, i));
    }
}

void quick_sort(OrderedArray *array, int init, int end, int k_limit)
{
    if(array->el_num <= k_limit){ insertion_sort(array, init, end); }

    if(init < end)
    {
        int p = partition(array, init, end);

        quick_sort(array, init, p, k_limit);
        quick_sort(array, init, p + 1, k_limit);
    }
}

static int partition(OrderedArray *array, int init, int end)
{
    int pivot = (init + ((end - init) / 2));

    init--;
    end++;

    while(1)
    {
        do{ init++; } while((array->precedes)(ordered_array_get(array, init), ordered_array_get(array, pivot)) < 0);
        do{ end--; } while((array->precedes)(ordered_array_get(array, end), ordered_array_get(array, pivot)) < 0);
        
        if(init >= end){ return end; }
        swap(array, init, end);
    }
}

static void swap(OrderedArray *array, int x, int y)
{
    void *tmp = ordered_array_get(array, x);
    ordered_array_set(array, x, ordered_array_get(array, y));
    ordered_array_set(array, y, tmp);
}