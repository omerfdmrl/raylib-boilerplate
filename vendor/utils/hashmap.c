#include "hashmap.h"

hash_map *hashmap_alloc(int16 capacity) {
    hash_map* mp;

    mp = (hash_map *) MALLOC(sizeof(hash_map));
    ASSERT_MSG(mp != NULL, "Map allocation failed");

    mp->capacity = capacity;
    mp->size = 0;

    mp->data = (hash_node**)MALLOC(sizeof(hash_node*) * mp->capacity);
    ASSERT_MSG(mp->data != NULL, "Map array allocation failed");

    for (int i = 0; i < mp->capacity; i++)
        mp->data[i] = NULL;

    return (mp);
}
 
int hashmap_function(hash_map* mp, char* key) {
    int bucketIndex, sum, factor;

    sum = 0;
    factor = 31;

    for (size_t i = 0; i < strlen(key); i++) {
        sum = (sum * factor + (int)key[i]) % mp->capacity;
        factor = (factor * 31) % __INT16_MAX__;
    }
 
    bucketIndex = sum;

    return (bucketIndex);
}
 
void hashmap_insert(hash_map* mp, char* key, void* value) {
    int bucketIndex;
    hash_node* newNode;

    bucketIndex = hashmap_function(mp, key);
    ASSERT_MSG(bucketIndex >= 0 && bucketIndex < mp->capacity, "Invalid bucket index");

    newNode = (hash_node*) MALLOC(sizeof(hash_node));
    ASSERT_MSG(newNode != NULL, "Node allocation failed");
    newNode->key = MALLOC(strlen(key) + 1);
    ASSERT_MSG(newNode->key != NULL, "Key allocation failed");
    strcpy(newNode->key, key);

    newNode->value = value;
    newNode->next = NULL;

    if (mp->data[bucketIndex] == NULL)
        mp->data[bucketIndex] = newNode;
    else {
        newNode->next = mp->data[bucketIndex];
        mp->data[bucketIndex] = newNode;
    }
    mp->size++;
}
 
void hashmap_delete(hash_map* mp, char* key) {
    int bucketIndex;
    hash_node *prevNode, *currNode;

    bucketIndex = hashmap_function(mp, key);
    prevNode = NULL;
    currNode = mp->data[bucketIndex];
 
    while (currNode != NULL) {
        if (strcmp(key, currNode->key) == 0) {
            if (currNode == mp->data[bucketIndex])
                mp->data[bucketIndex] = currNode->next;
            else
                prevNode->next = currNode->next;
            FREE(currNode);
            mp->size--;
            break;
        }
    }
}
 
void *hashmap_search(hash_map* mp, char* key) {
    int bucketIndex;
    hash_node* bucketHead;

    bucketIndex = hashmap_function(mp, key);
    bucketHead = mp->data[bucketIndex];

    while (bucketHead != NULL) {
        if (strcmp(bucketHead->key, key) == 0)
            return (bucketHead->value);
        bucketHead = bucketHead->next;
    }

    return (NULL);
}

void hashmap_apply(hash_map *mp, void (*fn)(hash_node* item)) {
    for (size_t i = 0; i < mp->capacity; i++) {
        hash_node *node = mp->data[i];
        while (node != NULL) {
            fn(node);
            node = node->next;
        }
    }
}

void hashmap_free(hash_map *mp) {
    ASSERT_MSG(mp != NULL, "mp is NULL but tried to freed");
    for (size_t i = 0; i < mp->capacity; i++) {
        hash_node *node = mp->data[i];
        while (node != NULL) {
            hash_node *temp = node;
            node = node->next;
            FREE(temp->key);
            FREE(temp);
        }
    }
    FREE(mp->data);
    FREE(mp);
}
