#ifndef str_h
#define str_h

#include <stddef.h>

struct str {
    size_t capacity;
    size_t len;
    char* data;
};

struct str str_new();
struct str str_from(char* cstr);
void str_free(struct str* self);
void str_push(struct str* self, char character);
void str_concat(struct str* self, struct str other);
int str_compare(struct str self, struct str other);
char* cstr(struct str self);
size_t str_len(struct str self);
char* str_char_at(struct str self, size_t index);

#endif

