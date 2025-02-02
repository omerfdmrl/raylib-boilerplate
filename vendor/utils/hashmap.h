#ifndef UTIL_HASHMAP_H

#define UTIL_HASHMAP_H

#include "../common.h"

struct s_hash_node {
    char* key;
    void* value;
    struct s_hash_node *next;
};
 
struct s_hash_map {
    int16 size;
    int16 capacity;
    struct s_hash_node **data;
};

typedef struct s_hash_node hash_node;
typedef struct s_hash_map hash_map;
 
hash_map *hashmap_alloc(int16 capacity);
int hashmap_function(hash_map* mp, char* key);
void hashmap_insert(hash_map* mp, char* key, void* value);
void hashmap_delete(hash_map* mp, char* key);
void *hashmap_search(hash_map* mp, char* key);
void hashmap_apply(hash_map *mp, void (*fn)(hash_node* item));
void hashmap_free(hash_map *mp);

#endif // !UTIL_HASHMAP_H
