#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../list/array/array.h"

MAKE_LIST_DEF(int)
MAKE_LIST_DEF(double);

int main(int argc, char *argv[]) {
    List_int list;
    initList_int_WithCapacity(&list, 2);

    for (int i = 0; i < 10; i++) {
        List_int_Append(&list, i * 5);
    }

    for (int i = 0; i < 10; i++) {
        printf("%d * 5: %d\n", i, list.items[i]);
    }

    free(list.items);


    printf("\n\n\n");


    List_double lst;
    initList_double_WithCapacity(&lst, 2);

    for (int i = 0; i < 10; i++) {
        List_double_Append(&lst, i * M_PI);
    }

    for (int i = 0; i < 10; i++) {
        printf("%d * pi: %f\n", i, lst.items[i]);
    }

    free(lst.items);
}
