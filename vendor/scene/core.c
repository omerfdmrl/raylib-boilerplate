#include "./core.h"

scene_core *scene_core_alloc(char *name) {
    scene_core *scene;

    scene = (scene_core*) MALLOC(sizeof(scene_core));
    ASSERT_MSG(scene != NULL, "Scene allocation failed");

    scene->name = MALLOC(strlen(name) + 1);
    ASSERT_MSG(scene->name != NULL, "Scene name allocation failed");

    strcpy(scene->name, name);

    g_scenes.insert(&g_scenes, name, scene);

    return (scene);
};

void scene_core_free(scene_core *scene) {
    FREE(scene->name);
    FREE(scene);
}