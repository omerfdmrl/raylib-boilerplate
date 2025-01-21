#ifndef SCENE_CORE_H

#define SCENE_CORE_H

#include "../common.h"

struct s_scene_core {
    uint8 id;
    void (*create)();
    void (*update)();
    void (*destroy)();
};

typedef struct s_scene_core scene_core;

scene_core *scene_core_alloc(uint8 id);
void scene_core_free(scene_core *scene);

#endif // !SCENE_CORE_H