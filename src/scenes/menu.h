#ifndef SCENE_MENU_H

#define SCENE_MENU_H

#include "scene/core.h"
#include "../global.h"

REGISTER_SCENE(scene_menu);
REGISTER_SCENE(scene_settings)

scene_core *scene_menu();
scene_core *scene_settings();

#endif // !SCENE_MENU_H