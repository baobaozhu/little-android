
#include "list.h"

void list_init(struct listnode *list) {
    list->next = list;
    list->prev = list;
}

void list_add_tail(struct listnode *list, struct listnode *item) {
    item->prev       = list->prev;
    list->prev->next = item;
    list->prev       = item;
    item->next       = list;
}