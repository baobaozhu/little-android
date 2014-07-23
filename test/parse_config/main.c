
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "parse.h"
#include "init_parse.h"

int main(int argc, char** argv) {
    struct parse_state state;
    int token;
    char *data = read_file("./data/init.rc", NULL);
    char *args[INIT_PARSER_MAXARGS];
    int nargs = 0;
    int i=0;

    if (NULL==data) {
        return 0;
    }

    state.data       = data;
    state.line_num   = 0;
    state.next_token = 0;
    state.text       = NULL;

    for (;;) {
        switch (next_token(&state)) {
        case TOKEN_ID_EOF:
            goto parse_done;
        case TOKEN_ID_NEWLINE:
            state.line_num++;
            for (i=0; i<nargs; i++) {
                printf("%s ", args[i]);
            }
            nargs = 0;
            printf("\n");
            break;
        case TOKEN_ID_TEXT:
            args[nargs++] = state.text;
            break;
        }
    }

parse_done:
    free(data);

    return 0;
}