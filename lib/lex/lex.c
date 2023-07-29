#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "lex.h"
#include "../token/token.h"

struct lexer {
    struct str source;
    struct vec tokens;
    size_t column;
};

struct lexer lexer_new(struct str source) {
    return (struct lexer) {
        .source = source,
        .tokens = vec_new(sizeof(struct token)),
        .column = 0,
    };
}

// forward declarations
char next_char(struct lexer* lexer);
char current_char(struct lexer lexer);
void lexer_push_token(struct lexer* self, struct token token);

// main function
struct vec lex(struct str source) {
    struct lexer lexer = lexer_new(source);

    while (next_char(&lexer) != EOF) {
        switch (current_char(lexer)) {
        case ' ': case '\n': case '\t': break;
        case '+':
            lexer_push_token(&lexer, token_new(ADD, str_from("+")));
            break;
        case '-':
            lexer_push_token(&lexer, token_new(SUBTRACT, str_from("-")));
            break;
        case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
            struct str number_str = str_new();
            char next = current_char(lexer);

            while (next != EOF && isdigit(next)) {
                str_push(&number_str, next);
                next = next_char(&lexer);
            }

            lexer_push_token(&lexer, token_new(INTEGER, number_str));
            if (next != EOF) { lexer.column--; }
            break;
        }
        default:
            printf("TODO: handle char '%c'\n", current_char(lexer));
            break;
        }
    }

    return lexer.tokens;
}

// lexer helpers
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

void lexer_push_token(struct lexer* self, struct token token) {
    struct token* tkn = malloc(sizeof(struct token));
    tkn->type = token.type;
    tkn->value = token.value;

    vec_push(&self->tokens, tkn);
}

