#include "../src/external/unity.h"
#include "../src/stack.h"

void setUp() {}

void tearDown() {}

void test_stack_should_grow() {
    SymbolStack stack = {0};
    stack_init(&stack);

    int initial_size = stack.__size;

    TEST_ASSERT_EQUAL(STACK_STARTING_SIZE, initial_size);
    TEST_ASSERT_EQUAL(0, stack.__top);

    for (int i = 0; i <= initial_size + 1; i++) {
        Symbol symbol = {0};
        stack_push(&stack, symbol);
    }

    TEST_ASSERT_EQUAL(initial_size * 2, stack.__size);

    stack_free(&stack);
}

void test_stack_should_contain_pushed_values() {
    SymbolStack stack = {0};
    stack_init(&stack);

    int values[6] = {12, 23, 34, 45, 56, 9922};

    for (int i = 0; i < 6; i++) {
        Symbol symbol = {.symbol_type = values[i]};
        stack_push(&stack, symbol);
    }

    for (int i = 0; i < 6; i++) {
        TEST_ASSERT_EQUAL(values[i], stack.__array[i].symbol_type);
    }
}

void test_stack_popping_works() {
    SymbolStack stack = {0};
    stack_init(&stack);

    int values[6] = {12, 23, 34, 45, 56, 9922};

    for (int i = 0; i < 6; i++) {
        Symbol symbol = {.symbol_type = values[i]};
        stack_push(&stack, symbol);
    }

    for (int i = 0; i < 6; i++) {
        Symbol out_symbol = {0};
        TEST_ASSERT_FALSE(stack_pop(&stack, &out_symbol));
        TEST_ASSERT_EQUAL(values[5 - i], out_symbol.symbol_type);
        TEST_ASSERT_EQUAL(5 - i, stack.__top);
    }

    TEST_ASSERT_EQUAL(0, stack.__top);
}

void test_out_of_bounds_value_should_fail() {
    SymbolStack stack = {0};
    stack_init(&stack);

    int values[6] = {12, 23, 34, 45, 56, 9922};

    for (int i = 0; i < 6; i++) {
        Symbol symbol = {.symbol_type = values[i]};
        stack_push(&stack, symbol);
    }

    Symbol out_symbol = {0};
    stack_peek_from_top(&stack, 2, &out_symbol);
    TEST_ASSERT_EQUAL(45, out_symbol.symbol_type);

    // These two should not affect the out_symbol variable
    //   and should return 1 indicating an error
    TEST_ASSERT(stack_peek_from_top(&stack, 6, &out_symbol));
    TEST_ASSERT_EQUAL(45, out_symbol.symbol_type);

    TEST_ASSERT(stack_peek_from_top(&stack, -1, &out_symbol));
    TEST_ASSERT_EQUAL(45, out_symbol.symbol_type);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_stack_should_grow);
    RUN_TEST(test_stack_should_contain_pushed_values);
    RUN_TEST(test_stack_popping_works);
    RUN_TEST(test_out_of_bounds_value_should_fail);
    return UNITY_END();
}
