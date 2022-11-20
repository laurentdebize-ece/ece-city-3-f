//
// Created by eleuc on 20/11/2022.
//

#include "../includes/game.h"

Game_t *create_game(void) {
    Game_t *game = malloc(sizeof(Game_t));
    game->money = 500000;
    game->time = {1,0,0,0,0,3,2069};
    //map = load_map(DEFAULT_MAP_FILE_PATH);
    load_saved_map(&game->map, &game->houses, &game->water_towers, &game->power_plants, &game->time, &game->money, SAVE_1_PATH);
    load_map();
    game->camera = camera_new();
    game->time = create_time();
    game->house = NULL;
    game->water_tower = NULL;
    game->power_plant = NULL;
    game->hud = create_hud();
    game->money = 1000;
    game->population = 0;
    return game;
}