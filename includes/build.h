//
// Created by eleuc on 31/10/2022.
//

#ifndef PROJET_BUILD_H
#define PROJET_BUILD_H

#include <raylib.h>
#include "map/map_draw.h"

bool is_there_place_to_build(Map_t *map, Vector2 building_core_position, TileType building_varient);

void test_build_house(Map_t *map, Vector2 building_core_position);

#endif //PROJET_BUILD_H
