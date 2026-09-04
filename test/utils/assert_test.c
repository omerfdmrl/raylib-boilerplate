#include "unity.h"
#include "assert.h"

static void test_assert_passes(void);
static void test_assert_msg_passes(void);

void assert_tests(void) {
    RUN_TEST(test_assert_passes);
    RUN_TEST(test_assert_msg_passes);
}

static void test_assert_passes(void) {
    ASSERT(1 == 1);
    TEST_ASSERT_TRUE(1);
}

static void test_assert_msg_passes(void) {
    ASSERT_MSG(2 + 2 == 4, "Math is broken");
    TEST_ASSERT_TRUE(1);
}
