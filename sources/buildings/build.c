//
// Created by eleuc on 31/10/2022.
//

#include "../../includes/buildings/build.h"

bool is_possible_to_build(Map_t *map, Vector2 building_core_position, TileType building_varient, int money){
    switch (building_varient) {
        case Tile_Type_Road:
            if(money < ROAD_PRICE || building_core_position.x < 0 || building_core_position.x > map->width || building_core_position.y < 0 || building_core_position.y > map->height || map->tiles[(int)building_core_position.y*map->width+(int)building_core_position.x]->type != Tile_Type_Grass){
                return false;
            }
            return true;
        case Tile_Type_House:

            if (money < HOUSE_PRICE || building_core_position.x - 1 < 0 || building_core_position.x + 1 > map->width || building_core_position.y - 1 < 0 || building_core_position.y + 1 > map->height){
                return false;
            }
            bool is_there_road = false;
            for (int y = (int)building_core_position.y - 1; y <= (int)building_core_position.y + 1; ++y) {
                for (int x = (int)building_core_position.x - 1; x <= (int)building_core_position.x + 1; ++x) {
                    if (map->tiles[y * map->width + x]->type != Tile_Type_Grass)
                        return false;
                    if (!is_there_road){
                        if (x == (int)building_core_position.x - 1 && x-1 >= 0){
                            if (map->tiles[y * map->width + (x-1)]->type == Tile_Type_Road)
                                is_there_road = true;
                        }
                        if (x == (int)building_core_position.x + 1 && x+1 < map->width){
                            if (map->tiles[y * map->width + (x+1)]->type == Tile_Type_Road)
                                is_there_road = true;
                        }
                        if (y == (int)building_core_position.y - 1 && y-1 >= 0){
                            if (map->tiles[(y-1) * map->width + x]->type == Tile_Type_Road)
                                is_there_road = true;
                        }
                        if (y == (int)building_core_position.y + 1 && y+1 < map->height){
                            if (map->tiles[(y+1) * map->width + x]->type == Tile_Type_Road)
                                is_there_road = true;
                        }

                    }
                }
            }
            return is_there_road;
        case Tile_Type_Builing:
            break;
        default:
            break;
    }
}

void test_build_house(Map_t *map, Vector2 building_core_position){
    for (int y = (int)building_core_position.y - 1; y <= (int)building_core_position.y + 1; ++y) {
        for (int x = (int)building_core_position.x - 1; x <= (int)building_core_position.x + 1; ++x) {
            map->tiles[y*map->width + x]->type = Tile_Type_House;
        }
    }
}

void build_one_road(Map_t *map, Vector2 building_core_position){
    bool north = false;
    bool south = false;
    bool east = false;
    bool west = false;
    map->tiles[(int)building_core_position.y*map->width+(int)building_core_position.x]->type = Tile_Type_Road;
    map->tiles[(int)building_core_position.y*map->width+(int)building_core_position.x]->varient = ROAD_ALONE;
    if (building_core_position.x - 1 >= 0){
        if (map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x - 1]->type == Tile_Type_Road)
            west = true;
    }
    if (building_core_position.x + 1 < map->width){
        if (map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x + 1]->type == Tile_Type_Road)
            east = true;
    }
    if (building_core_position.y - 1 >= 0){
        if (map->tiles[((int)building_core_position.y - 1) * map->width + (int)building_core_position.x]->type == Tile_Type_Road)
            north = true;
    }
    if (building_core_position.y + 1 < map->height){
        if (map->tiles[((int)building_core_position.y + 1) * map->width + (int)building_core_position.x]->type == Tile_Type_Road)
            south = true;
    }
    if(!north && !south && !east && !west)
        return;
    else if (north && south && east && west){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_NSEW;
    } else if (north && south && east){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_NSE;
    } else if (north && south && west){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_NSW;
    } else if (north && east && west){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_NEW;
    } else if (south && east && west){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_SEW;
    } else if (north && south){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_NS;
    } else if (east && west){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_EW;
    } else if (north && east){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_NE;
    } else if (north && west){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_NW;
    } else if (south && east){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_SE;
    } else if (south && west){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_SW;
    } else if (north){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_N;
    } else if (south){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_S;
    } else if (east){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_E;
    } else if (west){
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Road;
        map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = ROAD_W;
    }
}

int build_line_of_road(Map_t *map, Vector2 start, Vector2 end){
    Vector2 current = start;
    Vector2 direction = Vector2Subtract(end, start);
    direction = Vector2Normalize(direction);
    int nb_roads_built = 0;

    do {
        if(is_possible_to_build(map, current, Tile_Type_Road, ROAD_PRICE)){
            build_one_road(map, current);
            nb_roads_built++;
        }
        current = Vector2Add(current, direction);
    } while (Vector2Distance(current, end) >= 1);
    if(is_possible_to_build(map, current, Tile_Type_Road, ROAD_PRICE)){
        build_one_road(map, current);
        nb_roads_built++;
    }
    return nb_roads_built;
}