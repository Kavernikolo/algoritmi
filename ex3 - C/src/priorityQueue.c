#include "priorityQueue.h"

struct _PriorityQueue {
  void **pq_array;
  size_t size;
  size_t capacity;
  PriorityQueueCompareType compare;
  PriorityQueuePrintQueue printQueue;
};


PriorityQueue* PriorityQueue_new(size_t capacity, PriorityQueueCompareType compare,PriorityQueuePrintQueue printQueue) {
  PriorityQueue* result = (PriorityQueue*) malloc(sizeof(PriorityQueue));
  result->pq_array =(void**)malloc(sizeof(void*)*capacity);
  result->size = 1;
  result->capacity = capacity;
  result->compare=compare;
  result->printQueue=printQueue;
  return result;
}

 int compare_int(void* obj1, void* obj2) {
  /*pqElement* elem1 = (pqElement*)obj1;
  pqElement* elem2 = (pqElement*)obj2;*/
  
  if(*(int*)obj1 < *(int*)obj2)
    return -1;
  
  if(*(int*)obj1 > *(int*)obj2)
    return 1;
  return 0; //int1==int2
}

// Function implementing an order relation by the chose value between object.
 int compare_char(void* obj1, void* obj2) {
  char* str1 = (char*) obj1;
  char* str2 = (char*) obj2;

  if (strlen(str1)<strlen(str2))
    return -1;
  if (strlen(str1)>strlen(str2))
    return 1;  
  return 0;
}

// Function implementing an order relation by the chose value between object.
 int compare_float(void* obj1, void* obj2) {
  float flt1 = *(float*) obj1;
  float flt2 = *(float*) obj2;

  if(flt1 < flt2) 
    return -1;
  
  if(flt1 > flt2)
    return 1;
  return 0; //flt1==flt2
}

 pqElement* pqElement_new(void* data, void* priority,void* next){
  pqElement* result = (pqElement*) malloc(sizeof(pqElement));
  result->data=data;
  result->priority=priority;
  result->next=next;
  return result;
}

 void printInt(PriorityQueue* array){
  size_t size= PriorityQueue_size(array);
  printf("Size of priority queue: %zu\n",size);
  printf("Space allocated for queue: %zu\n", PriorityQueue_capacity(array));
  printf("Data in priority queue:\n");
  for (int i = 1; i < size; i++){
      pqElement * element=PriorityQueue_at(array,i);
      printf("%d-%d-%d\n", *(int*)element->data,*(int*)element->priority,*(int*)element->next);
  }
  printf("\n");
}

 void printFloat(PriorityQueue* array){
  size_t size= PriorityQueue_size(array);
  printf("Size of priority queue: %zu\n",size);
  printf("Space allocated for queue: %zu\n", PriorityQueue_capacity(array));
  printf("Data in priority queue:\n");
  for (int i = 1; i < size; i++){
      pqElement * element=PriorityQueue_at(array,i);
      printf("%d-%.2f-%d\n", *(int*)element->data,*(float*)element->priority,*(int*)element->next);
  }
  printf("\n");
}

 void printString(PriorityQueue* array){
  size_t size= PriorityQueue_size(array);
  printf("Size of priority queue: %zu\n",size);
  printf("Space allocated for queue: %zu\n", PriorityQueue_capacity(array));
  printf("Data in priority queue:\n");
  for (int i = 1; i < size; i++){
      pqElement * element=PriorityQueue_at(array,i);
      printf("%s-%s-%d\n", (char*)element->data,(char*)element->priority,*(char*)element->next);
  }
  printf("\n");
}

 int* new_int(int value){
  int *elem=(int*)malloc(sizeof(int));
  *elem=value;
  return elem;
}

 float* new_float(float value){
  float *elem=(float*)malloc(sizeof(float));
  *elem=value;
  return elem;
}

 char* new_string(char* value){
  char* elem=(char*)malloc(sizeof(char)*strlen(value)+1);
  strcpy(elem,value);
  return elem;
}

void PriorityQueue_print(PriorityQueue* array){
  array->printQueue(array);
}

void PriorityQueue_free(PriorityQueue* array) {
  free(array->pq_array);
  free(array);
  return;
}

size_t PriorityQueue_size(PriorityQueue* array) {
  return array->size;
}

size_t PriorityQueue_capacity(PriorityQueue* array) {
  return array->capacity;
}

int PriorityQueue_empty(PriorityQueue* array) {
  return array->size == 1;
}


void PriorityQueue_check_and_realloc(PriorityQueue* array) {
  if( array->capacity > array->size )
    return;
  array->capacity *= 2;
  array->pq_array = realloc(array->pq_array, sizeof(void*) * array->capacity);
}

void* PriorityQueue_at(PriorityQueue* array, size_t position) {
  if(position >= array->size) {
    fprintf(stderr, "Array index (%ld) out of bounds (0:%ld)\n", position, array->size);
    exit(EXIT_FAILURE);
  }
  return array->pq_array[position];
}

int PriorityQueue_compare(PriorityQueue* array, void* element1,void* element2){
  return array->compare(element1,element2);
}

void exchangePosition(PriorityQueue* array,int s,int f){
  pqElement * elem1 = PriorityQueue_at(array,s);
  pqElement * elem2 = PriorityQueue_at(array,f);
  array->pq_array[s]=elem2;
  array->pq_array[f]=elem1;
}


