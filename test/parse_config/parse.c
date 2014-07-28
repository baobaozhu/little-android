
#include <stddef.h>
#include "parse.h"

int next_token(struct parse_state *p_state) {
    char *s = p_state->data;

    if ( p_state->next_token ) {
        int t = p_state->next_token;
        p_state->next_token = 0;
        return t;
    }

    for (;;) {
        switch ( *s ) {
        case 0:
            p_state->data = s;
            return TOKEN_ID_EOF;
        case ' ':
        case '\t':
        case '\r':
            s++;
            continue;
        case '\n':
            s++;
            p_state->data = s;
            return TOKEN_ID_NEWLINE;
        case '#':
            s++;
            while ('\n'!=*s++);
            p_state->data = s;
            return TOKEN_ID_NEWLINE;
        default:
            goto text;
        }
    }

text:
    p_state->text = s;
    for (;;) {
        switch ( *s ) {
        case ' ':
        case '\t':
        case '\r':
            *s = 0;
            s++;
            p_state->data = s;
            return TOKEN_ID_TEXT;
        case '\n':
            *s = 0;
            s++;
            p_state->data = s;
            p_state->next_token = TOKEN_ID_NEWLINE;
            return TOKEN_ID_TEXT;
        default:
            s++;
            break;
        }
    }

    return TOKEN_ID_EOF;
}

void parse_line_no_op(struct parse_state *state, int nargs, char **args) {
}