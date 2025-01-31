#include "../src/external/unity.h"
#include "../src/queue.h"

static SymbolQueue queue = {0};

void setUp() { queue_init(&queue); }

void tearDown() { queue_free(&queue); }

void test_queue_should_grow() {
    int initial_size = queue.__size;

    TEST_ASSERT_EQUAL(QUEUE_STARTING_SIZE, initial_size);
    TEST_ASSERT_EQUAL(0, queue.__used);

    for (int i = 0; i <= initial_size + 1; i++) {
        Symbol symbol = {0};
        queue_enqueue(&queue, symbol);
    }

    TEST_ASSERT_EQUAL(initial_size * 2, queue.__size);
}

void test_queue_should_contain_pushed_values() {
    int8_t values[6] = {12, 23, 34, 45, 56, 230};

    for (int i = 0; i < 6; i++) {
        Symbol symbol = {.type = values[i]};
        queue_enqueue(&queue, symbol);
    }

    for (int i = 0; i < 6; i++) {
        TEST_ASSERT_EQUAL(values[i], queue.__array[i].type);
    }
}

void test_queue_dequeueing_works() {
    int8_t values[6] = {12, 23, 34, 45, 56, 230};

    for (int i = 0; i < 6; i++) {
        Symbol symbol = {.type = values[i]};
        queue_enqueue(&queue, symbol);
    }

    for (int i = 0; i < 6; i++) {
        Symbol out_symbol = {0};
        TEST_ASSERT_FALSE(queue_dequeue(&queue, &out_symbol));
        TEST_ASSERT_EQUAL(values[i], out_symbol.type);
    }

    TEST_ASSERT_EQUAL(queue.__used, queue.__start);
}

void test_over_dequeing_should_fail() {
    int8_t values[3] = {12, 23, 34};

    for (int i = 0; i < 3; i++) {
        Symbol symbol = {.type = values[i]};
        queue_enqueue(&queue, symbol);
    }

    for (int i = 0; i < 3; i++) {
        queue_dequeue(&queue, 0);
    }

    TEST_ASSERT(queue_dequeue(&queue, 0));
}

void test_out_of_bounds_value_should_fail() {
    SymbolQueue queue = {0};
    queue_init(&queue);

    int values[6] = {12, 23, 34, 45, 56, 9922};

    for (int i = 0; i < 6; i++) {
        Symbol symbol = {.type = values[i]};
        queue_enqueue(&queue, symbol);
    }

    Symbol out_symbol = {0};
    queue_peek_from_back(&queue, 2, &out_symbol);
    TEST_ASSERT_EQUAL(45, out_symbol.type);

    // These two should not affect the out_symbol variable
    //   and should return 1 indicating an error
    TEST_ASSERT(queue_peek_from_back(&queue, 6, &out_symbol));
    TEST_ASSERT_EQUAL(45, out_symbol.type);

    TEST_ASSERT(queue_peek_from_back(&queue, -1, &out_symbol));
    TEST_ASSERT_EQUAL(45, out_symbol.type);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_queue_should_grow);
    RUN_TEST(test_queue_should_contain_pushed_values);
    RUN_TEST(test_queue_dequeueing_works);
    RUN_TEST(test_over_dequeing_should_fail);
    RUN_TEST(test_out_of_bounds_value_should_fail);
    return UNITY_END();
}
