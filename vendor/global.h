#ifndef GLOBAL_H

#define GLOBAL_H

#include "./common.h"
#include "./utils/map.h"

#define WINDOW_TITLE "Example Window Title"
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#define TARGET_FPS 60

#define REGISTER_SCENE(name)                                     \
    scene_core *name();                                                \
    __attribute__((constructor)) static void register_##symbol_name() {    \
        name();                        \
    }

extern map g_scenes;
extern float g_delta;

#endif // !GLOBAL_H
