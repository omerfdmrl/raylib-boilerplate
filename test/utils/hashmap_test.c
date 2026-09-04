#include "unity.h"
#include "hashmap.h"

static void test_hashmap_insert_and_search(void);
static void test_hashmap_search_nonexistent(void);
static void test_hashmap_delete(void);
static void test_hashmap_delete_nonexistent(void);
static void test_hashmap_overwrite(void);
static void test_hashmap_collision(void);
static void test_hashmap_empty(void);
static void test_hashmap_function_consistency(void);
static void test_hashmap_function_range(void);
static void test_hashmap_apply_calls_all(void);

void hashmap_tests(void) {
    RUN_TEST(test_hashmap_insert_and_search);
    RUN_TEST(test_hashmap_search_nonexistent);
    RUN_TEST(test_hashmap_delete);
    RUN_TEST(test_hashmap_delete_nonexistent);
    RUN_TEST(test_hashmap_overwrite);
    RUN_TEST(test_hashmap_collision);
    RUN_TEST(test_hashmap_empty);
    RUN_TEST(test_hashmap_function_consistency);
    RUN_TEST(test_hashmap_function_range);
    RUN_TEST(test_hashmap_apply_calls_all);
}

static int hm_apply_counter = 0;
static void hm_apply_fn(hash_node *item) {
    (void)item;
    hm_apply_counter++;
}

static void test_hashmap_insert_and_search(void) {
    hash_map *mp = hashmap_alloc(16);
    int val1 = 42, val2 = 99;

    hashmap_insert(mp, "alpha", &val1);
    hashmap_insert(mp, "beta", &val2);

    TEST_ASSERT_EQUAL_PTR(&val1, hashmap_search(mp, "alpha"));
    TEST_ASSERT_EQUAL_PTR(&val2, hashmap_search(mp, "beta"));

    hashmap_free(mp);
}

static void test_hashmap_search_nonexistent(void) {
    hash_map *mp = hashmap_alloc(16);

    TEST_ASSERT_NULL(hashmap_search(mp, "missing"));

    hashmap_free(mp);
}

static void test_hashmap_delete(void) {
    hash_map *mp = hashmap_alloc(16);
    int val = 42;

    hashmap_insert(mp, "key", &val);
    hashmap_delete(mp, "key");

    TEST_ASSERT_NULL(hashmap_search(mp, "key"));
    TEST_ASSERT_EQUAL_INT16(0, mp->size);

    hashmap_free(mp);
}

static void test_hashmap_delete_nonexistent(void) {
    hash_map *mp = hashmap_alloc(16);

    hashmap_delete(mp, "missing");

    TEST_ASSERT_EQUAL_INT16(0, mp->size);
    hashmap_free(mp);
}

static void test_hashmap_overwrite(void) {
    hash_map *mp = hashmap_alloc(16);
    int v1 = 10, v2 = 20;

    hashmap_insert(mp, "key", &v1);
    hashmap_insert(mp, "key", &v2);

    TEST_ASSERT_EQUAL_PTR(&v2, hashmap_search(mp, "key"));
    TEST_ASSERT_EQUAL_INT16(1, mp->size);

    hashmap_free(mp);
}

static void test_hashmap_collision(void) {
    hash_map *mp = hashmap_alloc(2);
    int v1 = 1, v2 = 2, v3 = 3;

    hashmap_insert(mp, "a", &v1);
    hashmap_insert(mp, "b", &v2);
    hashmap_insert(mp, "c", &v3);

    TEST_ASSERT_EQUAL_PTR(&v1, hashmap_search(mp, "a"));
    TEST_ASSERT_EQUAL_PTR(&v2, hashmap_search(mp, "b"));
    TEST_ASSERT_EQUAL_PTR(&v3, hashmap_search(mp, "c"));

    hashmap_free(mp);
}

static void test_hashmap_empty(void) {
    hash_map *mp = hashmap_alloc(8);

    TEST_ASSERT_EQUAL_INT16(0, mp->size);
    TEST_ASSERT_NULL(hashmap_search(mp, "anything"));

    hashmap_free(mp);
}

static void test_hashmap_function_consistency(void) {
    hash_map *mp = hashmap_alloc(64);

    int h1 = hashmap_function(mp, "hello");
    int h2 = hashmap_function(mp, "hello");

    TEST_ASSERT_EQUAL_INT(h1, h2);
    hashmap_free(mp);
}

static void test_hashmap_function_range(void) {
    hash_map *mp = hashmap_alloc(32);

    int h = hashmap_function(mp, "test_key");
    TEST_ASSERT_TRUE(h >= 0 && h < 32);

    hashmap_free(mp);
}

static void test_hashmap_apply_calls_all(void) {
    hash_map *mp = hashmap_alloc(16);
    int v1 = 1, v2 = 2, v3 = 3;

    hashmap_insert(mp, "x", &v1);
    hashmap_insert(mp, "y", &v2);
    hashmap_insert(mp, "z", &v3);

    hm_apply_counter = 0;
    hashmap_apply(mp, hm_apply_fn);

    TEST_ASSERT_EQUAL_INT(3, hm_apply_counter);
    hashmap_free(mp);
}
