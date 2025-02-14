#include "../src/calculate.h"
#include "../src/external/unity.h"

static SymbolQueue symbols = {0};
static VariableStorage variables = {0};
static VariableAssignmentRequest null_request = {0};

void setUp() {
    queue_init(&symbols);
    variables_init(&variables);
}

void tearDown() {
    queue_free(&symbols);
    variables_free(&variables);
}

void test_expression_has_the_right_result() {
    char *expression = "((((100*(10+3))^(2)))+1.123)";
    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));

    double result = 0;
    TEST_ASSERT_FALSE(calculate_value(&symbols, &result));

    TEST_ASSERT(1690001.123 == result);
}

void test_signed_numeric_literals() {
    char *expression = "-5-2+3+-2";
    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));

    double result = 0;
    TEST_ASSERT_FALSE(calculate_value(&symbols, &result));

    TEST_ASSERT_EQUAL(-6, result);
}

void test_signed_numeric_literals_advanced() {
    char *expression = "((3+-4)*2+-1*-5+-6.2)/5";
    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));

    double result = 0;
    TEST_ASSERT_FALSE(calculate_value(&symbols, &result));

    TEST_ASSERT(-0.64 == result);
}

void test_fails_on_function_with_wrong_number_of_params() {
    char *expression = "3+min(1)+4";
    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));

    double result = 0;
    TEST_ASSERT_TRUE(calculate_value(&symbols, &result));
}

void test_fails_on_undefined_function() {
    char *expression = "3+notdefined(1)+4";
    TEST_ASSERT_TRUE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
}

void test_double_minus_in_the_middle() {
    char *expression = "5--2";
    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));

    double result = 0;
    TEST_ASSERT_FALSE(calculate_value(&symbols, &result));

    TEST_ASSERT_EQUAL(7, result);
}

void test_fails_on_invalid_rpn_basic() {
    double _result = 0;
    SymbolQueue queue = {0};
    queue_init(&queue);

    Symbol first_1 = {.type = SYMBOL_LITERAL, .literal = 5};
    Symbol first_2 = {.type = SYMBOL_OP_ADDITION};
    queue_enqueue(&queue, first_1);
    queue_enqueue(&queue, first_2);

    TEST_ASSERT(calculate_value(&queue, &_result));
}

void test_fails_on_invalid_rpn_more_symbols() {
    double _result = 0;
    SymbolQueue queue = {0};
    queue_init(&queue);

    Symbol symbols[4] = {
        {.type = SYMBOL_LITERAL, .literal = 5},
        {.type = SYMBOL_LITERAL, .literal = 5},
        {.type = SYMBOL_OP_ADDITION},
        {.type = SYMBOL_OP_MULTIPLICATION},
    };

    for (int i = 0; i < 4; i++) {
        queue_enqueue(&queue, symbols[i]);
    }

    TEST_ASSERT(calculate_value(&queue, &_result));
}

void test_fails_on_invalid_rpn_other_operators() {
    double _result = 0;
    SymbolQueue queue = {0};
    queue_init(&queue);

    Symbol symbols[8] = {
        {.type = SYMBOL_LITERAL, .literal = 5},
        {.type = SYMBOL_LITERAL, .literal = 5},
        {.type = SYMBOL_OP_ADDITION},
        {.type = SYMBOL_LITERAL, .literal = 5},
        {.type = SYMBOL_LITERAL, .literal = 5},
        {.type = SYMBOL_OP_MULTIPLICATION},
        {.type = SYMBOL_OP_MULTIPLICATION},
        {.type = SYMBOL_OP_EXPONENT},
    };

    for (int i = 0; i < 8; i++) {
        queue_enqueue(&queue, symbols[i]);
    }

    TEST_ASSERT(calculate_value(&queue, &_result));
    queue_free(&queue);
    queue_init(&queue);

    Symbol symbols_sub[2] = {
        {.type = SYMBOL_LITERAL, .literal = 5},
        {.type = SYMBOL_OP_SUBTRACTION},
    };

    for (int i = 0; i < 2; i++) {
        queue_enqueue(&queue, symbols_sub[i]);
    }

    TEST_ASSERT(calculate_value(&queue, &_result));
}

void test_division_by_zero_fails() {
    char *expression = "5+5*(4/0)+2";
    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));

    double _result = 0;
    TEST_ASSERT(calculate_value(&symbols, &_result));
}

