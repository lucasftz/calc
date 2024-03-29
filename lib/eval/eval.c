#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include "eval.h"
#include "../object/object.h"
#include "../debug/debug.h"

struct evaluator {
    struct vec tokens;
    struct vec* stack;
    size_t return_count;
    size_t index;
};

struct evaluator evaluator_new(struct vec tokens, struct vec* stack) {
    return (struct evaluator) {
        .tokens = tokens,
        .stack = stack,
        .return_count = 0,
        .index = 0,
    };
}

// forward declarations
struct token* next_token(struct evaluator* evaluator);
struct token current_token(struct evaluator evaluator);
int32_t to_i32(struct token integer_token);
struct str i32_to_str(int32_t i32);

// main function
size_t eval(struct vec tokens, struct vec* stack) {
    if (tokens.len == 0) { return 0; }
    struct evaluator evaluator = evaluator_new(tokens, stack);

    do {
        switch (current_token(evaluator).type) {
        case INTEGER: {
            int32_t i32 = to_i32(current_token(evaluator));
            struct object* int_object = object_create(I32, (union object_value) { .i32 = i32 });
            vec_push(evaluator.stack, int_object);
            evaluator.return_count++;
            break;
        }
        case ADD: {
            struct object* a = vec_access(*evaluator.stack, evaluator.stack->len - 1);
            if (a == NULL) { fprintf(stderr, "'+' expects 2 i32 values on the stack\n"); break; }
            if (a->tag != I32) { fprintf(stderr, "'+' expects an i32 value\n"); break; }
            
            struct object* b = vec_access(*evaluator.stack, evaluator.stack->len - 2);
            if (b == NULL) { fprintf(stderr, "'+' expects 2 i32 values on the stack\n"); break; }
            if (b->tag != I32) { fprintf(stderr, "'+' expects an i32 value\n"); break; }

            a = vec_pop(evaluator.stack);
            b = vec_pop(evaluator.stack);

            struct object* sum = object_create(I32, (union object_value) { .i32 = a->value.i32 + b->value.i32 });
            vec_push(evaluator.stack, sum);
            evaluator.return_count--;

            break;
        }
        case SUBTRACT: {
            struct object* a = vec_access(*evaluator.stack, evaluator.stack->len - 1);
            if (a == NULL) { fprintf(stderr, "'-' expects 2 i32 values on the stack\n"); break; }
            if (a->tag != I32) { fprintf(stderr, "'-' expects an i32 value\n"); break; }
            
            struct object* b = vec_access(*evaluator.stack, evaluator.stack->len - 2);
            if (b == NULL) { fprintf(stderr, "'-' expects 2 i32 values on the stack\n"); break; }
            if (b->tag != I32) { fprintf(stderr, "'-' expects an i32 value\n"); break; }

            a = vec_pop(evaluator.stack);
            b = vec_pop(evaluator.stack);

            struct object* difference = object_create(I32, (union object_value) { .i32 = a->value.i32 - b->value.i32 });
            vec_push(evaluator.stack, difference);
            evaluator.return_count--;

            break;
        }
        case PRINT: {
            struct object* object = vec_pop(evaluator.stack);
            if (object == NULL) { fprintf(stderr, "Cannot print on an empty stack\n"); break; }
            if (evaluator.return_count > 0) { evaluator.return_count--; }

            switch (object->tag) {
            case I32: printf("%s\n", cstr(i32_to_str(object->value.i32))); break;
            }
            break;
        }}
    } while (next_token(&evaluator) != NULL);

    return evaluator.return_count;
}

struct token* next_token(struct evaluator* evaluator) {
    evaluator->index++;
    return vec_access(evaluator->tokens, evaluator->index);
}

struct token current_token(struct evaluator evaluator) {
    return *(struct token*) vec_access(evaluator.tokens, evaluator.index);
}

int32_t to_i32(struct token integer_token) {
    char* endptr;
    intmax_t num = strtoimax(cstr(integer_token.value), &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "error: Failed to convert '%s' to int32_t\n", cstr(integer_token.value));
        exit(1);
    }

    if (num < INT32_MIN || num > INT32_MAX) {
        fprintf(stderr, "error: '%s' out of i32 range\n", cstr(integer_token.value));
    }

    return num;
}

struct str i32_to_str(int32_t i32) {
    char buffer[20];
    sprintf(buffer, "%d", i32);
    return str_from(buffer);
}

