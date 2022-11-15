//
// Created by eleuc on 15/11/2022.
//

#ifndef PROJET_SAVE_MAP_H
#define PROJET_SAVE_MAP_H

#include "map.h"
#include "../basics/time.h"
#include "../buildings/house.h"

#define SAVE_1_PATH "../assets/map/save_1.txt"

void save_map(Map_t *map, House_t *house, Time_t *time, int money, char *path);

void load_saved_map(Map_t **map, House_t **house, Time_t *time, int *money, char *path);

#endif //PROJET_SAVE_MAP_H
