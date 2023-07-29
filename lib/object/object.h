#ifndef object_h
#define object_h

#include <stdint.h>

enum object_tag {
    I32,
};

union object_value {
    int32_t i32;
};

struct object {
    enum object_tag tag;
    union object_value value;
};

struct object object_new(enum object_tag tag, union object_value value);
struct object* object_create(enum object_tag tag, union object_value value);

#endif
