#ifndef UTIL_MAP_H

#define UTIL_MAP_H

#include "../common.h"

struct s_map_item {
    char *key;
    void *data;
    struct s_map_item *next;
};

struct s_map {
    struct s_map_item *head;
    uint64 size;

    void (*insert)(struct s_map *, const char *, void *);
    void *(*find)(struct s_map *, const char *);
    void (*erase)(struct s_map *, const char *);
    void (*clear)(struct s_map *);
};

typedef struct s_map_item map_item;
typedef struct s_map map;

map_item *map_item_alloc(const char *key, void *data);
void map_item_free(map_item *item);

map *map_alloc();
void map_insert(map *map, const char *key, void *data);
void *map_find(map *map, const char *key);
void map_erase(map *map, const char *key);
void map_clear(map *map);
void map_free(map *map);

#endif // !UTIL_MAP_H