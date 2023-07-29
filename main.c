#include <stdio.h>
#include <stdbool.h>

#include "lib/lex/lex.h"
#include "lib/token/token.h"
#include "lib/debug/debug.h"

int main() {
    char character;

    while (true) {
        struct str line = str_new();

        printf("> ");
        while ((character = fgetc(stdin)) != '\n') {
            str_push(&line, character);
        }

        struct vec tokens = lex(line);

        for (size_t i = 0; i < tokens.len; i++) {
            struct token* tkn = vec_access(tokens, i);

            printf("[token %zu]: %s\n", i, cstr(debug_token(*tkn)));
        }
    }

    return 0;
}
