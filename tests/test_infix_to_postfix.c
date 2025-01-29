#include "../src/external/unity.h"
#include "../src/infix_to_postfix.h"
#include "../src/queue.h"

static SymbolQueue symbols = {0};

void setUp() { queue_init(&symbols); }

void tearDown() { queue_free(&symbols); }

void test_fails_with_invalid_characters_in_input() {
    char *expression = "15  !? +  540     / 3*100001^2";
    TEST_ASSERT(str_to_symbols_postfix(expression, &symbols));
}

void test_fails_with_unmatching_parenthesis() {
    char *expression = "(4 + ((15+9))";
    TEST_ASSERT(str_to_symbols_postfix(expression, &symbols));
}

void test_fails_with_unmatching_parenthesis_right() {
    char *expression = "((15+9)) + 3)";
    TEST_ASSERT(str_to_symbols_postfix(expression, &symbols));
}

void test_does_not_fail_with_matching_parenthesis() {
    char *expression = "(((15+9)))";
    TEST_ASSERT_FALSE(str_to_symbols_postfix(expression, &symbols));

    int i = 0;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(15, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(9, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].symbol_type);
}

void test_converts_correctly_basic_operations_with_integers() {
    char *expression = "15   +  540     / 3*  100001 ^2";

    TEST_ASSERT_FALSE(str_to_symbols_postfix(expression, &symbols));
    TEST_ASSERT_EQUAL(9, symbols.__used);

    // Correct RPN: 15 540 3 / 100001 2 ^ * +

    int i = 0;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(15, symbols.__array[i].literal);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(540, symbols.__array[i].literal);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(3, symbols.__array[i].literal);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_OP_DIVISION, symbols.__array[i].symbol_type);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(100001, symbols.__array[i].literal);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(2, symbols.__array[i].literal);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_OP_EXPONENT, symbols.__array[i].symbol_type);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_OP_MULTIPLICATION, symbols.__array[i].symbol_type);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].symbol_type);
}

void test_converts_correctly_parenthesis() {
    char *expression = " (5 + 3) * (12 / 4) - 7^2 ";
    // Correct RPN: 5 3 + 12 4 / * 7 2 ^ -
    TEST_ASSERT_FALSE(str_to_symbols_postfix(expression, &symbols));
    TEST_ASSERT_EQUAL(11, symbols.__used);

    int i = 0;
    // --
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(5, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(3, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(12, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(4, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_DIVISION, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_MULTIPLICATION, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(7, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(2, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_EXPONENT, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_SUBTRACTION, symbols.__array[i].symbol_type);
}

void test_coverts_correctly_decimal_literals() {
    char *expression = "(6 + 3.5) * 2.6^3.123 - 9 / 3";
    // Correct RPN: 6 3.5 + 2.6 3.123 ^ * 9 3 / -

    TEST_ASSERT_FALSE(str_to_symbols_postfix(expression, &symbols));
    TEST_ASSERT_EQUAL(11, symbols.__used);

    int i = 0;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(6, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(3.5, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(2.6, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(3.123, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_EXPONENT, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_MULTIPLICATION, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(9, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(3, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_DIVISION, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_SUBTRACTION, symbols.__array[i].symbol_type);
}

void test_coverts_correctly_nested_parenthesis() {
    char *expression = "(5^2 + (5*(5+2)) / (2 + 3)) - 4";
    // Correct RPN: 5 2 ^ 5 5 2 + * 2 3 + / + 4 -

    TEST_ASSERT_FALSE(str_to_symbols_postfix(expression, &symbols));
    TEST_ASSERT_EQUAL(15, symbols.__used);

    int i = 0;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(5, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(2, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_EXPONENT, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(5, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(5, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(2, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_MULTIPLICATION, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(2, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(3, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_DIVISION, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].symbol_type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].symbol_type);
    TEST_ASSERT_EQUAL(4, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_SUBTRACTION, symbols.__array[i].symbol_type);
    i++;
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_fails_with_invalid_characters_in_input);
    RUN_TEST(test_converts_correctly_basic_operations_with_integers);
    RUN_TEST(test_converts_correctly_parenthesis);
    RUN_TEST(test_coverts_correctly_decimal_literals);
    RUN_TEST(test_fails_with_unmatching_parenthesis);
    RUN_TEST(test_fails_with_unmatching_parenthesis_right);
    RUN_TEST(test_does_not_fail_with_matching_parenthesis);
    RUN_TEST(test_coverts_correctly_nested_parenthesis);

    return UNITY_END();
}
