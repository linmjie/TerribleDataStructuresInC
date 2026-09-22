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
    assert(list->capacity > 0 && "Shouldn't try appending to unitialized list");\
    if (list->size + 1 < list->capacity) {\
        list->items[list->size] = item;\
    } else {\
        T newCapacity = list->capacity * LIST_RESIZE_MULTIPLIER;\
        T *newItems = malloc(newCapacity * sizeof(T));\
        memcpy(newItems, list->items, list->capacity * sizeof(T));\
        free(list->items);\
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
