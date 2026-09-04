#include "unity.h"

#include "utils/linked_list_test.h"
#include "utils/hashmap_test.h"
#include "utils/logger_test.h"
#include "utils/assert_test.h"
#include "scene/core_test.h"
#include "object/core_test.h"

void setUp(void) {}
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();

    linked_list_tests();
    hashmap_tests();
    logger_tests();
    assert_tests();
    scene_core_tests();
    object_core_tests();

    return UNITY_END();
}
