#include "priorityQueue.h"


int main(int argc, char const *argv[]) {
    PriorityQueue* array=PriorityQueue_new(1,compare_int,printInt);  
    //PriorityQueue* arrayF=PriorityQueue_new(1,compare_float,printFloat);
    //PriorityQueue* arrayS=PriorityQueue_new(1,compare_char,printString);
    PriorityQueue_push(array, pqElement_new(new_int(23), new_int(1), new_int(234)));
    PriorityQueue_push(array, pqElement_new(new_int(4), new_int(2), new_int(234)));
    PriorityQueue_push(array, pqElement_new(new_int(23), new_int(3), new_int(234)));
    PriorityQueue_push(array, pqElement_new(new_int(23), new_int(4), new_int(234)));
    PriorityQueue_push(array, pqElement_new(new_int(22), new_int(5), new_int(234)));
    PriorityQueue_push(array, pqElement_new(new_int(22), new_int(6), new_int(234)));
    PriorityQueue_print(array);
    HeapExtractMin(array);
    printf("Minimo estratto\n");
    PriorityQueue_print(array);
    printf("Update\n");
    UpdatePriority(array,1,new_int(50));
    PriorityQueue_print(array);
    UpdatePriority(array,5,new_int(1));
    PriorityQueue_print(array);
    //PriorityQueue_push(array, pqElement_new(new_int(14), new_int(34572), new_int(234)));
    //PriorityQueue_print(array);
    //printf("Minimo %d \n",findMin(array));
    HeapSort(array);
    printf("HeapSort\n");
    PriorityQueue_print(array);
    printf("Push\n");
    PriorityQueue_push(array, pqElement_new(new_int(142), new_int(100), new_int(234)));
    PriorityQueue_print(array);
    PriorityQueue_free(array);
    return 0;
}
