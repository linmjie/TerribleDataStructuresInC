#pragma once

#define MAKE_SIMPLE_MAP_DEF(K, V, HASH)\
V empty_##V##_t = {0};\
\
typedef struct {\
    V *buckets;\
    size_t bucketSize;\
} SimpleMap_##K##_##V;\
\
V *SimpleMap_##K##_##V##_Get(SimpleMap_##K##_##V *map, const K *key) {\
    size_t bucketIdx = HASH(key) % map->bucketSize;\
    V *item = &map->buckets[bucketIdx];\
    int isEmpty = memcmp(&empty_##V##_t, item, sizeof(V));\
    return isEmpty ? item : NULL;\
}\
\
void SimpleMap_##K##_##V##_Set(SimpleMap_##K##_##V *map, const K *key, V val) {\
    size_t bucketIdx = hash(key) % map->bucketSize;\
    map->buckets[bucketIdx] = val;\
}\
\
void initSimpleMap_##K##_##V(SimpleMap_##K##_##V *map, size_t size) {\
    map->buckets = calloc(size, sizeof(V));\
    if (map->buckets == NULL) {\
        printf("No memory left :(\n");\
        exit(1);\
    }\
    map->bucketSize = size;\
}\
\
void deleteSimpleMap_##K##_##V(SimpleMap_##K##_##V *map) { free(map->buckets); }
