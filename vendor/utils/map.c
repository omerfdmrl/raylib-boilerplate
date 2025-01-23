#include "./map.h"

map_item *map_item_alloc(const char *key, void *data) {
    map_item *item;

    item = (map_item *)MALLOC(sizeof(map_item));
    ASSERT_MSG(item != NULL, "Map Item allocation failed");

    item->key = MALLOC(sizeof(strlen(key) + 1));
    ASSERT_MSG(item->key != NULL, "Map Item key allocation failed");

    strcpy(item->key, key);
    item->data = data;
    item->next = NULL;

    return (item);
}

void map_item_free(map_item *item) {
    FREE(item->key);
    FREE(item);
}

map *map_alloc() {
    map *m;

    m = (map *) MALLOC(sizeof(map));
    ASSERT_MSG(m != NULL, "Map allocation failed");

    m->head = NULL;
    m->size = 0;
    m->insert = map_insert;
    m->find = map_find;
    m->erase = map_erase;
    m->clear = map_clear;

    return (m);
};

void map_insert(map *map, const char *key, void *data) {
    map_item *current, *new_item;

    current = map->head;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->data = data;
            return;
        }
        current = current->next;
    }
    new_item = map_item_alloc(key, data);
    new_item->next = map->head;
    map->head = new_item;
    map->size++;
}

void *map_find(map *map, const char *key) {
    map_item *current;

    current = map->head;
    while (current) {
        if (strcmp(current->key, key) == 0)
            return (current->data);
        current = current->next;
    }

    return (NULL);
}

void map_erase(map *map, const char *key) {
    map_item *current, *prev;

    current = map->head;
    prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev)
                prev->next = current->next;
            else
                map->head = current->next;
            map_item_free(current);
            map->size--;
            return;
        }
        prev = current;
        current = current->next;
    }

}

void map_clear(map *map) {
    map_item *current;

    current = map->head;
    while (current) {
        map_item *next = current->next;
        map_item_free(current);
        current = next;
    }
    map->head = NULL;
    map->size = 0;
}

void map_free(map *map) {
    map_clear(map);
    FREE(map);
}
