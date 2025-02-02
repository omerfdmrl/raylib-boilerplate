#define RAYGUI_IMPLEMENTATION
#include "menu.h"
#include "raygui.h"
#include "raygui_style_terminal.h"

Rectangle startButton = {0};
Rectangle optionsButton = {0};
Rectangle exitButton = {0};

void scene_menu_create() {
    GuiLoadStyleTerminal();

    startButton = (Rectangle) { g_config.window_width/2 - 100, g_config.window_height/2 - 50, 200, 40 };
    optionsButton = (Rectangle) { g_config.window_width/2 - 100, g_config.window_height/2, 200, 40 };
    exitButton = (Rectangle) { g_config.window_width/2 - 100, g_config.window_height/2 + 50, 200, 40 };
}

void scene_menu_update() {
    ClearBackground((Color) {0, 0, 0, 0});
    DrawText("Main Menu", g_config.window_width/2 - MeasureText("Main Menu", 40)/2, 50, 40, DARKGRAY);

    if (g_status.paused) {
        if (GuiButton(startButton, "Resume Game")) {
            game_pause();
            scene_change("game", true, false);
        }
    }else {
        if (GuiButton(startButton, "Start Game"))
            scene_change("game", true, true);
    }

    if (GuiButton(optionsButton, "Settings"))
        scene_change("settings", false, true);

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

Rectangle backButton = {0};

void scene_settings_create() {
    backButton = (Rectangle) { g_config.window_width/2 - 100, g_config.window_height/2 + 50, 200, 40 };
}

void scene_settings_update() {
    ClearBackground((Color) {0, 0, 0, 0});
    DrawText("Settings", g_config.window_width/2 - MeasureText("Settings", 40)/2, 50, 40, DARKGRAY);
    
    if (GuiButton(backButton, "Back to main menu"))
        scene_change("menu", true, false);
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
