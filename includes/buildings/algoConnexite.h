//
// Created by theos on 09/11/2022.
//

#ifndef PROJET_ALGOCONNEXITE_H
#define PROJET_ALGOCONNEXITE_H

#include "../map/map.h"
#include "../basics/queue_file.h"
#include "../buildings/house.h"
#include "../buildings/water_tower.h"
#include "../buildings/power_plant.h"

void connexite(Map_t *map);

void connexity_init(Map_t *map);

void reset_connexity(Map_t *map);

#endif //PROJET_ALGOCONNEXITE_H
