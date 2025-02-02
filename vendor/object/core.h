#ifndef OBJECT_CORE_H

#define OBJECT_CORE_H

typedef struct s_object_core object_core;

#include "../status.h"
#include "../helpers/tilemap.h"

struct s_object_core {
    char *name;
    void (*create)();
    void (*update)();
    void (*draw)();
    void (*destroy)();
};

object_core *object_core_alloc(char *name);
void object_core_free(object_core *scene);

#endif // !OBJECT_CORE_H