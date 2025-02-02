#include "tilemap.h"

void load_tilemap_path(tilemap *map, cJSON *path_json) {
    cJSON *layers, *layer, *data, *properties, *properties_item, *properties_name, *properties_value;
    bool has_collision;
    uint16 tile_id;

    layers = cJSON_GetObjectItem(path_json, "layers");

    map->width = (uint16) cJSON_GetObjectItem(path_json, "width")->valueint;
    map->height = (uint16) cJSON_GetObjectItem(path_json, "height")->valueint;
    map->tile_width = (uint16) cJSON_GetObjectItem(path_json, "tilewidth")->valueint;
    map->tile_height = (uint16) cJSON_GetObjectItem(path_json, "tileheight")->valueint;
    map->layers_size = (uint16) cJSON_GetArraySize(layers);

    map->data = (uint16 *) MALLOC(map->layers_size * map->width * map->height * sizeof(uint16));
    ASSERT_MSG(map->data != NULL, "Tilemap data allocation failed");

    map->collisions = (uint8 *) CALLOC(map->layers_size * map->width * map->height, sizeof(uint8));
    ASSERT_MSG(map->collisions != NULL, "Tilemap collisions allocation failed");

    for (size_t i = 0; i < map->layers_size; i++) {
        has_collision = false;
        layer = cJSON_GetArrayItem(layers, i);
        data = cJSON_GetObjectItem(layer, "data");
        properties = cJSON_GetObjectItem(layer, "properties");
        for (size_t j = 0; j < cJSON_GetArraySize(properties); j++) {
            properties_item = cJSON_GetArrayItem(properties, j);
            properties_name = cJSON_GetObjectItem(properties_item, "name");
            properties_value = cJSON_GetObjectItem(properties_item, "value");
            if(strcmp(properties_name->valuestring, "collision") == 0 &&
                (cJSON_IsBool(properties_value) && cJSON_IsTrue(properties_value)))
                has_collision = true;
        }
        
        for (size_t j = 0; j < cJSON_GetArraySize(data); j++) {
            tile_id = (uint16) cJSON_GetArrayItem(data, j)->valueint;
            map->data[i * map->width * map->height + j] = tile_id;
            if (has_collision && tile_id != 0)
                map->collisions[i * map->width * map->height + j] = 1;
        }
    }

    map->layers = cJSON_Duplicate(layers, 1);
};

void load_tilemap_assets(tilemap *map, cJSON *assets_json) {
    cJSON *tiles, *tile;
    hash_map *hashmap;
    int32 tiles_size, id;
    char *image, *image_asset_path, id_char[10];

    tiles = cJSON_GetObjectItem(assets_json, "tiles");
    tiles_size = cJSON_GetArraySize(tiles);

    hashmap = hashmap_alloc(tiles_size);

    for (size_t i = 0; i < tiles_size; i++) {
        tile = cJSON_GetArrayItem(tiles, i);

        id = cJSON_GetObjectItem(tile, "id")->valueint;
        image = cJSON_GetObjectItem(tile, "image")->valuestring;

        Texture2D *texture = (Texture2D *) MALLOC(sizeof(Texture2D));
        ASSERT_MSG(texture != NULL, "Texture allocation failed");

        sprintf(id_char, "%d", id);
        image_asset_path = path_assets(image);
        *texture = LoadTexture(image_asset_path);
        FREE(image_asset_path);
        hashmap_insert(hashmap, id_char, texture);
    }
    
    map->assets = hashmap;
}

