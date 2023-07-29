#include <stdio.h>
#include "lex.h"

struct lexer {
    struct str source;
    struct vec tokens;
    size_t column;
};

struct lexer lexer_new(struct str source) {
    return (struct lexer) {
        .source = source,
        .tokens = vec_new(1),
        .column = 0,
    };
}

// FORWARD DECLARATIONS

char next_char(struct lexer* lexer);
char current_char(struct lexer lexer);

struct vec lex(struct str source) {
    struct lexer lexer = lexer_new(source);

    while (next_char(&lexer) != EOF) {
        switch (current_char(lexer)) {
            default:
                printf("TODO: handle char '%c'\n", current_char(lexer));
                break;
        }
    }

    return lexer.tokens;
}

// LEXER HELPERS

char next_char(struct lexer* lexer) {
    char* next_character = str_char_at(lexer->source, lexer->column);
    if (next_character == NULL) {
        return EOF;
    }

    lexer->column++;
    return *next_character;
}

char current_char(struct lexer lexer) {
    char* current_character = str_char_at(lexer.source, lexer.column - 1);
    return current_character == NULL ? EOF : *current_character;
}

