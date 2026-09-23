#define LIST_BASE_SIZE 256
#define LIST_RESIZE_MULTIPLIER 2

#define MAKE_LIST_DEF(T) \
typedef struct {\
    T *items;\
    size_t size;\
    size_t capacity;\
} List_##T;\
\
void List_##T##_Append(List_##T *list, T item) {\
    assert(list->capacity > 0 && "Shouldn't try appending to uninitialized list");\
    if (list->size < list->capacity) {\
        list->items[list->size] = item;\
    } else {\
        size_t newCapacity = list->capacity * LIST_RESIZE_MULTIPLIER;\
        T *newItems = realloc(list->items, newCapacity * sizeof(T));\
        if (newItems == NULL) {\
            printf("No memory left :(\n");\
            exit(1);\
        }\
        list->items = newItems;\
        list->capacity = newCapacity;\
        list->items[list->size] = item;\
    }\
    list->size++;\
}\
\
void initList_##T##_WithCapacity(List_##T *list, size_t capacity) {\
    list->items = malloc(capacity * sizeof(T));\
    list->size = 0;\
    list->capacity = capacity;\
}\
\
void initList_##T(List_##T *list) { initList_##T##_WithCapacity(list, LIST_BASE_SIZE); }



#define MAKE_REF_LIST_DEF(T) \
typedef struct {\
    T *items;\
    size_t size;\
    size_t capacity;\
} List_##T;\
\
void List_##T##_Append(List_##T *list, const T *item) {\
    assert(list->capacity > 0 && "Shouldn't try appending to uninitialized list");\
    if (list->size < list->capacity) {\
        list->items[list->size] = *item;\
    } else {\
        size_t newCapacity = list->capacity * LIST_RESIZE_MULTIPLIER;\
        T *newItems = realloc(list->items, newCapacity * sizeof(T));\
        if (newItems == NULL) {\
            printf("No memory left :(\n");\
            exit(1);\
        }\
        list->items = newItems;\
        list->capacity = newCapacity;\
        list->items[list->size] = *item;\
    }\
    list->size++;\
}\
\
void initList_##T##_WithCapacity(List_##T *list, size_t capacity) {\
    list->items = malloc(capacity * sizeof(T));\
    list->size = 0;\
    list->capacity = capacity;\
}\
\
void initList_##T(List_##T *list) { initList_##T##_WithCapacity(list, LIST_BASE_SIZE); }



#define MAKE_MUT_REF_LIST_DEF(T) \
typedef struct {\
    T **items;\
    size_t size;\
    size_t capacity;\
} List_p##T;\
\
void List_p##T##_Append(List_p##T *list, T *item) {\
    assert(list->capacity > 0 && "Shouldn't try appending to uninitialized list");\
    if (list->size < list->capacity) {\
        list->items[list->size] = item;\
    } else {\
        size_t newCapacity = list->capacity * LIST_RESIZE_MULTIPLIER;\
        T **newItems = realloc(list->items, newCapacity * sizeof(T));\
        if (newItems == NULL) {\
            printf("No memory left :(\n");\
            exit(1);\
        }\
        list->items = newItems;\
        list->capacity = newCapacity;\
        list->items[list->size] = item;\
    }\
    list->size++;\
}\
\
void initList_p##T##_WithCapacity(List_p##T *list, size_t capacity) {\
    list->items = malloc(capacity * sizeof(T*));\
    list->size = 0;\
    list->capacity = capacity;\
}\
\
void initList_p##T(List_p##T *list) { initList_p##T##_WithCapacity(list, LIST_BASE_SIZE); }
