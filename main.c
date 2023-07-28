#include <stdio.h>
#include <stdbool.h>
#include "lib/str/str.h"

int main() {
    char character;

    while (true) {
        struct str* line = str_new();
        printf("> ");
        while ((character = fgetc(stdin)) != '\n') {
            str_push(line, character);
        }

        printf("'%s'\n", cstr(line));
    }

    return 0;
}
