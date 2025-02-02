#include "./core.h"

object_core *object_core_alloc(char *name) {
    object_core *object;

    object = (object_core*) MALLOC(sizeof(object_core));
    ASSERT_MSG(object != NULL, "Object allocation failed");

    object->name = MALLOC(strlen(name) + 1);
    ASSERT_MSG(object->name != NULL, "Object name allocation failed");

    strcpy(object->name, name);

    linked_list_insert(&g_objects, name, object);

    return (object);
}

void object_core_free(object_core *object) {
    object->destroy();
    FREE(object->name);
    FREE(object);
}