void test_fails_on_invalid_rpn_leftover_symbols() {
    double _result = 0;
    SymbolQueue queue = {0};
    queue_init(&queue);

    Symbol symbols[6] = {
        {.type = SYMBOL_LITERAL, .literal = 5},
        {.type = SYMBOL_LITERAL, .literal = 5},
        {.type = SYMBOL_LITERAL, .literal = 5},
        {.type = SYMBOL_LITERAL, .literal = 5},
        {.type = SYMBOL_OP_ADDITION},
        {.type = SYMBOL_OP_MULTIPLICATION},
    };

    for (int i = 0; i < 6; i++) {
        queue_enqueue(&queue, symbols[i]);
    }

    TEST_ASSERT(calculate_value(&queue, &_result));
}

void test_calculate_with_variables() {
    char *expression = "pi*3.5";
    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
    double result = 0;
    TEST_ASSERT_FALSE(calculate_value(&symbols, &result));
    TEST_ASSERT(result > 10.99);
    TEST_ASSERT(result < 11);
}

void test_invalid_operator_fails() {
    double _result = 0;
    SymbolQueue queue = {0};
    queue_init(&queue);

    Symbol symbols[3] = {
        {.type = SYMBOL_LITERAL, .literal = 5},
        {.type = SYMBOL_LITERAL, .literal = 5},
        {.type = 123},
    };

    for (int i = 0; i < 3; i++) {
        queue_enqueue(&queue, symbols[i]);
    }

    TEST_ASSERT(calculate_value(&queue, &_result));
}

void test_function_with_one_operand() {
    double result = 0;
    SymbolQueue queue = {0};
    queue_init(&queue);

    Symbol symbols[2] = {
        {.type = SYMBOL_LITERAL, .literal = 0.5 * 3.141592653589793},
        {.type = SYMBOL_FUNC_SIN},
    };

    for (int i = 0; i < 2; i++) {
        queue_enqueue(&queue, symbols[i]);
    }

    TEST_ASSERT_FALSE(calculate_value(&queue, &result));
    TEST_ASSERT(result == 1);
}

void test_function_with_two_operands() {
    double result = 0;
    SymbolQueue queue = {0};
    queue_init(&queue);

    Symbol symbols[3] = {
        {.type = SYMBOL_LITERAL, .literal = 12},
        {.type = SYMBOL_LITERAL, .literal = 123},
        {.type = SYMBOL_FUNC_MAX},
    };

    for (int i = 0; i < 3; i++) {
        queue_enqueue(&queue, symbols[i]);
    }

    TEST_ASSERT_FALSE(calculate_value(&queue, &result));
    TEST_ASSERT_EQUAL(123, result);
}

void test_cos_function() {
    double result = 0;
    SymbolQueue queue = {0};
    queue_init(&queue);

    Symbol symbols[2] = {
        {.type = SYMBOL_LITERAL, .literal = 2 * 3.141592653589793},
        {.type = SYMBOL_FUNC_COS},
    };

    for (int i = 0; i < 2; i++) {
        queue_enqueue(&queue, symbols[i]);
    }

    TEST_ASSERT_FALSE(calculate_value(&queue, &result));
    TEST_ASSERT_EQUAL(1, result);
}

void test_tan_function() {
    double result = 0;
    SymbolQueue queue = {0};
    queue_init(&queue);

    Symbol symbols[2] = {
        {.type = SYMBOL_LITERAL, .literal = 0.25 * 3.141592653589793},
        {.type = SYMBOL_FUNC_TAN},
    };

    for (int i = 0; i < 2; i++) {
        queue_enqueue(&queue, symbols[i]);
    }

    TEST_ASSERT_FALSE(calculate_value(&queue, &result));
    TEST_ASSERT(result > 0.999);
    TEST_ASSERT(result < 1.001);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_expression_has_the_right_result);
    RUN_TEST(test_signed_numeric_literals);
    RUN_TEST(test_signed_numeric_literals_advanced);
    RUN_TEST(test_double_minus_in_the_middle);
    RUN_TEST(test_fails_on_invalid_rpn_basic);
    RUN_TEST(test_fails_on_invalid_rpn_more_symbols);
    RUN_TEST(test_division_by_zero_fails);
    RUN_TEST(test_fails_on_invalid_rpn_leftover_symbols);
    RUN_TEST(test_fails_on_invalid_rpn_other_operators);
    RUN_TEST(test_fails_on_function_with_wrong_number_of_params);
    RUN_TEST(test_fails_on_undefined_function);
    RUN_TEST(test_calculate_with_variables);
    RUN_TEST(test_invalid_operator_fails);
    RUN_TEST(test_function_with_one_operand);
    RUN_TEST(test_function_with_two_operands);
    RUN_TEST(test_tan_function);
    RUN_TEST(test_cos_function);

    return UNITY_END();
}
