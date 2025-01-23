#include "settings.h"
#include "raygui.h"
#include "raygui_style_terminal.h"

Rectangle backButton;

void scene_settings_create() {
    GuiLoadStyleTerminal();
    backButton = (Rectangle) { WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 50, 200, 40 };
}

void scene_settings_update() {
    ClearBackground((Color) {0, 0, 0, 0});
    DrawText("Settings", WINDOW_WIDTH/2 - MeasureText("Settings", 40)/2, 50, 40, DARKGRAY);
    
    if (GuiButton(backButton, "Back to main menu"))
        scene_change("menu");
}

void scene_settings_destroy() {
    
}

scene_core *scene_settings() {
    scene_core *scene;

    scene = scene_core_alloc("settings");
    scene->create = scene_settings_create;
    scene->update = scene_settings_update;
    scene->destroy = scene_settings_destroy;
    
    return (scene);
}