//
// Created by eleuc on 31/10/2022.
//

#ifndef PROJET_BUILD_H
#define PROJET_BUILD_H

#include <raylib.h>
#include "../map/map_draw.h"

#define ROAD_PRICE 10
#define HOUSE_PRICE 1000

bool is_possible_to_build(Map_t *map, Vector2 building_core_position, TileType building_varient, int money);

void test_build_house(Map_t *map, Vector2 building_core_position);

void build_one_road(Map_t *map, Vector2 building_core_position);

int build_line_of_road(Map_t *map, Vector2 start, Vector2 end);

#endif //PROJET_BUILD_H