
#ifndef __LIST_H__
#define __LIST_H__
///////////////////////////////////////////////////////////
struct listnode
{
    struct listnode *next;
    struct listnode *prev;
};

#define list_declare(name) \
    struct listnode name = { \
        .next = &name, \
        .prev = &name, \
    }

void list_init(struct listnode *list);
void list_add_tail(struct listnode *list, struct listnode *item);


///////////////////////////////////////////////////////////
#endif