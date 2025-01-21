#define RAYGUI_IMPLEMENTATION

#include "menu.h"
#include "raygui.h"
#include "raygui_style_terminal.h"

bool showMessageBox;

void scene_menu_create() {
    GuiLoadStyleTerminal();
    showMessageBox = false;
}

void scene_menu_update() {
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "#191#Show Message")) showMessageBox = true;

    if (showMessageBox)
    {
        int result = GuiMessageBox((Rectangle){ 85, 70, 250, 100 },
            "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

        if (result >= 0) showMessageBox = false;
    }
}

void scene_menu_destroy() {

}

scene_core *scene_menu() {
    scene_core *scene;

    scene = scene_core_alloc(0);
    scene->create = scene_menu_create;
    scene->update = scene_menu_update;
    scene->destroy = scene_menu_destroy;

    return (scene);
}