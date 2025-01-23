#include "./status.h"

status g_status = {
    .scene = 0,
    .debug = 0,
    .paused = 0
};

void scene_change(char *name) {
    scene_core *scene;

    scene = (scene_core *) g_scenes.find(&g_scenes, name);
    ASSERT_MSG(scene != NULL, "Scene could not found");

    g_status.scene = scene;
};