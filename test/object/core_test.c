#include "unity.h"
#include "object/core.h"
#include "status.h"
#include "global.h"

static void test_object_core_alloc(void);
static void test_object_core_stored_in_global(void);
static void test_object_core_free(void);

void object_core_tests(void) {
    RUN_TEST(test_object_core_alloc);
    RUN_TEST(test_object_core_stored_in_global);
    RUN_TEST(test_object_core_free);
}

static void test_object_core_alloc(void) {
    object_core *obj = object_core_alloc("test_object");

    TEST_ASSERT_NOT_NULL(obj);
    TEST_ASSERT_EQUAL_STRING("test_object", obj->name);

    object_core_free(obj);
}

static void test_object_core_stored_in_global(void) {
    object_core *obj = object_core_alloc("obj_global_test");

    void *found = linked_list_find(&g_objects, "obj_global_test");
    TEST_ASSERT_EQUAL_PTR(obj, found);

    object_core_free(obj);
}

static void test_object_core_free(void) {
    object_core *obj = object_core_alloc("obj_free_test");

    object_core_free(obj);

    TEST_ASSERT_NULL(linked_list_find(&g_objects, "obj_free_test"));
}
