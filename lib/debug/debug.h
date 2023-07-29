#ifndef debug_h
#define debug_h

#include "../token/token.h"
#include "../object/object.h"

struct str debug_token(struct token token);
struct str debug_object(struct object object);

#endif
