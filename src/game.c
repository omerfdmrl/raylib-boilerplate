#include "game.h"

void game_loop() {
    while (!WindowShouldClose() && g_status.running) {
        g_delta = GetFrameTime();

        if (g_status.fullscreen)
            SetWindowSize(GetMonitorWidth(g_status.monitor), GetMonitorHeight(g_status.monitor));
        else
            SetWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
        
        BeginDrawing();

        if (g_status.scene->update)
            g_status.scene->update();

        EndDrawing();
    }
}

void game_start() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    g_status.monitor = GetCurrentMonitor();

    scene_change("menu");

    game_loop();

    CloseWindow();
}
