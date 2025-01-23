#include "home.h"

void scene_home_create() {
    
}

void scene_home_update() {
    
}

void scene_home_destroy() {
    
}

scene_core *scene_home() {
    scene_core *scene;

    scene = scene_core_alloc("home");
    scene->create = scene_home_create;
    scene->update = scene_home_update;
    scene->destroy = scene_home_destroy;
    
    return (scene);
}