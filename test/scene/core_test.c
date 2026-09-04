#include "unity.h"
#include "scene/core.h"
#include "status.h"
#include "global.h"

static void test_scene_core_alloc(void);
static void test_scene_core_stored_in_global(void);
static void test_scene_core_lifecycle(void);

void scene_core_tests(void) {
    RUN_TEST(test_scene_core_alloc);
    RUN_TEST(test_scene_core_stored_in_global);
    RUN_TEST(test_scene_core_lifecycle);
}

static void test_scene_core_alloc(void) {
    scene_core *scene = scene_core_alloc("test_scene");

    TEST_ASSERT_NOT_NULL(scene);
    TEST_ASSERT_EQUAL_STRING("test_scene", scene->name);

    scene_core_free(scene);
}

static void test_scene_core_stored_in_global(void) {
    scene_core *scene = scene_core_alloc("global_test");

    void *found = linked_list_find(&g_scenes, "global_test");
    TEST_ASSERT_EQUAL_PTR(scene, found);

    scene_core_free(scene);
}

static void test_scene_core_lifecycle(void) {
    scene_core *scene = scene_core_alloc("lifecycle_test");

    scene_core_free(scene);
    TEST_ASSERT_NULL(linked_list_find(&g_scenes, "lifecycle_test"));
}
