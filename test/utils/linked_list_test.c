#include "unity.h"
#include "linked_list.h"

static void test_linked_list_insert_and_find(void);
static void test_linked_list_find_nonexistent(void);
static void test_linked_list_upsert(void);
static void test_linked_list_erase(void);
static void test_linked_list_erase_nonexistent(void);
static void test_linked_list_clear(void);
static void test_linked_list_insert_order(void);
static void test_linked_list_apply_calls_all(void);

void linked_list_tests(void) {
    RUN_TEST(test_linked_list_insert_and_find);
    RUN_TEST(test_linked_list_find_nonexistent);
    RUN_TEST(test_linked_list_upsert);
    RUN_TEST(test_linked_list_erase);
    RUN_TEST(test_linked_list_erase_nonexistent);
    RUN_TEST(test_linked_list_clear);
    RUN_TEST(test_linked_list_insert_order);
    RUN_TEST(test_linked_list_apply_calls_all);
}

static int ll_apply_counter = 0;
static void ll_apply_fn(linked_list_item *item) {
    (void)item;
    ll_apply_counter++;
}

static void test_linked_list_insert_and_find(void) {
    linked_list list = { .head = NULL, .size = 0 };
    int val1 = 42, val2 = 99;

    linked_list_insert(&list, "first", &val1);
    linked_list_insert(&list, "second", &val2);

    TEST_ASSERT_EQUAL_PTR(&val1, linked_list_find(&list, "first"));
    TEST_ASSERT_EQUAL_PTR(&val2, linked_list_find(&list, "second"));
    TEST_ASSERT_EQUAL_UINT64(2, list.size);
}

static void test_linked_list_find_nonexistent(void) {
    linked_list list = { .head = NULL, .size = 0 };

    TEST_ASSERT_NULL(linked_list_find(&list, "missing"));
}

static void test_linked_list_upsert(void) {
    linked_list list = { .head = NULL, .size = 0 };
    int val1 = 10, val2 = 20;

    linked_list_insert(&list, "key", &val1);
    linked_list_insert(&list, "key", &val2);

    TEST_ASSERT_EQUAL_PTR(&val2, linked_list_find(&list, "key"));
    TEST_ASSERT_EQUAL_UINT64(1, list.size);
}

static void test_linked_list_erase(void) {
    linked_list list = { .head = NULL, .size = 0 };
    int val = 42;

    linked_list_insert(&list, "key", &val);
    linked_list_erase(&list, "key");

    TEST_ASSERT_NULL(linked_list_find(&list, "key"));
    TEST_ASSERT_EQUAL_UINT64(0, list.size);
}

static void test_linked_list_erase_nonexistent(void) {
    linked_list list = { .head = NULL, .size = 0 };

    linked_list_erase(&list, "missing");
    TEST_ASSERT_EQUAL_UINT64(0, list.size);
}

static void test_linked_list_clear(void) {
    linked_list list = { .head = NULL, .size = 0 };
    int v1 = 1, v2 = 2, v3 = 3;

    linked_list_insert(&list, "a", &v1);
    linked_list_insert(&list, "b", &v2);
    linked_list_insert(&list, "c", &v3);

    linked_list_clear(&list);

    TEST_ASSERT_NULL(list.head);
    TEST_ASSERT_EQUAL_UINT64(0, list.size);
}

static void test_linked_list_insert_order(void) {
    linked_list list = { .head = NULL, .size = 0 };
    int v1 = 1, v2 = 2;

    linked_list_insert(&list, "first", &v1);
    linked_list_insert(&list, "second", &v2);

    linked_list_item *head = list.head;
    TEST_ASSERT_EQUAL_STRING("second", head->key);
    TEST_ASSERT_EQUAL_STRING("first", head->next->key);
}

static void test_linked_list_apply_calls_all(void) {
    linked_list list = { .head = NULL, .size = 0 };
    int v1 = 1, v2 = 2, v3 = 3;

    linked_list_insert(&list, "a", &v1);
    linked_list_insert(&list, "b", &v2);
    linked_list_insert(&list, "c", &v3);

    ll_apply_counter = 0;
    linked_list_apply(&list, ll_apply_fn);

    TEST_ASSERT_EQUAL_INT(3, ll_apply_counter);
    linked_list_clear(&list);
}
