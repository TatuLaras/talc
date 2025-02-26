#include "../src/external/unity.h"
#include "../src/results_buffer.h"
#include <string.h>

void setUp() {}
void tearDown() {}

void test_buffer_contains_pushed_data() {
    ResultsBuffer buffer = {0};
    Result results[3] = {
        {.result = 123, .expression = "100+23"},
        {.result = 133, .expression = "100+33"},
        {.result = 143, .expression = "100+43"},
    };

    for (int i = 0; i < 3; i++) {
        results_buffer_push(&buffer, results[i]);

        Result out = {0};
        TEST_ASSERT_FALSE(results_buffer_get_latest(&buffer, 0, &out));
        TEST_ASSERT_EQUAL(results[i].result, out.result);
        TEST_ASSERT_FALSE(strcmp(out.expression, results[i].expression));
    }
}

void test_buffer_clear() {
    ResultsBuffer buffer = {0};
    Result results[3] = {
        {.result = 123, .expression = "100+23"},
        {.result = 133, .expression = "100+33"},
        {.result = 143, .expression = "100+43"},
    };

    for (int i = 0; i < 3; i++) {
        results_buffer_push(&buffer, results[i]);
    }

    results_buffer_clear(&buffer);
    TEST_ASSERT_FALSE(buffer.count);
    TEST_ASSERT_FALSE(buffer._current);
}

void test_get_fails_on_out_of_bounds_value() {
    ResultsBuffer buffer = {0};
    Result results[3] = {
        {.result = 123, .expression = "100+23"},
        {.result = 133, .expression = "100+33"},
        {.result = 143, .expression = "100+43"},
    };

    for (int i = 0; i < 3; i++) {
        results_buffer_push(&buffer, results[i]);
    }

    Result out;
    TEST_ASSERT(results_buffer_get_latest(&buffer, -1, &out));
    TEST_ASSERT(results_buffer_get_latest(&buffer, 3, &out));
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_buffer_contains_pushed_data);
    RUN_TEST(test_buffer_clear);
    RUN_TEST(test_get_fails_on_out_of_bounds_value);

    return UNITY_END();
}
