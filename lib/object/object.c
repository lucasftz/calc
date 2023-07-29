#include <stdlib.h>
#include "object.h"

struct object object_new(enum object_tag tag, union object_value value) {
    return (struct object) {
        .tag = tag,
        .value = value,
    };
}

struct object* object_create(enum object_tag tag, union object_value value) {
    struct object* object = malloc(sizeof(struct object));
    object->tag = tag;
    object->value = value;

    return object;
}
