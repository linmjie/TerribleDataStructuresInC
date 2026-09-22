#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_BASE_SIZE 32
#define LIST_RESIZE_MULTIPLIER 2

typedef struct {
    int *items;
    size_t size;
    size_t capacity;
} List;

void List_append(List *list, int item) {
    assert(list->capacity > 0 && "Shouldn't try appending to empty list");
    if (list->size + 1 < list->capacity) {
        list->items[list->size] = item;
    } else {
        int newCapacity = list->capacity * LIST_RESIZE_MULTIPLIER;
        int *newItems = malloc(newCapacity * sizeof(int));
        memcpy(newItems, list->items, list->capacity * sizeof(int));
        free(list->items);
        list->items = newItems;
        list->capacity = newCapacity;
        list->items[list->size] = item;
    }
    list->size++;
}


void initListWithCapacity(List *list, size_t capacity) {
    list->items = malloc(capacity * sizeof(int));
    list->size = 0;
    list->capacity = capacity;
}

void initList(List *list) {
    initListWithCapacity(list, LIST_BASE_SIZE); 
}

int main(int argc, char *argv[]) {
    List list;
    initList(&list);

    for (int i = 0; i < 100; ++i) {
        List_append(&list, i * 5);
    }

    for (int i = 0; i < 100; ++i) {
        printf("Item at %d: %d\n", i, list.items[i]);
    }

    free(list.items);
}