tilemap *tilemap_load(const char *path, const char *assets_path) {
    char *path_text, *assets_text;
    cJSON *path_json, *assets_json;
    tilemap *map;

    path_text = LoadFileText(path);
    ASSERT_MSG(path_text != NULL, "Tilemap path could not readed");

    assets_text = LoadFileText(assets_path);
    ASSERT_MSG(path_text != NULL, "Assets path could not readed");

    path_json = cJSON_Parse(path_text);
    ASSERT_MSG(path_json != NULL, "Tilemap data could not parsed");

    assets_json = cJSON_Parse(assets_text);
    ASSERT_MSG(assets_json != NULL, "Assets data could not parsed");

    map = (tilemap *) MALLOC(sizeof(tilemap));
    ASSERT_MSG(map != NULL, "Tilemap allocation failed");

    load_tilemap_path(map, path_json);
    load_tilemap_assets(map, assets_json);

    UnloadFileText(path_text);
    UnloadFileText(assets_text);
    cJSON_Delete(path_json);
    cJSON_Delete(assets_json);

    return map; 
}

void tilemap_draw_layer(tilemap *map, uint16 layer) {
    uint32 tile_id;
    float screen_x, screen_y;
    Texture2D *texture;
    Vector2 screen_position;
    char tile_id_char[10];

    for (size_t y = 0; y < map->height; y++) {
        for (size_t x = 0; x < map->width; x++) {
            tile_id = map->data[layer * map->width * map->height + y * map->width + x];
            if (tile_id == 0) continue;

            sprintf(tile_id_char, "%d", tile_id - 1);
            texture = (Texture2D *) hashmap_search(map->assets, tile_id_char);

            if (texture != NULL) {
                screen_position = tile_to_world(map, (Vector2) {.x=x, .y=y});
                DrawTexture(*texture, screen_position.x, screen_position.y, WHITE);
            } else
                TraceLog(LOG_WARNING, "Texture not found for tile ID: %s", tile_id_char);
        }
    }
}

void tilemap_draw(tilemap *map) {
    for (size_t i = 0; i < map->layers_size; i++) {
        tilemap_draw_layer(map, i);
    }
}

void tilemap_destroy_callback(hash_node *item) {
    UnloadTexture(*((Texture2D *) item->value));
    FREE(item->value);
}

void tilemap_free(tilemap *map) {
    cJSON_Delete(map->layers);
    hashmap_apply(map->assets, tilemap_destroy_callback);
    hashmap_free(map->assets);
    FREE(map->data);
    FREE(map->collisions);
    FREE(map);
}

Vector2 tile_to_world(tilemap *map, Vector2 position) {
    float x = (position.x - position.y) * (map->tile_width / 2.0f);
    float y = (position.x + position.y) * (map->tile_height / 2.0f);
    return (Vector2){x, y};
}

Vector2 world_to_tile(tilemap *map, Vector2 position) {
    float tile_x = (position.x / (map->tile_width / 2.0f) + position.y / (map->tile_height / 2.0f)) / 2.0f;
    float tile_y = (position.y / (map->tile_height / 2.0f) - position.x / (map->tile_width / 2.0f)) / 2.0f;
    return (Vector2){tile_x, tile_y};
}

bool tilemap_check_collision_layer(tilemap *map, Vector2 position, float margin, uint16 layer) {
    Vector2 tile_pos = world_to_tile(map, position);
    int tile_x = (int)(tile_pos.x + margin);
    int tile_y = (int)(tile_pos.y + margin);

    if (tile_x < 0 || tile_x >= map->width || tile_y < 0 || tile_y >= map->height)
        return false;

    uint16 index = layer * map->width * map->height + tile_y * map->width + tile_x;
    if (map->collisions[index])
        return true;

    return false;
}

bool tilemap_check_collision(tilemap *map, Vector2 position, float margin) {
    for (uint16 layer = 0; layer < map->layers_size; layer++) {
        if(tilemap_check_collision_layer(map, position, margin, layer)) return true;
    }
    return false;
}

uint16 tilemap_get_tile(tilemap *map, Vector2 position, float margin, uint16 layer) {
    Vector2 tile_pos = world_to_tile(map, position);
    int tile_x = (int)(tile_pos.x + margin);
    int tile_y = (int)(tile_pos.y + margin);

    if (tile_x < 0 || tile_x >= map->width || tile_y < 0 || tile_y >= map->height)
        return false;

    uint16 index = layer * map->width * map->height + tile_y * map->width + tile_x;
    
    return index;
}
