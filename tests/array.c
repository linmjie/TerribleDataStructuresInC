#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lists/array/array.h"

typedef struct {
    double x;
    double y;
    double z;
} Point;

MAKE_LIST_DEF(double);
MAKE_MUT_REF_LIST_DEF(Point);
MAKE_REF_LIST_DEF(Point);

void testDoubleList() {
    List_double list;
    initList_double_WithCapacity(&list, 2);

    for (int i = 0; i < 10; i++) {
        List_double_Append(&list, i * M_PI);
    }

    for (int i = 0; i < 10; i++) {
        printf("%d * pi: %f\n", i, list.items[i]);
    }

    free(list.items);
}

void test_pPointList() {
    List_pPoint list;
    initList_pPoint_WithCapacity(&list, 2);
    for (int i = 0; i < 10; i++) {
        Point *point = malloc(sizeof(Point));
        *point = (Point){ 
            .x = i * M_PI,
            .y = i * M_PI_2,
            .z = i * M_PI_4
        };
        List_pPoint_Append(&list, point);
    }

    for (size_t i = 0; i < list.size; i++) {
        Point *item = list.items[i];
        printf("x=%f, y=%f, z=%f\n", item->x, item->y, item->z);
    }

    for (size_t i = 0; i < list.size; i++) {
        free(list.items[i]);
        list.items[i] = NULL;
    }

    free(list.items);
}

void testPointList() {
    List_Point list;
    initList_Point_WithCapacity(&list, 2);
    for (int i = 0; i < 10; i++) {
        Point point = { 
            .x = i * M_PI,
            .y = i * M_PI_2,
            .z = i * M_PI_4
        };
        List_Point_Append(&list, &point);
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

    free(list.items);
}

int main(int argc, char *argv[]) {
    testDoubleList();
    printf("\n\n\n");
    test_pPointList();
    printf("\n\n\n");
    testPointList();
}
