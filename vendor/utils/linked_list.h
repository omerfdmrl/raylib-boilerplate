#ifndef UTIL_MAP_H

#define UTIL_MAP_H

#include "../common.h"

struct s_linked_list_item {
    char *key;
    void *data;
    struct s_linked_list_item *next;
};

struct s_linked_list {
    struct s_linked_list_item *head;
    uint64 size;
};

typedef struct s_linked_list_item linked_list_item;
typedef struct s_linked_list linked_list;

linked_list_item *linked_list_item_alloc(const char *key, void *data);
void linked_list_item_free(linked_list_item *item);

linked_list *linked_list_alloc();
void linked_list_insert(linked_list *linked_list, const char *key, void *data);
void *linked_list_find(linked_list *linked_list, const char *key);
void linked_list_erase(linked_list *linked_list, const char *key);
void linked_list_apply(linked_list *linked_list, void (*fn)(linked_list_item *item));
void linked_list_clear(linked_list *linked_list);
void linked_list_free(linked_list *linked_list);

#endif // !UTIL_MAP_H