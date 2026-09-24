#include "../../lists/array/array.h"
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MAKE_REF_LIST_DEF(int);

typedef struct {
    const char *key;
    const int *value;
} Pair;

typedef struct {
    List_int *buckets;
    size_t loaded; // how many buckets loaded; not amount of kv pairs
    size_t capacity; // capacity of buckets; not capacity of kv pairs
} Map;

void initMap(Map *map, size_t capacity) {
    map->buckets = malloc(capacity * sizeof(List_int));
    for (size_t i = 0; i < capacity; i++) {
        initList_int_WithCapacity(&map->buckets[i], 4);
    }
    map->loaded = 0;
    map->capacity = capacity;
}

void deleteMap(Map *map) {
}
