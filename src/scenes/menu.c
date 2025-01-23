#define RAYGUI_IMPLEMENTATION
#include "menu.h"
#include "raygui.h"
#include "raygui_style_terminal.h"

Rectangle startButton;
Rectangle optionsButton;
Rectangle exitButton;

void scene_menu_create() {
    GuiLoadStyleTerminal();
    startButton = (Rectangle) { WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 50, 200, 40 };
    optionsButton = (Rectangle) { WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2, 200, 40 };
    exitButton = (Rectangle) { WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 50, 200, 40 };
}

void scene_menu_update() {
    ClearBackground((Color) {0, 0, 0, 0});
    DrawText("Main Menu", WINDOW_WIDTH/2 - MeasureText("Main Menu", 40)/2, 50, 40, DARKGRAY);

    if (GuiButton(startButton, "Start Game"))
        DrawText("Game Started", WINDOW_WIDTH/2 - MeasureText("Game Started", 20)/2, WINDOW_HEIGHT/2 + 100, 20, GREEN);

    if (GuiButton(optionsButton, "Settings"))
        scene_change("settings");

    if (GuiButton(exitButton, "Exit"))
        game_close();
}

void scene_menu_destroy() {

}

scene_core *scene_menu() {
    scene_core *scene;

    scene = scene_core_alloc("menu");
    scene->create = scene_menu_create;
    scene->update = scene_menu_update;
    scene->destroy = scene_menu_destroy;

    return (scene);
}
