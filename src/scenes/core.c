#include "core.h"

scene_core *scene_core_alloc(uint8 id) {
    scene_core *scene;

    scene = (scene_core*) MALLOC(sizeof(scene_core));
    ASSERT_MSG(scene != NULL, "Scene allocation failed");

    scene->id = id;

    return (scene);
};

void scene_core_free(scene_core *scene) {
    FREE(scene);
}