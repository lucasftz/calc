#ifndef eval_h
#define eval_h

#include "../token/token.h"
#include "../vec/vec.h"

size_t eval(struct vec tokens, struct vec* stack);

#endif
