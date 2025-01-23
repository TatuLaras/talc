#include "../src/external/unity.h"
#include "../src/infix_to_postfix.h"
#include "../src/stack.h"

static SymbolStack symbols = {0};

void setUp() { stack_init(&symbols); }

void tearDown() { stack_free(&symbols); }

void test_fails_with_invalid_characters_in_input() {
    char *src_str = "15  !? +  540     / 3*100001^2";
    TEST_ASSERT(str_to_symbols_postfix(src_str, &symbols));
}

void test_converts_correctly_basic_operations_with_integers() {
    char *second_src_str = "15   +  540     / 3*  100001 ^2";

    TEST_ASSERT_FALSE(str_to_symbols_postfix(second_src_str, &symbols));
    TEST_ASSERT_EQUAL(9, symbols.__top);

    // Correct RPN: 15 540 3 / 100001 2 ^ * +

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL_INTEGER, symbols.__array[0].symbol_type);
    TEST_ASSERT_EQUAL(15, symbols.__array[0].literal_integer);

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL_INTEGER, symbols.__array[1].symbol_type);
    TEST_ASSERT_EQUAL(540, symbols.__array[1].literal_integer);

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL_INTEGER, symbols.__array[2].symbol_type);
    TEST_ASSERT_EQUAL(3, symbols.__array[2].literal_integer);

    TEST_ASSERT_EQUAL(SYMBOL_OP_DIVISION, symbols.__array[3].symbol_type);

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL_INTEGER, symbols.__array[4].symbol_type);
    TEST_ASSERT_EQUAL(100001, symbols.__array[4].literal_integer);

    TEST_ASSERT_EQUAL(SYMBOL_LITERAL_INTEGER, symbols.__array[5].symbol_type);
    TEST_ASSERT_EQUAL(2, symbols.__array[5].literal_integer);

    TEST_ASSERT_EQUAL(SYMBOL_OP_EXPONENT, symbols.__array[6].symbol_type);

    TEST_ASSERT_EQUAL(SYMBOL_OP_MULTIPLICATION, symbols.__array[7].symbol_type);

    TEST_ASSERT_EQUAL(SYMBOL_OP_ADDITION, symbols.__array[8].symbol_type);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_fails_with_invalid_characters_in_input);
    RUN_TEST(test_converts_correctly_basic_operations_with_integers);

    return UNITY_END();
}
