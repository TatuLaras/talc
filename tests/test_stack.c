#include "../src/external/unity.h"
#include "../src/symbol_stack.h"

SymbolStack stack = {0};
void setUp() { stack_init(&stack); }
void tearDown() { stack_free(&stack); }

void test_stack_should_grow() {
    int initial_size = stack.__size;

    TEST_ASSERT_EQUAL(STACK_STARTING_SIZE, initial_size);
    TEST_ASSERT_EQUAL(0, stack.__top);

    for (int i = 0; i <= initial_size + 1; i++) {
        Symbol symbol = {0};
        stack_push(&stack, symbol);
    }

    TEST_ASSERT_EQUAL(initial_size * 2, stack.__size);
}

void test_stack_should_contain_pushed_values() {
    int8_t values[6] = {12, 23, 34, 45, 56, 230};

    for (int i = 0; i < 6; i++) {
        Symbol symbol = {.type = values[i]};
        stack_push(&stack, symbol);
    }

    for (int i = 0; i < 6; i++) {
        TEST_ASSERT_EQUAL(values[i], stack.__array[i].type);
    }
}

void test_stack_get_and_popping_works() {
    int8_t values[6] = {12, 23, 34, 45, 56, 230};

    for (int i = 0; i < 6; i++) {
        Symbol symbol = {.type = values[i]};
        stack_push(&stack, symbol);
    }

    Symbol out_symbol = {0};
    TEST_ASSERT_FALSE(stack_get(&stack, 2, &out_symbol));
    TEST_ASSERT_EQUAL(values[2], out_symbol.type);

    for (int i = 0; i < 6; i++) {
        Symbol out_symbol = {0};
        TEST_ASSERT_FALSE(stack_pop(&stack, &out_symbol));
        TEST_ASSERT_EQUAL(values[5 - i], out_symbol.type);
        TEST_ASSERT_EQUAL(5 - i, stack.__top);
    }

    TEST_ASSERT_EQUAL(0, stack.__top);
}

void test_out_of_bounds_value_should_fail() {
    int values[6] = {12, 23, 34, 45, 56, 9922};

    for (int i = 0; i < 6; i++) {
        Symbol symbol = {.type = values[i]};
        stack_push(&stack, symbol);
    }

    Symbol out_symbol = {0};
    stack_peek_from_top(&stack, 2, &out_symbol);
    TEST_ASSERT_EQUAL(45, out_symbol.type);

    TEST_ASSERT(stack_peek_from_top(&stack, 6, &out_symbol));
    TEST_ASSERT(stack_peek_from_top(&stack, -1, &out_symbol));
    TEST_ASSERT(stack_get(&stack, -1, &out_symbol));
    TEST_ASSERT(stack_get(&stack, 6, &out_symbol));
}

void test_popping_from_empty_stack_should_fail() {
    Symbol symbol = {.type = 0};
    stack_push(&stack, symbol);

    TEST_ASSERT_FALSE(stack_pop(&stack, &symbol));
    TEST_ASSERT(stack_pop(&stack, &symbol));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_stack_should_grow);
    RUN_TEST(test_stack_should_contain_pushed_values);
    RUN_TEST(test_stack_get_and_popping_works);
    RUN_TEST(test_out_of_bounds_value_should_fail);
    RUN_TEST(test_popping_from_empty_stack_should_fail);
    return UNITY_END();
}
