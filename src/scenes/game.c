#include "game.h"

Camera2D camera = {0};
tilemap *tile_map = NULL;

void scene_game_create() {
    if (tile_map == NULL) {
        char *tilemap_asset_path, *assets_asset_path;
        
        tilemap_asset_path = path_assets("tilemap.json");
        assets_asset_path = path_assets("assets.json");

        tile_map = tilemap_load(tilemap_asset_path, assets_asset_path);
        linked_list_insert(&g_data, "tilemap", tile_map);

        FREE(tilemap_asset_path);
        FREE(assets_asset_path);

        LOG(LOG_LEVEL_DEBUG, "tile_map created");
    } else LOG(LOG_LEVEL_WARN, "tile_map tried to calling twice");

    if (linked_list_find(&g_data, "camera") == NULL) {
        camera.offset = (Vector2){ g_config.window_width / 2.0f, g_config.window_height / 2.0f };
        camera.zoom = 1.0f;
        linked_list_insert(&g_data, "camera", &camera);
        LOG(LOG_LEVEL_DEBUG, "camera created");
    } else LOG(LOG_LEVEL_WARN, "camera tried to calling twice");
}

void scene_game_update() {
    camera.zoom += GetMouseWheelMove() * 0.05f;

    BeginMode2D(camera);
        // Insert your drawings here
    EndMode2D();
}

void scene_game_destroy() {
    if (tile_map != NULL) {
        tilemap_free(tile_map);
        linked_list_erase(&g_data, "tilemap");
        LOG(LOG_LEVEL_DEBUG, "tile_map freed");
    }
    if (linked_list_find(&g_data, "camera") != NULL) {
        linked_list_erase(&g_data, "camera");
    }
}

scene_core *scene_game() {
    scene_core *scene;

    scene = scene_core_alloc("game");
    scene->create = scene_game_create;
    scene->update = scene_game_update;
    scene->destroy = scene_game_destroy;
    
    return (scene);
}