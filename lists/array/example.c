#include "array.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
    double z;
} Point;

typedef struct {
    Point *items;
    size_t size;
    size_t capacity;
} List;

void List_Append(List *list, const Point *item) {
    assert(list->capacity > 0 &&
           "Shouldn't try appending to uninitialized list");
    if (list->size < list->capacity) {
        list->items[list->size] = *item;
    } else {
        size_t newCapacity = list->capacity * 2;
        Point *newItems = realloc(list->items, newCapacity * sizeof(Point));
        if (newItems == ((void *)0)) {
            printf("No memory left :(\n");
            exit(1);
        }
        list->items = newItems;
        list->capacity = newCapacity;
        list->items[list->size] = *item;
    }
    list->size++;
}

void initList_WithCapacity(List *list, size_t capacity) {
    list->items = malloc(capacity * sizeof(Point));
    list->size = 0;
    list->capacity = capacity;
}

void initList(List *list) {
    initList_WithCapacity(list, 256);
}
void deleteList(List *list) { free(list->items); }

int main() {
    List list;
    initList_WithCapacity(&list, 2);
    for (int i = 0; i < 10; i++) {
        Point point = {.x = i * M_PI, .y = i * M_PI_2, .z = i * M_PI_4};
        List_Append(&list, &point);
    }

    for (size_t i = 0; i < list.size; i++) {
        Point item = list.items[i];
        printf("x=%f, y=%f, z=%f\n", item.x, item.y, item.z);
    }

    printf("\nNow transforming everything by sin(x)\n");

    for (size_t i = 0; i < list.size; i++) {
        Point *item = &list.items[i];
        item->x = sin(item->x);
        item->y = sin(item->y);
        item->z = sin(item->z);
    }

    for (size_t i = 0; i < list.size; i++) {
        Point item = list.items[i];
        printf("x=%f, y=%f, z=%f\n", item.x, item.y, item.z);
    }

    deleteList(&list);
}
