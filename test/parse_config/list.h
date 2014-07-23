
#ifndef __LIST_H__
#define __LIST_H__
///////////////////////////////////////////////////////////
struct list_node {
    struct list_node *next;
    struct list_node *prev;
};

#define declare_list(name) \
    struct list_node name; \
    name.next = &name; \
    name.prev = &name;


///////////////////////////////////////////////////////////
#endif