#ifndef GLOBAL_H

#define GLOBAL_H

#include "common.h"
#include "scenes/core.h"

#define WINDOW_TITLE "Example Window Title"
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#define TARGET_FPS 60

struct s_scenes {
    uint32 menu: 8;
    uint32 home: 8;
};

typedef struct s_scenes scenes;

extern scenes g_scenes;
extern float g_delta;

#endif // !GLOBAL_H
