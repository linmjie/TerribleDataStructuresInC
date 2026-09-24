#define MAKE_SIMPLE_MAP(K, V, HASH)\
typedef struct {\
    V *buckets;\
    size_t bucketSize;\
} SimpleMap_##K##_##V;\
\
V SimpleMap_##K##_##V##_Get(SimpleMap_##K##_##V *map, const K *key) {\
    size_t bucketIdx = HASH(key) % map->bucketSize;\
    return map->buckets[bucketIdx];\
}\
\
void SimpleMap_##K##_##V##_Set(SimpleMap_##K##_##V *map, const K *key, V val) {\
    size_t bucketIdx = hash(key) % map->bucketSize;\
    map->buckets[bucketIdx] = val;\
}\
\
void initSimpleMap_##K##_##V(SimpleMap_##K##_##V *map, size_t size) {\
    map->buckets = malloc(size * sizeof(V));\
    if (map->buckets == NULL) {\
        printf("No memory left :(\n");\
        exit(1);\
    }\
    map->bucketSize = size;\
}\
\
void deleteSimpleMap_##K##_##V(SimpleMap_##K##_##V *map) { free(map->buckets); }
