#include "status.h"

status g_status = {
    .scene = 0,
    .debug = 0,
    .paused = 0
};

void scene_change(uint8 id) {
    if (id == g_scenes.menu) {
        g_status.scene = scene_menu();
    }else if (id == g_scenes.home) {
        g_status.scene = scene_home();
    }
    
};