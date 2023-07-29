#ifndef token_h
#define token_h

#include "../str/str.h"

enum token_type {
    INTEGER,
    ADD,
    SUBTRACT,
    PRINT,
};

struct token {
    enum token_type type;
    struct str value;
};

struct token token_new(enum token_type type, struct str value);

#endif
