
#ifndef __PARSE_H__
#define __PARSE_H__

#define TOKEN_ID_EOF     1
#define TOKEN_ID_NEWLINE 2
#define TOKEN_ID_TEXT    3

struct parse_state {
    unsigned char *data;
    unsigned int line_num;
    int next_token;
    char *text;
};

int next_token(struct parse_state *p_state);

#endif