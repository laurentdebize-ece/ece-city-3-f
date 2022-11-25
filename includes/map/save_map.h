//
// Created by eleuc on 15/11/2022.
//

#ifndef PROJET_SAVE_MAP_H
#define PROJET_SAVE_MAP_H

#include "map.h"
#include "../basics/time.h"
#include "../buildings/house.h"
#include "../buildings/water_tower.h"
#include "../buildings/power_plant.h"
#include "../buildings/algoConnexite.h"

#define SAVE_1_PATH "../assets/map/save_1.txt"

void save_map(Map_t *map, Queue_t *house, Queue_t *water_tower, Queue_t *power_plant, Time_t *time, int money, char *path);

void load_saved_map(Map_t **map, Queue_t **house, Queue_t **water_tower, Queue_t **power_plant, Time_t *time, int *money, int *population, char *path);

#endif //PROJET_SAVE_MAP_H
