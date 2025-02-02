#include "./linked_list.h"

linked_list_item *linked_list_item_alloc(const char *key, void *data) {
    linked_list_item *item;

    item = (linked_list_item *)MALLOC(sizeof(linked_list_item));
    ASSERT_MSG(item != NULL, "Linked List Item allocation failed");

    item->key = MALLOC(strlen(key) + 1);
    ASSERT_MSG(item->key != NULL, "Linked List Item key allocation failed");

    strcpy(item->key, key);
    item->data = data;
    item->next = NULL;

    return (item);
}

void linked_list_item_free(linked_list_item *item) {
    FREE(item->key);
    FREE(item);
}

linked_list *linked_list_alloc() {
    linked_list *m;

    m = (linked_list *) MALLOC(sizeof(linked_list));
    ASSERT_MSG(m != NULL, "Linked List allocation failed");

    m->head = NULL;
    m->size = 0;

    return (m);
};

void linked_list_insert(linked_list *linked_list, const char *key, void *data) {
    linked_list_item *current, *new_item;

    current = linked_list->head;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->data = data;
            return;
        }
        current = current->next;
    }
    new_item = linked_list_item_alloc(key, data);
    new_item->next = linked_list->head;
    linked_list->head = new_item;
    linked_list->size++;
}

void *linked_list_find(linked_list *linked_list, const char *key) {
    linked_list_item *current;

    current = linked_list->head;
    while (current) {
        if (strcmp(current->key, key) == 0)
            return (current->data);
        current = current->next;
    }

    return (NULL);
}

void linked_list_erase(linked_list *linked_list, const char *key) {
    linked_list_item *current, *prev;

    current = linked_list->head;
    prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev)
                prev->next = current->next;
            else
                linked_list->head = current->next;
            linked_list_item_free(current);
            linked_list->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void linked_list_apply(linked_list *linked_list, void (*fn)(linked_list_item *item)) {
    linked_list_item *current;

    current = linked_list->head;
    while (current) {
        fn(current);
        current = current->next;
    }
}

void linked_list_clear(linked_list *linked_list) {
    linked_list_item *current;

    current = linked_list->head;
    while (current) {
        linked_list_item *next = current->next;
        linked_list_item_free(current);
        current = next;
    }
    linked_list->head = NULL;
    linked_list->size = 0;
}

void linked_list_free(linked_list *linked_list) {
    ASSERT_MSG(linked_list != NULL, "linked_list is NULL but tried to freed");
    linked_list_clear(linked_list);
    FREE(linked_list);
}
