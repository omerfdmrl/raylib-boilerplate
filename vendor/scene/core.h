#ifndef SCENE_CORE_H

#define SCENE_CORE_H

struct s_scene_core {
    char *name;
    void (*create)();
    void (*update)();
    void (*destroy)();
};

typedef struct s_scene_core scene_core;

scene_core *scene_core_alloc(char *name);
void scene_core_free(scene_core *scene);

#endif // !SCENE_CORE_H
