#include "./global.h"

linked_list g_data = {
    .head = NULL,
    .size = 0,
};

linked_list g_scenes = {
    .head = NULL,
    .size = 0,
};

linked_list g_objects = {
    .head = NULL,
    .size = 0,
};

config g_config = {
    .title = "Example Window Title",
    .base_dir = "./",
    .window_width = 1200,
    .window_height = 690,
    .target_fps = 60,
};

char *path_assets(char *path) {
    char *concated;
    size_t path_length, base_dir_length, assets_length;

    path_length = strlen(path);
    base_dir_length = strlen(g_config.base_dir);
    assets_length = strlen("assets/");

    concated = MALLOC(path_length + base_dir_length + assets_length + 1);
    ASSERT_MSG(concated != NULL, "String allocation failed");

    memcpy(concated, g_config.base_dir, base_dir_length);
    memcpy(concated + base_dir_length, "assets/", assets_length);
    memcpy(concated + base_dir_length + assets_length, path, path_length);
    concated[base_dir_length + assets_length + path_length] = '\0';

    return concated;
}

char *path_data(char *path) {
    char *concated;
    size_t path_length, base_dir_length, data_length;

    path_length = strlen(path);
    base_dir_length = strlen(g_config.base_dir);
    data_length = strlen("data/");

    concated = MALLOC(path_length + base_dir_length + data_length + 1);
    ASSERT_MSG(concated != NULL, "String allocation failed");

    memcpy(concated, g_config.base_dir, base_dir_length);
    memcpy(concated + base_dir_length, "data/", data_length);
    memcpy(concated + base_dir_length + data_length, path, path_length);
    concated[base_dir_length + data_length + path_length] = '\0';

    return concated;
}