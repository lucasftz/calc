#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "lib/lex/lex.h"
#include "lib/eval/eval.h"
#include "lib/token/token.h"
#include "lib/object/object.h"

int main() {
    struct vec stack = vec_new(sizeof(struct object));
    char character;

    while (true) {
        struct str line = str_new();

        printf("> ");
        while ((character = fgetc(stdin)) != '\n') {
            str_push(&line, character);
        }

        struct vec tokens = lex(line);
        size_t return_count = eval(tokens, &stack);

        if (return_count <= 0) { continue; }
        struct object* return_object = vec_access(stack, stack.len - 1);
        if (return_object == NULL) {
            fprintf(stderr, "something went wrong\n");
            exit(1);
        }

        switch (return_object->tag) {
        case I32: printf("%d\n", return_object->value.i32); break;
        }
    }

    return 0;
}
