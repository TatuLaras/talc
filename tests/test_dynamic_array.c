#include "../src/dynamic_array.h"
#include "../src/external/unity.h"

static DynamicArray array = {0};
static DynamicPointerArray pointer_array = {0};

void setUp() {
    darray_init(&array);
    dparray_init(&pointer_array);
}

void tearDown() {
    darray_free(&array);
    dparray_free(&pointer_array);
}

void test_array_should_grow() {
    int initial_size = array.__size;

    TEST_ASSERT_EQUAL(DARRAY_STARTING_SIZE, initial_size);
    TEST_ASSERT_EQUAL(0, array.__used);

    for (int i = 0; i <= initial_size + 1; i++) {
        darray_push(&array, 123);
    }

    TEST_ASSERT_EQUAL(initial_size * 2, array.__size);
}

void test_array_should_contain_pushed_values() {
    int values[6] = {12, 23, 34, 45, 56, 9922};

    for (int i = 0; i < 6; i++) {
        darray_push(&array, values[i]);
    }

    for (int i = 0; i < 6; i++) {
        TEST_ASSERT_EQUAL(values[i], array.__array[i]);
    }
}

void test_out_of_bounds_value_should_be_zero() {
    int values[6] = {12, 23, 34, 45, 56, 9922};

    for (int i = 0; i < 6; i++) {
        darray_push(&array, values[i]);
    }

    array.__array[6] = 123;
    TEST_ASSERT_EQUAL(array.__array[6], 123);
    TEST_ASSERT_EQUAL(darray_get(&array, 6), 0);
}

void test_array_should_contain_pushed_references() {
    int values[6] = {12, 23, 34, 45, 56, 9922};

    for (int i = 0; i < 6; i++) {
        int *heap_allocated = malloc(sizeof(int));
        *heap_allocated = values[i];
        dparray_push(&pointer_array, heap_allocated);
    }

    for (int i = 0; i < 6; i++) {
        TEST_ASSERT_EQUAL(values[i], *((int *)dparray_get(&pointer_array, i)));
    }
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_array_should_grow);
    RUN_TEST(test_array_should_contain_pushed_values);
    RUN_TEST(test_out_of_bounds_value_should_be_zero);
    RUN_TEST(test_array_should_contain_pushed_references);
    return UNITY_END();
}
