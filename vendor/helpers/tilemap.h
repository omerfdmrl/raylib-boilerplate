#ifndef HELPER_TILEMAP_H

#define HELPER_TILEMAP_H

#include "../common.h"
#include "../global.h"
#include "../utils/hashmap.h"
#include "cJSON.h"

struct s_tilemap {
    uint16 width;
    uint16 height;
    uint16 tile_height;
    uint16 tile_width;
    uint16 layers_size;
    uint16 *data;
    uint8 *collisions;
    cJSON *layers;
    hash_map *assets;
};

typedef struct s_tilemap tilemap;

tilemap *tilemap_load(const char *path, const char *asset_path);
void tilemap_draw_layer(tilemap *map, uint16 layer);
void tilemap_draw(tilemap *map);
void tilemap_free(tilemap *map);
bool tilemap_check_collision(tilemap *map, Vector2 position, float margin);
Vector2 world_to_tile(tilemap *map, Vector2 position);
Vector2 tile_to_world(tilemap *map, Vector2 position);
uint16 tilemap_get_tile(tilemap *map, Vector2 position, float margin, uint16 layer);

#endif // !HELPER_TILEMAP_H