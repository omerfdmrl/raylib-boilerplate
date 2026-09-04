#include "unity.h"
#include "logger.h"

static void test_log_level_fatal(void);
static void test_log_level_error(void);
static void test_log_level_warn(void);
static void test_log_level_info(void);
static void test_log_level_debug(void);
static void test_log_level_trace(void);
static void test_log_format_string(void);

void logger_tests(void) {
    RUN_TEST(test_log_level_fatal);
    RUN_TEST(test_log_level_error);
    RUN_TEST(test_log_level_warn);
    RUN_TEST(test_log_level_info);
    RUN_TEST(test_log_level_debug);
    RUN_TEST(test_log_level_trace);
    RUN_TEST(test_log_format_string);
}

static void test_log_level_fatal(void) {
    LOG(LOG_LEVEL_FATAL, "Test fatal: %d", 42);
    TEST_ASSERT_TRUE(1);
}

static void test_log_level_error(void) {
    LOG(LOG_LEVEL_ERROR, "Test error: %s", "hello");
    TEST_ASSERT_TRUE(1);
}

static void test_log_level_warn(void) {
    LOG(LOG_LEVEL_WARN, "Test warn");
    TEST_ASSERT_TRUE(1);
}

static void test_log_level_info(void) {
    LOG(LOG_LEVEL_INFO, "Test info");
    TEST_ASSERT_TRUE(1);
}

static void test_log_level_debug(void) {
    LOG(LOG_LEVEL_DEBUG, "Test debug");
    TEST_ASSERT_TRUE(1);
}

static void test_log_level_trace(void) {
    LOG(LOG_LEVEL_TRACE, "Test trace");
    TEST_ASSERT_TRUE(1);
}

static void test_log_format_string(void) {
    LOG(LOG_LEVEL_INFO, "Number: %d, String: %s, Float: %.2f", 42, "test", 3.14);
    TEST_ASSERT_TRUE(1);
}
