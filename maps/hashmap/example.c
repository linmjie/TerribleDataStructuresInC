#include "../../lists/array/array.h"
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOAD_FACTOR 0.75
#define MAP_RESIZE_MUTLIPLIER 2

typedef struct {
    const char *key;
    const int *value;
} Pair;

MAKE_REF_LIST_DEF(Pair);

typedef struct {
    List_Pair *buckets;
    size_t loaded; // how many buckets loaded; not amount of kv pairs
    size_t capacity; // capacity of buckets; not capacity of kv pairs
} Map;

void Map_Set(Map *map, const char *key, const int *value) {
    if ((double)map->loaded / map->capacity > LOAD_FACTOR) {
        size_t newCapacity = map->capacity * MAP_RESIZE_MUTLIPLIER * sizeof(List_Pair);
        map->buckets = realloc(map->buckets, newCapacity);
        if (map->buckets == NULL) {
            printf("No memory left :(\n");
            exit(1);
        }
        for (size_t i = map->capacity; i < newCapacity; i++) {
            initList_Pair_WithCapacity(&map->buckets[i], 4);
        }
        return;
    }
}

void initMap(Map *map, size_t capacity) {
    map->buckets = malloc(capacity * sizeof(List_Pair));
    for (size_t i = 0; i < capacity; i++) {
        initList_Pair_WithCapacity(&map->buckets[i], 4);
    }
    map->loaded = 0;
    map->capacity = capacity;
}

void deleteMap(Map *map) {
    for (size_t i = 0; i < map->capacity; i++) {
        deleteList_Pair(&map->buckets[i]);
    }
}
