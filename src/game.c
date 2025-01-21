#include "game.h"

void game_loop() {
    while (!WindowShouldClose()) {
        g_delta = GetFrameTime();
        
        BeginDrawing();

        if (g_status.scene->update)
            g_status.scene->update();

        EndDrawing();
    }
}

void game_start() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    scene_change(g_scenes.menu);

    if (g_status.scene->create)
        g_status.scene->create();

    game_loop();

    if (g_status.scene->destroy)
        g_status.scene->destroy();


    CloseWindow();
}
