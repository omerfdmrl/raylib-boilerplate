#ifndef STATUS_H

#define STATUS_H

#include "./common.h"
#include "./global.h"
#include "./scene/core.h"
#include "./object/core.h"

struct s_status {
    scene_core *scene;
    struct {
        uint8 running: 1;
        uint8 paused: 1;
        uint8 debug: 1;
        uint8 fullscreen: 1;
    };

    int monitor;
};

typedef struct s_status status;

extern status g_status;

void scene_change(char *name, bool call_destroy, bool call_create);
void game_close();
void game_pause();
void game_fullscreen();

#endif // !STATUS_H