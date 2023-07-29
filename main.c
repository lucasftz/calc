#include <stdio.h>
#include <stdbool.h>

#include "lib/lex/lex.h"
#include "lib/eval/eval.h"
#include "lib/token/token.h"
#include "lib/object/object.h"

int main() {
    char character;

    while (true) {
        struct str line = str_new();

        printf("> ");
        while ((character = fgetc(stdin)) != '\n') {
            str_push(&line, character);
        }

        struct vec tokens = lex(line);
        struct vec stack = eval(tokens);
        struct object* return_object = vec_pop(&stack);

        if (return_object != NULL) {
            switch (return_object->tag) {
            case I32: printf("%d\n", return_object->value.i32); break;
            }
        }
    }

    return 0;
}
