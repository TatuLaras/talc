#include "../src/external/unity.h"
#include "../src/infix_to_postfix.h"
#include "../src/queue.h"
#include <string.h>

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

void test_fails_with_invalid_characters_in_input() {
    char *expression = "15  !? +  540     / 3*100001^2";
    TEST_ASSERT(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
}

void test_fails_with_unmatching_parenthesis() {
    char *expression = "(4 + ((15+9))";
    TEST_ASSERT(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
}

void test_fails_with_unmatching_parenthesis_right() {
    char *expression = "((15+9)) + 3)";
    TEST_ASSERT(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
}

void test_does_not_fail_with_matching_parenthesis() {
    char *expression = "(((15+9)))";
    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));

    int i = 0;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(15, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(9, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].type);
}

void test_converts_correctly_basic_operations_with_integers() {
    char *expression = "15   +  540     / 3*  100001 ^2";

    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
    TEST_ASSERT_EQUAL(9, symbols.__used);

    // Correct RPN: 15 540 3 / 100001 2 ^ * +

    int i = 0;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(15, symbols.__array[i].literal);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(540, symbols.__array[i].literal);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(3, symbols.__array[i].literal);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_OP_DIVISION, symbols.__array[i].type);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(100001, symbols.__array[i].literal);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(2, symbols.__array[i].literal);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_OP_EXPONENT, symbols.__array[i].type);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_OP_MULTIPLICATION, symbols.__array[i].type);
    i++;

    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].type);
}

void test_converts_correctly_parenthesis() {
    char *expression = " (5 + 3) * (12 / 4) - 7^2 ";
    // Correct RPN: 5 3 + 12 4 / * 7 2 ^ -
    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
    TEST_ASSERT_EQUAL(11, symbols.__used);

    int i = 0;
    // --
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(5, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(3, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(12, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(4, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_DIVISION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_MULTIPLICATION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(7, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(2, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_EXPONENT, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_SUBTRACTION, symbols.__array[i].type);
}

void test_coverts_correctly_decimal_literals() {
    char *expression = "(6 + 3.5) * 2.6^3.123 - 9 / 3";
    // Correct RPN: 6 3.5 + 2.6 3.123 ^ * 9 3 / -

    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
    TEST_ASSERT_EQUAL(11, symbols.__used);

    int i = 0;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(6, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(3.5, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(2.6, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(3.123, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_EXPONENT, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_MULTIPLICATION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(9, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(3, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_DIVISION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_SUBTRACTION, symbols.__array[i].type);
}

void test_coverts_correctly_nested_parenthesis() {
    char *expression = "(5^2 + (5*(5+2)) / (2 + 3)) - 4";
    // Correct RPN: 5 2 ^ 5 5 2 + * 2 3 + / + 4 -

    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
    TEST_ASSERT_EQUAL(15, symbols.__used);

    int i = 0;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(5, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(2, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_EXPONENT, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(5, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(5, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(2, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_MULTIPLICATION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(2, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(3, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_DIVISION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(4, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_SUBTRACTION, symbols.__array[i].type);
    i++;
}

void test_signed_numeric_literals() {
    char *expression = "-5-2+3+-2";
    // Correct RPN: -5 2 - 3 + -2 +

    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
    TEST_ASSERT_EQUAL(7, symbols.__used);

    int i = 0;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(-5, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(2, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_SUBTRACTION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(3, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(-2, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].type);
}

void test_double_minus_at_start() {
    //  NOTE: I decided that --2 should be interpreted as (-(-2)), very unlikely
    //   that someone would use it that way, but I think a calculator should be
    //   as permissible as possible when it comes to stuff like this, with
    //   errors being reserved for situations when there is no way to interpret
    //   the input
    char *expression = "--2+3";
    // RPN: 2 3 +
    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
    TEST_ASSERT_EQUAL(3, symbols.__used);

    int i = 0;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(2, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(3, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].type);
}

void test_number_with_letters_in_it_fails() {
    char *expression = "15+12a3";
    TEST_ASSERT(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
}

void test_using_a_defined_variable_does_not_fail() {
    variables_assign(&variables, "abcd123", 123);

    char *expression = "15+abcd123";
    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));

    int i = 0;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(15, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(123, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[i].type);
}

void test_using_an_undefined_variable_fails() {
    char *expression = "15+abcd123";
    TEST_ASSERT_TRUE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
}

void test_variable_with_dots_in_it_fails() {
    char *expression = "15+abc.def";
    TEST_ASSERT(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
}

void test_using_functions() {
    char *expression = " sin ( max ( 2, 3 ) / 3 * 9 ) ";
    // Correct RPN: 2 3 max 3 / 9 * sin

    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &null_request));
    TEST_ASSERT_EQUAL(8, symbols.__used);

    int i = 0;

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(2, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(3, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_FUNC_MAX, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(3, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_DIVISION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_LITERAL, symbols.__array[i].type);
    TEST_ASSERT_EQUAL(9, symbols.__array[i].literal);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_OP_MULTIPLICATION, symbols.__array[i].type);
    i++;
    TEST_ASSERT_EQUAL(SYMBOL_FUNC_SIN, symbols.__array[i].type);
    i++;
}

void test_variable_assignment() {
    VariableAssignmentRequest request = {0};
    char *expression = "nameofvariable123=15+3";
    TEST_ASSERT_FALSE(
        infix_to_postfix(expression, &variables, &symbols, &request));
    TEST_ASSERT_TRUE(request.valid);
    TEST_ASSERT(strcmp("nameofvariable123", request.name) == 0);
}

void test_multiple_variable_assignments_fails() {
    VariableAssignmentRequest request = {0};
    char *expression = "nameofvariable123=another=15+3";
    TEST_ASSERT_TRUE(
        infix_to_postfix(expression, &variables, &symbols, &request));
}

void test_numeric_variable_assignments_fails() {
    VariableAssignmentRequest request = {0};
    char *expression = "123=15+3";
    TEST_ASSERT_TRUE(
        infix_to_postfix(expression, &variables, &symbols, &request));
    TEST_ASSERT_FALSE(request.valid);
}

void test_invalid_variable_assignments_fails() {
    VariableAssignmentRequest request = {0};
    char *expression = "sin+2=15+3";
    TEST_ASSERT_TRUE(
        infix_to_postfix(expression, &variables, &symbols, &request));
    TEST_ASSERT_FALSE(request.valid);
}

//  TODO: -(-2)+3
//  TODO: 3-(-(-2))

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
    RUN_TEST(test_signed_numeric_literals);
    RUN_TEST(test_double_minus_at_start);
    RUN_TEST(test_number_with_letters_in_it_fails);
    RUN_TEST(test_using_a_defined_variable_does_not_fail);
    RUN_TEST(test_variable_with_dots_in_it_fails);
    RUN_TEST(test_using_functions);
    RUN_TEST(test_using_an_undefined_variable_fails);
    RUN_TEST(test_variable_assignment);
    RUN_TEST(test_multiple_variable_assignments_fails);
    RUN_TEST(test_numeric_variable_assignments_fails);
    RUN_TEST(test_invalid_variable_assignments_fails);

    return UNITY_END();
}
