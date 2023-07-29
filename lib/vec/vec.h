#ifndef vec_h
#define vec_h

#include <stddef.h>

struct vec {
    size_t capacity;
    size_t len;
    size_t item_size;
    void** data;
};

struct vec vec_new(size_t item_size);
void vec_push(struct vec* self, void* item);
void* vec_access(struct vec self, size_t index);
void* vec_pop(struct vec* self);

#endif

