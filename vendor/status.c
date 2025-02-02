#include "./status.h"

status g_status = {
    .scene = 0,
    .running = 1,
    .debug = 0,
    .paused = 0,
    .fullscreen = 0,
    .monitor = 0,
};

void scene_change(char *name, bool call_destroy, bool call_create) {
    scene_core *scene;

    if (g_status.scene && g_status.scene->destroy && call_destroy)
        g_status.scene->destroy();

    scene = (scene_core *) linked_list_find(&g_scenes, name);
    ASSERT_MSG(scene != NULL, "Scene could not found");

    if (scene->create && call_create)
        scene->create();

    g_status.scene = scene;
};

void game_pause() {
    g_status.paused = !g_status.paused;
}

void linked_list_scene_destroy_callback(linked_list_item *item) {
    scene_core * item_core = ((scene_core *) item->data);
    scene_core_free(item_core);
};
void linked_list_data_destroy_callback(linked_list_item *item) {
    void* item_core = item->data;
    FREE(item_core);
};
void linked_list_object_destroy_callback(linked_list_item *item) {
    object_core * item_core = ((object_core *) item->data);
    object_core_free(item_core);
};

void game_close() {
    g_status.running = 0;
    
    linked_list_apply(&g_scenes, linked_list_scene_destroy_callback);
    linked_list_clear(&g_scenes);

    linked_list_apply(&g_data, linked_list_data_destroy_callback);
    linked_list_clear(&g_data);

    linked_list_apply(&g_objects, linked_list_object_destroy_callback);
    linked_list_clear(&g_objects);

    UnloadFont(g_config.font);
}

void game_fullscreen() {
    ToggleFullscreen();
    g_status.fullscreen = !g_status.fullscreen;
}
