#ifndef __INIT_H__
#define __INIT_H__

#include "list.h"

struct command
{
    struct listnode clist;

    int (*func)(int nargs, char **args);
    int nargs;
    char *args[1];
};

struct action {
        /* node in list of all actions */
    struct listnode alist;
        /* node in the queue of pending actions */
    struct listnode qlist;
        /* node in list of actions for a trigger */
    struct listnode tlist;

    unsigned hash;
    const char *name;
    
    struct listnode commands;
    struct command *current;
};

struct service {
    struct listnode slist;

    const char *name;
    const char *classname;

    pid_t pid;
    uid_t uid;
    gid_t gid;

    int nargs;
    char *args[1];
};

#endif