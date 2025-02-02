#ifndef GLOBAL_H

#define GLOBAL_H

#include "./common.h"
#include "./utils/linked_list.h"
#include "./object/core.h"

struct s_config {
    char *title;
    char *base_dir;
    uint32 window_height;
    uint32 window_width;
    uint16 target_fps;
    Font font;
};

typedef struct s_config config;

#define REGISTER_SCENE(name)                                        \
    scene_core *name();                                             \
    __attribute__((constructor)) static void register_##name() {    \
        name();                                                     \
    }

#define REGISTER_OBJECT(name)                                       \
    object_core *name();                                             \
    __attribute__((constructor)) static void register_##name() {    \
        name();                                                     \
    }

extern linked_list g_data;
extern linked_list g_scenes;
extern linked_list g_objects;
extern config g_config;

char *path_assets(char *path);

#endif // !GLOBAL_H
