#define INITIAL_CAPACITY 2

#define K 50

#define TRUE 1
#define FALSE 0

typedef struct _OrderedArray
{
    void **array;

    size_t size;
    size_t capacity;
  
    int (*precedes)(void *, void *);
}OrderedArray;

OrderedArray *ordered_array_create(int (*precedes)(void *, void *));

int ordered_array_is_empty(OrderedArray *);

size_t ordered_array_size(OrderedArray *);

void ordered_array_add(OrderedArray *, void *);

void *ordered_array_get(OrderedArray *, size_t i);

void ordered_array_free_memory(OrderedArray *);

void merge_binary_insertion_sort(OrderedArray *);

void quick_binary_insertion_sort(OrderedArray *);