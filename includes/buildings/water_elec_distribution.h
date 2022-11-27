//
// Created by eleuc on 22/11/2022.
//

#ifndef PROJET_WATER_ELEC_DISTRIBUTION_H
#define PROJET_WATER_ELEC_DISTRIBUTION_H

#include "house.h"
#include "water_tower.h"
#include "power_plant.h"

typedef struct {
    int x;
    int y;
    int distance;
} Cell_t;

typedef struct Building_With_Distance_t{
    void *building;
    int distance;
}Building_With_Distance_t;

Cell_t *create_cell(int x, int y, int distance);

Building_With_Distance_t *create_building_with_distance(void *building, int distance);

void add_house_to_power_plant_by_level(Power_Plant_t *power_plant, House_t *house);

void water_tower_add_house(Map_t *map);

bool is_water_tower_connected_to_house(Water_Tower_t *water_tower, House_t *house);

void add_house_to_water_tower(Water_Tower_t *water_tower, House_t *house, int distance);

void link_house_to_water_towers(Map_t *map, House_t *house);

void link_all_houses_to_water_towers(Map_t* map, Queue_t* houses);

void share_water(Queue_t *houses);

void reset_water_canalisations(Map_t *map);

void reset_houses_water(Queue_t *houses);



#endif //PROJET_WATER_ELEC_DISTRIBUTION_H
