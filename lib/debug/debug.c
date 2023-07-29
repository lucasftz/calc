#include <stdio.h>
#include "debug.h"

// forward declarations
struct str token_type(struct token token);
struct str object_type(struct object object);

// main functions
struct str debug_token(struct token token) {
    struct str debug_str = str_from("{ type = ");
    str_concat(&debug_str, token_type(token));
    str_concat(&debug_str, str_from(" value = '"));
    str_concat(&debug_str, token.value);
    str_concat(&debug_str, str_from("' }"));

    return debug_str;
}

struct str debug_object_value(struct object object) {
    char buffer[20];

    switch (object.tag) {
    case I32: sprintf(buffer, "%d", object.value.i32); return str_from(buffer);
    }
}

struct str debug_object(struct object object) {
    struct str debug_str = str_from("{ type = ");
    str_concat(&debug_str, object_type(object));
    str_concat(&debug_str, str_from(" value = '"));
    str_concat(&debug_str, debug_object_value(object));
    str_concat(&debug_str, str_from("' }"));

    return debug_str;
}

// helpers
struct str token_type(struct token token) {
    switch (token.type) {
    case INTEGER: return str_from("INTEGER");
    case ADD: return str_from("ADD");
    case SUBTRACT: return str_from("SUBTRACT");
    case PRINT: return str_from("PRINT");
    }
}

struct str object_type(struct object object) {
    switch (object.tag) {
    case I32: return str_from("I32");
    }
}

