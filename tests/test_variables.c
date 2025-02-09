#include "../src/external/unity.h"
#include "../src/variables.h"
#include <stdio.h>

static VariableStorage var = {0};

void setUp() { variables_init(&var); }

void tearDown() { variables_free(&var); }

void test_assign_and_retrieve() {
    variables_assign(&var, "name123", 117412);
    variables_assign(&var, "ajc91", 81231);
    variables_assign(&var, "mnxj1", 184);
    variables_assign(&var, "bxc1", 95125);
    variables_assign(&var, "mxca8", 456134);
    variables_assign(&var, "masx1", 123123);

    double name123 = 0;
    TEST_ASSERT_FALSE(variables_retrieve(&var, "name123", &name123));
    TEST_ASSERT_EQUAL(117412, name123);

    double ajc91 = 0;
    TEST_ASSERT_FALSE(variables_retrieve(&var, "ajc91", &ajc91));
    TEST_ASSERT_EQUAL(81231, ajc91);

    double mnxj1 = 0;
    TEST_ASSERT_FALSE(variables_retrieve(&var, "mnxj1", &mnxj1));
    TEST_ASSERT_EQUAL(184, mnxj1);

    double bxc1 = 0;
    TEST_ASSERT_FALSE(variables_retrieve(&var, "bxc1", &bxc1));
    TEST_ASSERT_EQUAL(95125, bxc1);

    double mxca8 = 0;
    TEST_ASSERT_FALSE(variables_retrieve(&var, "mxca8", &mxca8));
    TEST_ASSERT_EQUAL(456134, mxca8);

    double masx1 = 0;
    TEST_ASSERT_FALSE(variables_retrieve(&var, "masx1", &masx1));
    TEST_ASSERT_EQUAL(123123, masx1);
}

void test_undefined_variable() {
    variables_assign(&var, "name123", 117412);
    variables_assign(&var, "ajc91", 81231);

    double name123 = 0;
    TEST_ASSERT_FALSE(variables_retrieve(&var, "name123", &name123));
    TEST_ASSERT_EQUAL(117412, name123);

    double ajc91 = 0;
    TEST_ASSERT_FALSE(variables_retrieve(&var, "ajc91", &ajc91));
    TEST_ASSERT_EQUAL(81231, ajc91);

    double mnxj1 = 0;
    TEST_ASSERT_TRUE(variables_retrieve(&var, "mnxj1", &mnxj1));
}

void test_array_should_grow() {
    int initial_size = var.__size;

    TEST_ASSERT_EQUAL(VARIABLES_STARTING_SIZE, initial_size);

    for (int i = 0; i <= initial_size + 1; i++) {
        double item = 0;
        variables_assign(&var, "name", item);
    }

    TEST_ASSERT_EQUAL(initial_size * 2, var.__size);
}

void test_variable_reassignment() {
    variables_assign(&var, "name123", 117412);
    variables_assign(&var, "name123", 81231);
    variables_assign(&var, "mxca8", 456134);

    double name123 = 0;
    TEST_ASSERT_FALSE(variables_retrieve(&var, "name123", &name123));
    TEST_ASSERT_EQUAL(81231, name123);
}

void test_bug_reproduction() {
    variables_assign(&var, "pi", 3.14);
    variables_assign(&var, "e", 2.7);

    double name123 = 0;
    TEST_ASSERT_FALSE(variables_retrieve(&var, "pi", &name123));
    TEST_ASSERT_EQUAL(81231, name123);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_assign_and_retrieve);
    RUN_TEST(test_undefined_variable);
    RUN_TEST(test_array_should_grow);
    RUN_TEST(test_variable_reassignment);

    return UNITY_END();
}
