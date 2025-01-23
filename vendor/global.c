#include "./global.h"

map g_scenes = {
    .head = NULL,
    .size = 0,
    .insert = map_insert,
    .find = map_find,
    .erase = map_erase,
    .clear = map_clear
};

float g_delta = 0.0f;
