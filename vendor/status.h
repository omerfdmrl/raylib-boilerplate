#ifndef STATUS_H

#define STATUS_H

#include "./common.h"
#include "./global.h"
#include "./scene/core.h"

struct s_status {
    scene_core *scene;
    struct {
        uint8 paused: 1;
        uint8 debug: 1;
    };
};

typedef struct s_status status;

extern status g_status;

void scene_change(char *name);

#endif // !STATUS_H