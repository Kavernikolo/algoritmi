#include "priorityQueue.h"
#include "unity.h"
#include "unity_internals.h"

// Function implementing the order relation between integers
int compare_int_ptr(void* elem1, void* elem2) {
    int int1 = *(int*) elem1;
    int int2 = *(int*) elem2;

    if(int1 == int2) {
        return 0;
    }

    if(int1 < int2) {
        return -1;
    }

    return 1;
}

static PriorityQueue* build_fixture() {
    PriorityQueue* array=PriorityQueue_new(1,compare_int,printInt);

    PriorityQueue_push(array, pqElement_new(new_int(23), new_int(234), new_int(234)));
    PriorityQueue_push(array, pqElement_new(new_int(4), new_int(231), new_int(234)));
    PriorityQueue_push(array, pqElement_new(new_int(23), new_int(23), new_int(234)));
    PriorityQueue_push(array, pqElement_new(new_int(23), new_int(53), new_int(234)));
    PriorityQueue_push(array, pqElement_new(new_int(22), new_int(24), new_int(234)));
    PriorityQueue_push(array, pqElement_new(new_int(22), new_int(240), new_int(234)));

    return array;
}

static void free_fixture(PriorityQueue* array) {
    for(size_t i = 1; i<PriorityQueue_size(array); i++) {
        free(PriorityQueue_at(array, i));
    }

    PriorityQueue_free(array);
}

static void test_queue_new_not_null() {
    PriorityQueue* array=PriorityQueue_new(10,compare_int,printInt);
    TEST_ASSERT_NOT_NULL(array);

    PriorityQueue_free(array);
}

static void test_queue_new_capacity_is_correct() {
    PriorityQueue* array=PriorityQueue_new(10,compare_int,printInt);
    TEST_ASSERT_EQUAL_INT(10, PriorityQueue_capacity(array));

    PriorityQueue_free(array);
}

static void test_queue_new_size_one() { //size iniziale è 1
    PriorityQueue* array=PriorityQueue_new(10,compare_int,printInt);
    TEST_ASSERT_EQUAL_INT(1, PriorityQueue_size(array));

    PriorityQueue_free(array);
}


static void test_queue_free() {
    PriorityQueue* array=PriorityQueue_new(10,compare_int,printInt);
    PriorityQueue_free(array);

    TEST_ASSERT_EQUAL_INT(1, 1);
}

static void test_queue_size() {
    PriorityQueue* array = build_fixture();
    TEST_ASSERT_EQUAL_INT(7, PriorityQueue_size(array));
    PriorityQueue_free(array);
}

static void test_queue_empty() {
    PriorityQueue* array=PriorityQueue_new(10,compare_int,printInt);
    TEST_ASSERT_EQUAL_INT(1, PriorityQueue_empty(array));
    PriorityQueue_free(array);
}

static void test_queue_realloc() {
    PriorityQueue* array = build_fixture();
    size_t old_capacity = PriorityQueue_capacity(array);
    PriorityQueue_push(array, pqElement_new(new_int(44), new_int(1515), new_int(234)));
    PriorityQueue_push(array, pqElement_new(new_int(88), new_int(121), new_int(234)));
    TEST_ASSERT_EQUAL_INT(1, PriorityQueue_capacity(array) > old_capacity);
    TEST_ASSERT_EQUAL_INT(1, PriorityQueue_capacity(array) >= PriorityQueue_size(array));

    PriorityQueue_free(array);
}

static void test_priority_at() {
    PriorityQueue* array = build_fixture();

    TEST_ASSERT_EQUAL_INT(23, *(int*)getPriority(PriorityQueue_at(array, 1)) );
    TEST_ASSERT_EQUAL_INT(24, *(int*)getPriority(PriorityQueue_at(array, 2)) );
    TEST_ASSERT_EQUAL_INT(231, *(int*)getPriority(PriorityQueue_at(array, 3)) );
    TEST_ASSERT_EQUAL_INT(234, *(int*)getPriority(PriorityQueue_at(array, 4)) );
    TEST_ASSERT_EQUAL_INT(53, *(int*)getPriority(PriorityQueue_at(array, 5)) );
    TEST_ASSERT_EQUAL_INT(240, *(int*)getPriority(PriorityQueue_at(array, 6)) );
    free_fixture(array);
}

static void test_extract_min(){
    PriorityQueue* array = build_fixture();
    HeapExtractMin(array);
    TEST_ASSERT_EQUAL_INT(24, *(int*)getPriority(PriorityQueue_at(array, 1)) );
    TEST_ASSERT_EQUAL_INT(231, *(int*)getPriority(PriorityQueue_at(array, 3)) );
    TEST_ASSERT_EQUAL_INT(234, *(int*)getPriority(PriorityQueue_at(array, 4)) );
    TEST_ASSERT_EQUAL_INT(53, *(int*)getPriority(PriorityQueue_at(array, 2)) );
    TEST_ASSERT_EQUAL_INT(240, *(int*)getPriority(PriorityQueue_at(array, 5)) );
    TEST_ASSERT_EQUAL_INT(6, PriorityQueue_size(array));
    free_fixture(array);
}

static void test_heap_sort(){
    PriorityQueue* array = build_fixture();
    HeapSort(array);
    TEST_ASSERT_EQUAL_INT(23, *(int*)getPriority(PriorityQueue_at(array, 6)) );
    TEST_ASSERT_EQUAL_INT(24, *(int*)getPriority(PriorityQueue_at(array, 5)) );
    TEST_ASSERT_EQUAL_INT(231, *(int*)getPriority(PriorityQueue_at(array, 3)) );
    TEST_ASSERT_EQUAL_INT(234, *(int*)getPriority(PriorityQueue_at(array, 2)) );
    TEST_ASSERT_EQUAL_INT(53, *(int*)getPriority(PriorityQueue_at(array, 4)) );
    TEST_ASSERT_EQUAL_INT(240, *(int*)getPriority(PriorityQueue_at(array, 1)) );
    free_fixture(array);
}

static void test_update_priority(){
    PriorityQueue* array = build_fixture();
    UpdatePriority(array, 1, new_int(50));
    TEST_ASSERT_EQUAL_INT(50, *(int*)getPriority(PriorityQueue_at(array, 2)) );
    TEST_ASSERT_EQUAL_INT(24, *(int*)getPriority(PriorityQueue_at(array, 1)) );
    TEST_ASSERT_EQUAL_INT(231, *(int*)getPriority(PriorityQueue_at(array, 3)) );
    TEST_ASSERT_EQUAL_INT(234, *(int*)getPriority(PriorityQueue_at(array, 4)) );
    TEST_ASSERT_EQUAL_INT(53, *(int*)getPriority(PriorityQueue_at(array, 5)) );
    TEST_ASSERT_EQUAL_INT(240, *(int*)getPriority(PriorityQueue_at(array, 6)) );
    free_fixture(array);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_queue_new_not_null);
    RUN_TEST(test_queue_new_capacity_is_correct);
    RUN_TEST(test_queue_new_size_one);
    RUN_TEST(test_queue_size);
    RUN_TEST(test_queue_free);
    RUN_TEST(test_queue_empty);
    RUN_TEST(test_queue_realloc);
    RUN_TEST(test_priority_at);
    RUN_TEST(test_extract_min);
    RUN_TEST(test_heap_sort);
    RUN_TEST(test_update_priority);
    UNITY_END();

    return 0;
}