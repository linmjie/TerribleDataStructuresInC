#include "../../lists/array/array.h"
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOAD_FACTOR 0.75
#define MAP_BASE_SIZE 256
#define MAP_RESIZE_MUTLIPLIER 2

typedef struct {
    const char *key;
    int value;
} Pair;

MAKE_LIST_DEF(Pair);

typedef struct {
    List_Pair *buckets;
    size_t loaded; // how many buckets loaded; not amount of kv pairs
    size_t capacity; // capacity of buckets; not capacity of kv pairs
} Map;

size_t hash(const char *str) {
    return strlen(str) - 1;
}

int *Map_Get(const Map *map, const char *key) {
    size_t bucketIdx = hash(key) % map->capacity;
    const List_Pair *pairs = &map->buckets[bucketIdx];
    if (pairs->size == 0) {
        return NULL;
    }
    for (size_t i = 0; i < pairs->size; i++) {
        if (strcmp(key, pairs->items[i].key) == 0) {
            return &pairs->items[i].value;
        }
    }
    return NULL;
}

void Map_Expand(Map *map) {
    size_t newCapacity = map->capacity * MAP_RESIZE_MUTLIPLIER * sizeof(List_Pair);
    map->buckets = realloc(map->buckets, newCapacity);
    if (map->buckets == NULL) {
        printf("No memory left :(\n");
        exit(1);
    }
    for (size_t i = map->capacity; i < newCapacity; i++) {
        initList_Pair_WithCapacity(&map->buckets[i], 4);
    }
}

void Map_Set(Map *map, const char *key, const int *value) {
    if ((double)map->loaded / map->capacity > LOAD_FACTOR) {
        Map_Expand(map);
        return;
    }
    size_t bucketIdx = hash(key);
    List_Pair *pairs = &map->buckets[bucketIdx];
    if (pairs->size == 0) {
        List_Pair_Append(pairs, (Pair){key, *value});
        return;
    }
    for (size_t i = 0; i < pairs->size; i++) {
        if (strcmp(pairs->items[i].key, key) == 0) {
            pairs->items[i].value = *value;
            return;
        }
    }
    List_Pair_Append(pairs, (Pair){key, *value});
}

void initMapWithCapacity(Map *map, size_t capacity) {
    map->buckets = malloc(capacity * sizeof(List_Pair));
    for (size_t i = 0; i < capacity; i++) {
        initList_Pair_WithCapacity(&map->buckets[i], 4);
    }
    map->loaded = 0;
    map->capacity = capacity;
}

void initMap(Map *map) { initMapWithCapacity(map, MAP_BASE_SIZE); }

void deleteMap(Map *map) {
    for (size_t i = 0; i < map->capacity; i++) {
        deleteList_Pair(&map->buckets[i]);
    }
}

int main() {
    Map map;
    initMap(&map);
}
