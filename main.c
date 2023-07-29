#include <stdio.h>
#include <stdbool.h>

#include "lib/lex/lex.h"
#include "lib/token/token.h"

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
            char* tkn_type;
            switch (tkn->type) {
            case INTEGER:
                tkn_type = "INTEGER";
                break;
            }

            printf("[token %zu]: { type = %s value = '%s' }\n", i, tkn_type, cstr(tkn->value));
        }
    }

    return 0;
}
