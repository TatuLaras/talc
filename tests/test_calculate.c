#include "../src/calculate.h"
#include "../src/external/unity.h"

static SymbolQueue symbols = {0};

void setUp() { queue_init(&symbols); }

void tearDown() { queue_free(&symbols); }

void test_expression_has_the_right_result() {
    char *expression = "((((100*(10+3))^(2)))+1.123)";
    TEST_ASSERT_FALSE(str_to_symbols_postfix(expression, &symbols));

    double result = 0;
    TEST_ASSERT_FALSE(calculate_value(&symbols, &result));

    TEST_ASSERT(1690001.123 == result);
}

void test_signed_numeric_literals() {
    char *expression = "-5-2+3+-2";
    TEST_ASSERT_FALSE(str_to_symbols_postfix(expression, &symbols));

    double result = 0;
    TEST_ASSERT_FALSE(calculate_value(&symbols, &result));

    TEST_ASSERT_EQUAL(-6, result);
}

void test_signed_numeric_literals_advanced() {
    char *expression = "((3+-4)*2+-1*-5+-6.2)-5";
    TEST_ASSERT_FALSE(str_to_symbols_postfix(expression, &symbols));

    double result = 0;
    TEST_ASSERT_FALSE(calculate_value(&symbols, &result));

    TEST_ASSERT(-8.2 == result);
}

void test_double_minus_at_start() {
    //  NOTE: I decided that --2 should be interpreted as (-(-2)), very unlikely
    //   that someone would use it that way, but I think a calculator should be
    //   as permissible as possible when it comes to stuff like this, with
    //   errors being reserved for situations when there is no way to interpret
    //   the input
    char *expression = "--2+3";
    TEST_ASSERT_FALSE(str_to_symbols_postfix(expression, &symbols));

    double result = 0;
    TEST_ASSERT_FALSE(calculate_value(&symbols, &result));

    TEST_ASSERT_EQUAL(5, result);
}

void test_double_minus_in_the_middle() {
    char *expression = "5--2";
    TEST_ASSERT_FALSE(str_to_symbols_postfix(expression, &symbols));

    double result = 0;
    TEST_ASSERT_FALSE(calculate_value(&symbols, &result));

    TEST_ASSERT_EQUAL(7, result);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_expression_has_the_right_result);
    RUN_TEST(test_signed_numeric_literals);
    RUN_TEST(test_signed_numeric_literals_advanced);
    RUN_TEST(test_double_minus_at_start);
    RUN_TEST(test_double_minus_in_the_middle);

    return UNITY_END();
}
