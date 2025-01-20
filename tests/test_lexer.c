#include "../src/external/unity.h"
#include "../src/lexer.h"
#include <stdio.h>

void setUp() {}

void tearDown() {}

void test_idk() {
    // DynamicPointerArray symbol = {0};
    // dparray_init(&symbol);
    //
    // char *src_string = "123+abc123 + 456";
    // divide_into_symbols(src_string, &symbol);
    //
    // for (int i = 0; i < symbol.__used; i++) {
    //     printf("%s\n", (char *)symbol.__array[i]);
    // }
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_idk);
    return UNITY_END();
}
