#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef struct _PriorityQueue PriorityQueue;
typedef struct _pqElement pqElement;

struct _pqElement {
  void* data;
  void* priority;
  void* next;
};

typedef int (*PriorityQueueCompareType)(void*, void*);
typedef void (*PriorityQueuePrintQueue)(PriorityQueue*);

PriorityQueue* PriorityQueue_new(size_t capacity,PriorityQueueCompareType compare,PriorityQueuePrintQueue printQueue);

pqElement* pqElement_new(void* data,void* priority,void* next);

// Deallocates the ordered array
void PriorityQueue_free(PriorityQueue* array);

// Returns the number of elements currently stored in the ordered array
size_t PriorityQueue_size(PriorityQueue* array);

// Returns the capacity of the ordered array
size_t PriorityQueue_capacity(PriorityQueue* array);

// Returns 1 if array is empty, 0 otherwise
int PriorityQueue_empty(PriorityQueue* array);


// Insert element in the ordered array
void PriorityQueue_insert(PriorityQueue* array, void* element);

void PriorityQueue_push(PriorityQueue* array,pqElement* element);

void PriorityQueue_print(PriorityQueue* array);

void exchangePosition(PriorityQueue* array,int s,int f);

void* PriorityQueue_at(PriorityQueue* array, size_t position);

int Right(PriorityQueue* array, int index);

int Left(PriorityQueue* array, int index);

int Parent(PriorityQueue * array, int index);

void* min(PriorityQueue* array, void* i, void*j, void* k);

void Heapify(PriorityQueue * array, int index);

void HeapExtractMin(PriorityQueue *array);

void* getPriority(void * obj);

void UpdatePriority(PriorityQueue* array,int index,void* priority);

void HeapReBuild(PriorityQueue* array,int index); 	

void buildHeap(PriorityQueue* array);

void HeapSort(PriorityQueue* array);

 int compare_int(void* obj1, void* obj2);

// Function implementing an order relation by the chose value between object.
 int compare_char(void* obj1, void* obj2);

// Function implementing an order relation by the chose value between object.
 int compare_float(void* obj1, void* obj2);


 void printInt(PriorityQueue* array);

 void printFloat(PriorityQueue* array);

 void printString(PriorityQueue* array);

 int* new_int(int value);

 float* new_float(float value);

 char* new_string(char* value);

void* getData(void * obj);

void UpdateNext(PriorityQueue* array,int index,void* next);

int findQueueElem(PriorityQueue* array,int index);
