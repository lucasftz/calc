#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "str.h"

struct str* str_new() {
    struct str* str = malloc(sizeof(struct str));

    str->capacity = 5;
	str->len = 0;
	str->data = malloc(sizeof(char) * str->capacity);

	return str;
}

struct str* str_from(char* cstr) {
	struct str* str = malloc(sizeof(struct str));

	str->capacity = strlen(cstr) + 5;
	str->len = strlen(cstr);
	str->data = malloc(sizeof(char) * str->capacity);
	memcpy(str->data, cstr, str->len);
	str->data[str->len] = '\0';

	return str;
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
		self->data = realloc(self->data, self->capacity);
	}

	self->data[self->len] = character;
	self->data[self->len + 1] = '\0';
	self->len++;
}

char* cstr(struct str* self) {
	return self->data;
}

size_t str_len(struct str self) {
	return self.len;
}

char* str_char_at(struct str* self, size_t index) {
	if (index < 0 || index >= self->len) {
		return NULL;
	}

	return &self->data[index];
}  
