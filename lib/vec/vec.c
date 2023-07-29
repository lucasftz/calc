#include <stdlib.h>
#include "vec.h"

struct vec vec_new(size_t item_size) {
    return (struct vec) {
        .capacity = 5,
        .len = 0,
        .data = malloc(item_size * 5)
    };
}
