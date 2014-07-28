
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "init.h"
#include "init_parse.h"
#include "parse.h"

static list_declare(service_list);
static list_declare(action_list);
static list_declare(action_queue);

static void *parse_service(struct parse_state *state, int nargs, char **args);
static void parse_line_service(struct parse_state *state, int nargs, char **args);

static void *parse_action(struct parse_state *state, int nargs, char **args);
static void parse_line_action(struct parse_state *state, int nargs, char **args);

static void dump();

#define SECTION 0x01
#define COMMAND 0x02
#define OPTION  0x04

#include "keywords.h"

#define KEYWORD(symbol, flags, nargs, func) \
    [ K_##symbol ] = { #symbol, func, nargs + 1, flags, },

struct {
    const char *name;
    int (*func)(int nargs, char **args);
    unsigned char nargs;
    unsigned char flags;
} keyword_info[KEYWORD_COUNT] = {
    [ K_UNKNOWN ] = { "unknown", 0, 0, 0 },
#include "keywords.h"
};
#undef KEYWORD

#define kw_is(kw, type) (keyword_info[kw].flags & (type))
#define kw_name(kw) (keyword_info[kw].name)
#define kw_func(kw) (keyword_info[kw].func)
#define kw_nargs(kw) (keyword_info[kw].nargs)

int lookup_keyword(const char *s) {
    int i = 0;
    for (i=0; i<KEYWORD_COUNT; i++) {
        if ( !strcmp(s, keyword_info[i].name) ) {
            return i;
        }
    }
    return K_UNKNOWN;
}

void parse_new_section(struct parse_state *state, int kw, int nargs, char **args) {
    switch ( kw ) {
    case K_service:
        state->p_context  = parse_service(state, nargs, args);
        state->parse_line = parse_line_service;
        break;
    case K_on:
        state->p_context  = parse_action(state, nargs, args);
        state->parse_line = parse_line_action;
        break;
    default:
        state->parse_line = parse_line_no_op;
        break;
    }
}

void *parse_service(struct parse_state *state, int nargs, char **args) {
    if ( 3>nargs ) {
        printf("parse_service failed, 3>nargs\n");
        return NULL;
    }

    struct service *p_service = calloc(1, sizeof(struct service)+sizeof(char*)*(nargs-2));
    p_service->name      = args[1];
    p_service->classname = "default";
    p_service->nargs     = nargs-2;
    memcpy(p_service->args, args+2, sizeof(char*)*(nargs-2));
    p_service->args[nargs-2] = 0;
    list_add_tail(&service_list, &(p_service->slist));
}

void parse_line_service(struct parse_state *state, int nargs, char **args) {
    struct service *p_service = (struct service *)state->p_context;
    if ( !p_service ) {
        return;
    }

    if ( 1>nargs ) {
        return;
    }

    int kw = lookup_keyword(args[0]);
    if ( !kw_is(kw, OPTION) ) {
        return;
    }

    switch (kw) {
    case K_class:
        p_service->classname = args[1];
        break;
    default:
        break;
    }
}

void *parse_action(struct parse_state *state, int nargs, char **args) {
    struct action *p_action = calloc(1, sizeof(struct action));
    list_init(&(p_action->qlist));
    list_init(&(p_action->commands));

    p_action->name = args[1];

    list_add_tail(&action_list, &(p_action->alist));

    return p_action;
}

void parse_line_action(struct parse_state *state, int nargs, char **args) {
    struct action *p_action = (struct action *)state->p_context;
    struct command *p_command = calloc(1, sizeof(struct command)+sizeof(char*)*nargs);

    int kw = lookup_keyword(args[0]);

    p_command->func = keyword_info[kw].func;
    p_command->nargs = nargs;
    memcpy(p_command->args, args, sizeof(char*)*nargs);
    p_command->args[nargs] = 0;
    list_add_tail(&(p_action->commands), &(p_command->clist));
}

static void parse_config(const char *fn, char *s) {
    struct parse_state state;
    int token;
    char *args[INIT_PARSER_MAXARGS];
    int nargs = 0;
    int i=0;

    state.data       = s;
    state.line_num   = 0;
    state.next_token = 0;
    state.text       = NULL;
    state.parse_line = parse_line_no_op;

    for (;;) {
        switch (next_token(&state)) {
        case TOKEN_ID_EOF:
            goto parse_done;
        case TOKEN_ID_NEWLINE:
            state.line_num++;
            if ( 0>=nargs ) {
                break;
            }
            int kw = lookup_keyword( args[0] );
            if ( kw_is(kw, SECTION) ) {
                parse_new_section(&state, kw, nargs, args);
            } else {
                state.parse_line(&state, nargs, args);
            }
            nargs = 0;
            break;
        case TOKEN_ID_TEXT:
            args[nargs++] = state.text;
            break;
        }
    }

parse_done:
    return;
}

int init_parse_config_file(const char *fn) {
    char *data = read_file(fn, NULL);
    if (!data) {
        return -1;
    }

    parse_config(fn, data);
    // dump();
    return 0;
}

void dump() {
    struct listnode* p_node = NULL;
    struct listnode* p_node2 = NULL;
    int i=0;

    for (p_node=action_list.next; p_node!=&action_list; p_node=p_node->next) {
        struct action *p_action = (struct action *)p_node;
        printf("on %s\n", p_action->name);

        for (p_node2=p_action->commands.next; p_node2!=&(p_action->commands); p_node2=p_node2->next) {
            struct command *p_command = (struct command *)p_node2;
            for (i=0; i<p_command->nargs; i++) {
                printf("%s ", p_command->args[i]);
            }
            printf("\n");
        }
        printf("\n");
    }

    for (p_node=service_list.next; p_node!=&service_list; p_node=p_node->next) {
        struct service *p_service = (struct service *)p_node;
        printf("service %s\n", p_service->name);
        printf("class %s\n", p_service->classname);
        for (i=0; i<p_service->nargs; i++) {
            printf("%s ", p_service->args[i]);
        }
        printf("\n\n");
    }
}