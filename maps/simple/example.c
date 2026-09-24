#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t hash(const char *str) {
    return strlen(str) - 1;
}

typedef struct {
    int *buckets;
    size_t bucketSize;
} SimpleMap;

int SimpleMap_Get(SimpleMap *map, const char *key) {
    size_t bucketIdx = hash(key) % map->bucketSize;
    return map->buckets[bucketIdx];
}

void SimpleMap_Set(SimpleMap *map, const char *key, int val) {
    size_t bucketIdx = hash(key) % map->bucketSize;
    map->buckets[bucketIdx] = val;
}

void initSimpleMap(SimpleMap *map, size_t size) {
    map->buckets = malloc(size * sizeof(int));
    if (map->buckets == NULL) {
        printf("No memory left :(\n");
        exit(1);
    }
    map->bucketSize = size;
}

void deleteSimpleMap(SimpleMap *map) {
    free(map->buckets);
};

int main(int argc, char *argv[]) {
    SimpleMap map;
    initSimpleMap(&map, 10);

    SimpleMap_Set(&map, "a", 20);
    SimpleMap_Set(&map, "ab", 31);
    SimpleMap_Set(&map, "abc", 25);
    SimpleMap_Set(&map, "abcd", 22);
    SimpleMap_Set(&map, "abcde", 43);
    SimpleMap_Set(&map, "abcdef", 21);
    SimpleMap_Set(&map, "abcdefg", 9);
    SimpleMap_Set(&map, "abcdefgh", 39);
    SimpleMap_Set(&map, "abcdefghi", 24);
    SimpleMap_Set(&map, "abcdefghij", 6);

    printf("val: %d\n", SimpleMap_Get(&map, "abcdefg"));
    printf("val: %d\n", SimpleMap_Get(&map, "abcd"));
    printf("val: %d\n", SimpleMap_Get(&map, "abcde"));
    printf("val: %d\n", SimpleMap_Get(&map, "abcdefghi"));
    printf("val: %d\n", SimpleMap_Get(&map, "a"));
    printf("val: %d\n", SimpleMap_Get(&map, "abcdefgh"));
    printf("val: %d\n", SimpleMap_Get(&map, "abcdefghij"));
    printf("val: %d\n", SimpleMap_Get(&map, "abc"));
    printf("val: %d\n", SimpleMap_Get(&map, "ab"));
    printf("val: %d\n", SimpleMap_Get(&map, "abcdef"));

    deleteSimpleMap(&map);
}
