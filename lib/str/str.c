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
    char* data = malloc(sizeof(char) * (len + 1));
    memcpy(data, cstr, len);
    data[len] = '\0';

    return (struct str) {
        .capacity = len,
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

void str_concat(struct str* self, struct str other) {
    if (self->len + other.len > self->capacity) {
        size_t new_capacity = self->len + other.len;
        char* new_data = malloc(new_capacity + 1);
        memcpy(new_data, self->data, self->len);
        free(self->data);
        self->data = new_data;
        self->capacity = new_capacity;
    }

    memcpy(self->data + self->len, other.data, other.len);
    self->len += other.len;
    self->data[self->len] = '\0';
}

