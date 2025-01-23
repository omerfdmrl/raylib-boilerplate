#include "./status.h"

status g_status = {
    .scene = 0,
    .running = 1,
    .debug = 0,
    .paused = 0,
    .fullscreen = 0,
    .monitor = 0
};

void scene_change(char *name) {
    scene_core *scene;

    if (g_status.scene && g_status.scene->destroy)
        g_status.scene->destroy();


    scene = (scene_core *) g_scenes.find(&g_scenes, name);
    ASSERT_MSG(scene != NULL, "Scene could not found");

    if (scene->create)
        scene->create();

    g_status.scene = scene;
};

void game_stop() {
    g_status.paused = !g_status.paused;
}

void game_close() {
    g_status.running = 0;
}

void game_fullscreen() {
    ToggleFullscreen();
    g_status.fullscreen = !g_status.fullscreen;
}
