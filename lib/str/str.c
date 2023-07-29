#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "str.h"

struct str str_new() {
    char* data = malloc(sizeof(char) * 1);
    data[0] = '\0';
    return (struct str) {
        .capacity = 1,
        .len = 0,
        .data = data,
    };
}

struct str str_from(char* cstr) {
    size_t len = strlen(cstr);
    size_t capacity = len;
    char* data = malloc(sizeof(char) * capacity);
    memcpy(data, cstr, len);
    data[len] = '\0';

    return (struct str) {
        .capacity = capacity,
        .len = len,
        .data = data,
    };
}

void str_free(struct str* self) {
	self->capacity = 0;
	self->len = 0;
	free(self->data);
	free(self);
}

void str_push(struct str* self, char character) {
    if (self->len + 1 >= self->capacity) {
        self->capacity += 5;
        self->data = realloc(self->data, sizeof(char) * self->capacity);
    }

    self->data[self->len] = character;
    self->data[self->len + 1] = '\0';
    self->len++;
}

char* cstr(struct str self) {
	return self.data;
}

size_t str_len(struct str self) {
	return self.len;
}

char* str_char_at(struct str self, size_t index) {
	if (index < 0 || index >= self.len) {
		return NULL;
	}

	return &self.data[index];
}  
