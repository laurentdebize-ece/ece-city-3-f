//
// Created by eleuc on 31/10/2022.
//

#include "../includes/build.h"

bool is_there_place_to_build(Map_t *map, Vector2 building_core_position, TileType building_varient){
    switch (building_varient) {
        case TILE_ROAD:
            if (map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type == TILE_GRASS)
                return true;
            return false;
        case TILE_HOUSE:
            if (building_core_position.x - 1 < 0 || building_core_position.x + 1 > map->width || building_core_position.y - 1 < 0 || building_core_position.y + 1 > map->height){
                return false;
            }
            for (int y = (int)building_core_position.y - 1; y <= (int)building_core_position.y + 1; ++y) {
                for (int x = (int)building_core_position.x - 1; x <= (int)building_core_position.x + 1; ++x) {
                    if (map->tiles[y * map->width + x]->type != TILE_GRASS)
                        return false;
                }
            }
            for (int i = 0; i < ; ++i) {

            }
            return true;
            break;
        case TILE_BUILDING:
            break;
    }
}

void test_build_house(Map_t *map, Vector2 building_core_position){
    for (int y = (int)building_core_position.y - 1; y <= (int)building_core_position.y + 1; ++y) {
        for (int x = (int)building_core_position.x - 1; x <= (int)building_core_position.x + 1; ++x) {
            map->tiles[y*map->width + x]->type = TILE_HOUSE;
        }
    }
}