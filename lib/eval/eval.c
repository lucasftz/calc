#include <stdio.h>
#include "eval.h"
#include "../debug/debug.h"

struct evaluator {
    struct vec tokens;
    size_t index;
};

struct evaluator evaluator_new(struct vec tokens) {
    return (struct evaluator) {
        .tokens = tokens,
        .index = 0,
    };
}

// forward declarations
struct token* next_token(struct evaluator* evaluator);
struct token* current_token(struct evaluator evaluator);

// main function
struct str eval(struct vec tokens) {
    if (tokens.len == 0) { return str_new(); }
    struct evaluator evaluator = evaluator_new(tokens);

    do {
        printf("[token %zu]: %s\n", evaluator.index, cstr(debug_token(*current_token(evaluator))));
    } while (next_token(&evaluator) != NULL);

    return str_new();
}

struct token* next_token(struct evaluator* evaluator) {
    evaluator->index++;
    return vec_access(evaluator->tokens, evaluator->index);
}

struct token* current_token(struct evaluator evaluator) {
    return vec_access(evaluator.tokens, evaluator.index);
}

