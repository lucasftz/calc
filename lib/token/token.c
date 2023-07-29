#include "token.h"

struct token token_new(enum token_type type, struct str value) {
    return (struct token) {
        .type = type,
        .value = value,
    };
}

