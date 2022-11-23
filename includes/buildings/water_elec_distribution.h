//
// Created by eleuc on 22/11/2022.
//

#ifndef PROJET_WATER_ELEC_DISTRIBUTION_H
#define PROJET_WATER_ELEC_DISTRIBUTION_H

#include "house.h"
#include "water_tower.h"
#include "power_plant.h"

void add_house_by_level(Power_Plant_t *power_plant, House_t *house);

void water_tower_add_house(Map_t *map);

#endif //PROJET_WATER_ELEC_DISTRIBUTION_H
