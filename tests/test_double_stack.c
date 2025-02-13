#include "../src/double_stack.h"
#include "../src/external/unity.h"

void setUp() {}

void tearDown() {}

void test_double_stack_should_grow() {
    DoubleStack stack = {0};
    double_stack_init(&stack);

    int initial_size = stack._size;

    TEST_ASSERT_EQUAL(DOUBLE_STACK_STARTING_SIZE, initial_size);
    TEST_ASSERT_EQUAL(0, stack.top);

    for (int i = 0; i <= initial_size + 1; i++) {
        double item = 0;
        double_stack_push(&stack, item);
    }

    TEST_ASSERT_EQUAL(initial_size * 2, stack._size);

    double_stack_free(&stack);
}

void test_double_stack_should_contain_pushed_values() {
    DoubleStack stack = {0};
    double_stack_init(&stack);

    double values[6] = {12, 23, 34, 45, 56, 230};

    for (int i = 0; i < 6; i++) {
        double symbol = values[i];
        double_stack_push(&stack, symbol);
    }

    for (int i = 0; i < 6; i++) {
        TEST_ASSERT_EQUAL(values[i], stack._array[i]);
    }
}

void test_double_stack_popping_works() {
    DoubleStack stack = {0};
    double_stack_init(&stack);

    int8_t values[6] = {12, 23, 34, 45, 56, 230};

    for (int i = 0; i < 6; i++) {
        double item = values[i];
        double_stack_push(&stack, item);
    }

    for (int i = 0; i < 6; i++) {
        double out_symbol = {0};
        TEST_ASSERT_FALSE(double_stack_pop(&stack, &out_symbol));
        TEST_ASSERT_EQUAL(values[5 - i], out_symbol);
        TEST_ASSERT_EQUAL(5 - i, stack.top);
    }

    TEST_ASSERT_EQUAL(0, stack.top);
}

void test_out_of_bounds_value_should_fail() {
    DoubleStack stack = {0};
    double_stack_init(&stack);

    int values[6] = {12, 23, 34, 45, 56, 9922};

    for (int i = 0; i < 6; i++) {
        double item = values[i];
        double_stack_push(&stack, item);
    }

    double out_symbol = {0};
    double_stack_peek_from_top(&stack, 2, &out_symbol);
    TEST_ASSERT_EQUAL(45, out_symbol);

    // These two should not affect the out_symbol variable
    //   and should return 1 indicating an error
    TEST_ASSERT(double_stack_peek_from_top(&stack, 6, &out_symbol));
    TEST_ASSERT_EQUAL(45, out_symbol);

    TEST_ASSERT(double_stack_peek_from_top(&stack, -1, &out_symbol));
    TEST_ASSERT_EQUAL(45, out_symbol);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_double_stack_should_grow);
    RUN_TEST(test_double_stack_should_contain_pushed_values);
    RUN_TEST(test_double_stack_popping_works);
    RUN_TEST(test_out_of_bounds_value_should_fail);
    return UNITY_END();
}
