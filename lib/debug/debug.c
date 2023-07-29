#include "debug.h"

// forward declarations
struct str token_type(struct token token);

struct str debug_token(struct token token) {
    struct str debug_str = str_from("{ type = ");
    str_concat(&debug_str, token_type(token));
    str_concat(&debug_str, str_from(" value = '"));
    str_concat(&debug_str, token.value);
    str_concat(&debug_str, str_from("' }"));

    return debug_str;
}

// helpers
struct str token_type(struct token token) {
    switch (token.type) {
    case INTEGER: return str_from("INTEGER");
    case ADD: return str_from("ADD");
    case SUBTRACT: return str_from("SUBTRACT");
    }
}

