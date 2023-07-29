#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "vec.h"

struct vec vec_new(size_t item_size) {
    return (struct vec) {
        .capacity = 5,
        .len = 0,
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

