//
// Created by eleuc on 31/10/2022.
//

#ifndef PROJET_BUILD_H
#define PROJET_BUILD_H

#include <raylib.h>
#include "../basics/vectors.h"
#include "../map/map_draw.h"

#define ROAD_PRICE 10
#define HOUSE_PRICE 1000

bool is_possible_to_build(Map_t *map, Vector2 building_core_position, TileType building_varient, int money);

void test_build_house(Map_t *map, Vector2 building_core_position);

void build_one_road(Map_t *map, Vector2 building_core_position);

void build_line_of_road(Map_t *map, Vector2 start, Vector2 end, int *money);

void build_roads(Map_t *map, Vector2 mouse_pos_world, Vector2 *first_road_coord, Vector2 *second_road_coord, Vector2 *last_road_coord, int *money, bool is_mouse_in_map);

#endif //PROJET_BUILD_H