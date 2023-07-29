#include <stdio.h>
#include <stdbool.h>

#include "lib/lex/lex.h"

int main() {
    char character;

    while (true) {
        struct str line = str_new();

        printf("> ");
        while ((character = fgetc(stdin)) != '\n') {
            str_push(&line, character);
        }

        struct vec tokens = lex(line);
    }

    return 0;
}
