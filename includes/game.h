//
// Created by eleuc on 20/11/2022.
//

#ifndef PROJET_GAME_H
#define PROJET_GAME_H

#include "basics/camera.h"
#include "buildings/build.h"
#include "basics/time.h"
#include "buildings/house.h"
#include "buildings/water_tower.h"
#include "buildings/power_plant.h"
#include "hud.h"
#include "map/save_map.h"
#include "buildings/algoConnexite.h"

typedef struct Game_t {
    Camera camera;
    Time_t time;
    Queue_t *house;
    Queue_t *water_tower;
    Queue_t *power_plant;
    Hud_t *hud;
    Map_t *map;
    int money;
    int population;
} Game_t;

Game_t *create_game(void);



#endif //PROJET_GAME_H
