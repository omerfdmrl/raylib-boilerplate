#include "game.h"
#include <GLFW/glfw3.h>

void game_loop() {
    while (!WindowShouldClose() && g_status.running) {
        if (g_status.fullscreen)
            SetWindowSize(GetMonitorWidth(g_status.monitor), GetMonitorHeight(g_status.monitor));
        else
            SetWindowSize(g_config.window_width, g_config.window_height);

        if (IsKeyPressed(KEY_ESCAPE)) {
            game_pause();
            scene_change("menu", false, false);
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (g_status.scene->update)
            g_status.scene->update();
        EndDrawing();
    }
}

void game_start() {
    char *font_asset_path;

    InitWindow(g_config.window_height, g_config.window_width, g_config.title);
    SetTargetFPS(g_config.target_fps);

    SetExitKey(0);

    g_status.monitor = GetCurrentMonitor();

    font_asset_path = path_assets("Fonts/Ubuntu-Regular.ttf");
    g_config.font = LoadFontEx(font_asset_path, 96, NULL, 0);
    FREE(font_asset_path);

    scene_change("menu", true, true);

    game_loop();

    CloseWindow();
}
