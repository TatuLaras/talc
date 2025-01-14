#include "../src/external/unity.h"
#include "../src/testable.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_should_doBlahAndBlah(void) {
    TEST_ASSERT(sum_numbers(10, 11) == 21);
}

void test_function_should_doAlsoDoBlah(void) {
    TEST_ASSERT(sum_numbers(10, 21) == 21);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_doBlahAndBlah);
    RUN_TEST(test_function_should_doAlsoDoBlah);
    return UNITY_END();
}