int Parent(PriorityQueue * array, int index){
  size_t size = PriorityQueue_size(array);
  if(index>=1 && index<size){
    return index/2;
  }
  return 0;
}

int Left(PriorityQueue* array, int index){
  size_t size = PriorityQueue_size(array);
  if(index>=1 && index< size){
    if(2*index<size)
      return 2*index;
    else
      return index;
  }
  return 0; 
}

int Right(PriorityQueue* array, int index){
 size_t size = PriorityQueue_size(array);
  if(index>=1 && index< size){
    if((2*index)+1<size)
      return (2*index)+1;
    else
      return index;
  }
  return 0; 
}

void PriorityQueue_push(PriorityQueue* array,pqElement* element){
    int s; // indices to traverse tree (s son, f father)
    array->size=array->size+1;
    PriorityQueue_check_and_realloc(array); // one more element in PQ
    s = array->size-1; // new element is placed at bottom of tree/array
     //pq_array[f] is father of pq_array[s]
    array->pq_array[s]=element;
    while ((s > 1) && (PriorityQueue_compare(array,getPriority(PriorityQueue_at(array,s)),getPriority(PriorityQueue_at(array,Parent(array,s))))==-1)){
        exchangePosition(array,s,Parent(array,s));
        s = Parent(array,s); // son takes place of father
        // father at this new position of son
    }    
    //place element here
    //printf("Inserting data %d and priority %d in heap at index %d\n", data, priority, s);
}

void* min(PriorityQueue* array, void* i, void* j, void* k){
  if(PriorityQueue_compare(array,i,j)==-1 || PriorityQueue_compare(array,i,j)==0){
    if(PriorityQueue_compare(array,i,k)==-1 || PriorityQueue_compare(array,i,k)==0)
      return i;
    else
      return k;
  }else{
    if(PriorityQueue_compare(array,j,k)==-1 || PriorityQueue_compare(array,j,k)==0)
      return j;
    else 
      return k;
  }
}
void* getPriority(void * obj){
  pqElement* elem=(pqElement*)obj;
  return elem->priority;
}

void* getData(void * obj){
  pqElement* elem=(pqElement*)obj;
  return elem->data;
}

void Heapify(PriorityQueue * array, int index){
  size_t size = PriorityQueue_size(array);
  if(index>=1 && index<size ){
    void* m = min(array,getPriority(PriorityQueue_at(array,index)),getPriority(PriorityQueue_at(array,Left(array,index))),getPriority(PriorityQueue_at(array,Right(array,index))));
    if(PriorityQueue_compare(array,m,getPriority(PriorityQueue_at(array,index)))!=0){
      if(PriorityQueue_compare(array,m,getPriority(PriorityQueue_at(array,Left(array,index))))==0){
        exchangePosition(array,Left(array,index),index);
        Heapify(array,Left(array,index)); 
      }
      else{
        exchangePosition(array,Right(array,index),index);
        Heapify(array,Right(array,index));
      }
    }
  }
}  

void HeapExtractMin(PriorityQueue *array){
  size_t size = PriorityQueue_size(array);
  array->pq_array[1]=array->pq_array[size-1];
  array->size=size-1;
  Heapify(array,1);
}

void HeapReBuild(PriorityQueue* array,int index){
  size_t size = PriorityQueue_size(array);
  pqElement* elem=PriorityQueue_at(array,index);
  if(index>=1 && index<size){
      if(Parent(array,index)!=0 && PriorityQueue_compare(array,elem->priority,getPriority(PriorityQueue_at(array,Parent(array,index))))==-1){
        exchangePosition(array,index,Parent(array,index));
        HeapReBuild(array,Parent(array,index));
      }else if(Left(array,index)!=0 && PriorityQueue_compare(array,elem->priority,getPriority(PriorityQueue_at(array,Left(array,index))))==1){
        exchangePosition(array,index,Left(array,index));
        HeapReBuild(array,Left(array,index));
        HeapReBuild(array,Right(array,index));
      }else if(Right(array,index)!=0 && PriorityQueue_compare(array,elem->priority,getPriority(PriorityQueue_at(array,Right(array,index))))==1){
        exchangePosition(array,index,Right(array,index));
        HeapReBuild(array,Right(array,index));
        HeapReBuild(array,Left(array,index));
      }
  }
}

void UpdatePriority(PriorityQueue* array,int index,void* priority){
  pqElement * elem=PriorityQueue_at(array,index);
  elem->priority=priority;
  array->pq_array[index]=elem;
  HeapReBuild(array,index);
}

void UpdateNext(PriorityQueue* array,int index,void* next){
  pqElement * elem=PriorityQueue_at(array,index);
  elem->next=next;
  array->pq_array[index]=elem;
}

void buildHeap(PriorityQueue* array){
  for(int i=array->size/2;i>=1;i--)
    Heapify(array,i);
}

void HeapSort(PriorityQueue* array){
  buildHeap(array);
  size_t size = PriorityQueue_size(array);
  for(int i=array->size-1; i>=2;i--){
    exchangePosition(array,i,1);
    array->size--;
    Heapify(array,1);
  }
  array->size=size;
}

int findQueueElem(PriorityQueue* array,int index){
  size_t size = PriorityQueue_size(array);
  for(int i=1;i<size;i++){
    if(*(int*)getData(PriorityQueue_at(array,i))==index)
      return i;
  }
  return -1;
}
