#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "vec.h"

struct vec vec_new(size_t item_size) {
    return (struct vec) {
        .capacity = 5,
        .len = 0,
        .item_size = item_size,
        .data = malloc(5 * sizeof(void*) + 5 * item_size),
    };
}

void vec_push(struct vec* self, void* item) {
    if (item == NULL) { return; }

    // TODO: realloc if necessary

    self->data[self->len] = item;
    self->len++;
}

void* vec_access(struct vec self, size_t index) {
    if (index >= self.len) {
        return NULL;
    }

    return self.data[index];
}

void vec_remove_last(struct vec* self) {
    if (self->len == 0) { return; }

    free(self->data[self->len - 1]);
    self->data[self->len - 1] = NULL;
    self->len--;
}

void* vec_pop(struct vec* self) {
    if (self->len == 0) {
        return NULL;
    }

    void* item_copy = malloc(self->item_size);
    memcpy(item_copy, vec_access(*self, self->len - 1), self->item_size);
    vec_remove_last(self);
    return item_copy;
}

