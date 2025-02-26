#include "../src/external/unity.h"
#include "../src/ui_helpers.h"
#include <string.h>

VariableStorage var = {0};

void setUp() { variables_init(&var); }
void tearDown() { variables_free(&var); }

void test_currently_typed_name_parsed_correctly_simple_case() {
    UserInterface ui = {0};

    char *str = "5+3-hello";
    strcpy(ui.input_buffer, str);
    ui.input_buffer_used = strlen(str);
    ui.input_buffer_cursor = strlen(str);

    char result[100] = {0};
    TEST_ASSERT_FALSE(ui_helper_get_currently_typed_name(&ui, result, 100));
    TEST_ASSERT_EQUAL(0, strcmp("hello", result));
}

void test_currently_typed_name_parsed_correctly_only_name() {
    UserInterface ui = {0};

    char *str = "hello";
    strcpy(ui.input_buffer, str);
    ui.input_buffer_used = strlen(str);
    ui.input_buffer_cursor = strlen(str);

    char result[100] = {0};
    TEST_ASSERT_FALSE(ui_helper_get_currently_typed_name(&ui, result, 100));
    TEST_ASSERT_EQUAL(0, strcmp("hello", result));
}

void test_currently_typed_name_parsed_correctly_complicated_case() {
    UserInterface ui = {0};

    char *str = "5+(hello)+thisshouldbeit";
    strcpy(ui.input_buffer, str);
    ui.input_buffer_used = strlen(str);
    ui.input_buffer_cursor = strlen(str);

    char result[100] = {0};
    TEST_ASSERT_FALSE(ui_helper_get_currently_typed_name(&ui, result, 100));
    TEST_ASSERT_EQUAL(0, strcmp("thisshouldbeit", result));
}

void test_currently_typed_name_fails_on_number() {
    UserInterface ui = {0};

    char *str = "5+3-999";
    strcpy(ui.input_buffer, str);
    ui.input_buffer_used = strlen(str);
    ui.input_buffer_cursor = strlen(str);

    char result[100] = {0};
    TEST_ASSERT(ui_helper_get_currently_typed_name(&ui, result, 100));
}

void test_currently_typed_name_fails_on_operator() {
    UserInterface ui = {0};

    char *str = "5+3+hello-";
    strcpy(ui.input_buffer, str);
    ui.input_buffer_used = strlen(str);
    ui.input_buffer_cursor = strlen(str);

    char result[100] = {0};
    TEST_ASSERT(ui_helper_get_currently_typed_name(&ui, result, 100));
}

void test_currently_typed_name_fails_on_parenthesis() {
    UserInterface ui = {0};

    char *str = "5+3-min(";
    strcpy(ui.input_buffer, str);
    ui.input_buffer_used = strlen(str);
    ui.input_buffer_cursor = strlen(str);

    char result[100] = {0};
    TEST_ASSERT(ui_helper_get_currently_typed_name(&ui, result, 100));
}

void test_currently_typed_name_wont_overflow() {
    UserInterface ui = {0};

    char *str = "5+3-variable13long";
    strcpy(ui.input_buffer, str);
    ui.input_buffer_used = strlen(str);
    ui.input_buffer_cursor = strlen(str);

    char result[100] = {0};
    TEST_ASSERT_FALSE(ui_helper_get_currently_typed_name(&ui, result, 5));
    TEST_ASSERT_FALSE(result[5]);
}

void test_correct_summary_is_returned() {
    char *incomplete = "mi";
    char summary[4] = {0};

    TEST_ASSERT_FALSE(ui_helper_get_summary(incomplete, &var, summary, 3));
    TEST_ASSERT_FALSE(strcmp("min", summary));

    char *incomplete2 = "max";
    char summary2[10] = {0};

    TEST_ASSERT_FALSE(ui_helper_get_summary(incomplete2, &var, summary2, 9));
    TEST_ASSERT_FALSE(strcmp("max(x, y)", summary2));
}

void test_correct_completion_is_returned() {
    char *incomplete = "as";
    char completion[10] = {0};

    TEST_ASSERT_FALSE(
        ui_helper_get_completion(incomplete, &var, completion, 9));
    TEST_ASSERT_FALSE(strcmp("in(", completion));
}

void test_correct_variable_summary_is_returned() {
    variables_assign(&var, "longvariablename", 5.5);

    char *incomplete = "longv";
    char summary[30] = {0};

    TEST_ASSERT_FALSE(ui_helper_get_summary(incomplete, &var, summary, 29));
    TEST_ASSERT_FALSE(strcmp("longvariablename - 5.5", summary));
}

void test_correct_variable_completion_is_returned() {
    variables_assign(&var, "longvariablename", 5.5);

    char *incomplete = "longv";
    char completion[30] = {0};

    int is_function = 0;
    TEST_ASSERT_FALSE(
        ui_helper_get_completion(incomplete, &var, completion, 29));
    TEST_ASSERT_FALSE(strcmp("ariablename", completion));
    TEST_ASSERT_FALSE(is_function);
}

void test_completion_fails_on_no_match() {
    char *incomplete = "longv";
    char completion[1] = {0};
    TEST_ASSERT(ui_helper_get_completion(incomplete, &var, completion, 0));
}

void test_get_summary_fails_on_no_match() {
    char *incomplete = "longv";
    char completion[1] = {0};
    TEST_ASSERT(ui_helper_get_summary(incomplete, &var, completion, 0));
}

void test_get_summary_fails_on_empty_incomplete_name() {
    char *incomplete = "";
    char completion[1] = {0};
    TEST_ASSERT(ui_helper_get_summary(incomplete, &var, completion, 0));
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_currently_typed_name_parsed_correctly_simple_case);
    RUN_TEST(test_currently_typed_name_fails_on_number);
    RUN_TEST(test_currently_typed_name_fails_on_operator);
    RUN_TEST(test_currently_typed_name_fails_on_parenthesis);
    RUN_TEST(test_currently_typed_name_parsed_correctly_complicated_case);
    RUN_TEST(test_correct_summary_is_returned);
    RUN_TEST(test_currently_typed_name_wont_overflow);
    RUN_TEST(test_currently_typed_name_parsed_correctly_only_name);
    RUN_TEST(test_correct_completion_is_returned);
    RUN_TEST(test_correct_variable_summary_is_returned);
    RUN_TEST(test_correct_variable_completion_is_returned);
    RUN_TEST(test_completion_fails_on_no_match);
    RUN_TEST(test_get_summary_fails_on_no_match);
    RUN_TEST(test_get_summary_fails_on_empty_incomplete_name);

    return UNITY_END();
}
