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

            if (money < HOUSE_PRICE || building_core_position.x - 1 < 0 || building_core_position.x + 1 >= map->width || building_core_position.y - 1 < 0 || building_core_position.y + 1 >= map->height){
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
    /// On ajoute une route sur la case
    map->tiles[(int)building_core_position.y*map->width+(int)building_core_position.x]->type = Tile_Type_Road;
    /// On ajoute les côtés de la route
    if (building_core_position.x - 1 >= 0){ /// Si on n'est pas sur le bord gauche
        /// Si la case à gauche est une route
        if (map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x - 1]->type == Tile_Type_Road){
            /// On ajoute le côté gauche
            map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient += ROAD_W;
            /// On ajoute le côté droit à la case à gauche
            map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x - 1]->varient += ROAD_E;
        }
    }
    if (building_core_position.x + 1 < map->width) {
        if (map->tiles[(int) building_core_position.y * map->width + (int) building_core_position.x + 1]->type ==Tile_Type_Road){
            map->tiles[(int) building_core_position.y * map->width + (int) building_core_position.x]->varient += ROAD_E;
            map->tiles[(int) building_core_position.y * map->width + (int) building_core_position.x + 1]->varient += ROAD_W;
        }
    }
    if (building_core_position.y - 1 >= 0){
        if (map->tiles[((int)building_core_position.y - 1) * map->width + (int)building_core_position.x]->type == Tile_Type_Road){
            map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient += ROAD_N;
            map->tiles[((int)building_core_position.y - 1) * map->width + (int)building_core_position.x]->varient += ROAD_S;
        }
    }
    if (building_core_position.y + 1 < map->height){
        if (map->tiles[((int)building_core_position.y + 1) * map->width + (int)building_core_position.x]->type == Tile_Type_Road){
            map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient += ROAD_S;
            map->tiles[((int)building_core_position.y + 1) * map->width + (int)building_core_position.x]->varient += ROAD_N;
        }
    }
}

void build_line_of_road(Map_t *map, Vector2 start, Vector2 end, int *money){
    Vector2 current = start;
    Vector2 direction = Vector2Subtract(end, start);
    direction = Vector2Normalize(direction);

    do {
        if(is_possible_to_build(map, current, Tile_Type_Road, *money)){
            build_one_road(map, current);
            *money -= ROAD_PRICE;
        }
        current = Vector2Add(current, direction);
    } while (Vector2Distance(current, end) >= 1);
    if(is_possible_to_build(map, current, Tile_Type_Road, *money)){
        build_one_road(map, current);
        *money -= ROAD_PRICE;
    }
}

void build_roads(Map_t *map, Vector2 mouse_pos_world, Vector2 *first_road_coord, Vector2 *second_road_coord, Vector2 *last_road_coord, int *money, bool is_mouse_in_map){
    /// Si on a cliqué sur la map
    if (IsMouseButtonPressed(Mouse_Button_Left) && is_mouse_in_map) {
        *first_road_coord = mouse_pos_world;
        *second_road_coord = mouse_pos_world;
        *last_road_coord = mouse_pos_world;
    }
    /// Si on garde le clic enfoncé
    else if (IsMouseButtonDown(Mouse_Button_Left)) {
        if (is_vec2D_same(*first_road_coord, *second_road_coord)) {
            *second_road_coord = mouse_pos_world;
        } else if (vec2D_sub(*first_road_coord, *second_road_coord).x) last_road_coord->x = mouse_pos_world.x;
        else last_road_coord->y = mouse_pos_world.y;
    }
    /// Si on relâche le clic
    else if (IsMouseButtonReleased(Mouse_Button_Left)) {
        if (is_mouse_in_map && !is_vec2D_same(*first_road_coord, *last_road_coord)) {
            build_line_of_road(map, *first_road_coord, *last_road_coord, money);
        }
        else if (IsMouseButtonReleased(Mouse_Button_Left) && is_vec2D_same(*first_road_coord, *last_road_coord) &&is_vec2D_same(*first_road_coord, *second_road_coord)) {
            if (is_possible_to_build(map, *first_road_coord, Tile_Type_Road, *money)) {
                build_one_road(map, *first_road_coord);
                money -= ROAD_PRICE;
            }
        }
    }
}

void draw_transparent_house(Map_t *map, Vector2 mouse_pos_world, int money){
    if (is_possible_to_build(map, mouse_pos_world, Tile_Type_House, money)){
        DrawCube((Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, HOUSE_CUBE_WIDTH, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, HOUSE_CUBE_WIDTH, HOUSE_CUBE_WIDTH*2, HOUSE_CUBE_WIDTH,Fade(GREEN, 0.5f));
        DrawCubeWires((Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, HOUSE_CUBE_WIDTH, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, HOUSE_CUBE_WIDTH, HOUSE_CUBE_WIDTH*2, HOUSE_CUBE_WIDTH, Fade(BLACK, 0.5f));
    }
    else{
        DrawCube((Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, HOUSE_CUBE_WIDTH, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, HOUSE_CUBE_WIDTH, HOUSE_CUBE_WIDTH*2, HOUSE_CUBE_WIDTH,Fade(RED, 0.5f));
        DrawCubeWires((Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, HOUSE_CUBE_WIDTH, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, HOUSE_CUBE_WIDTH, HOUSE_CUBE_WIDTH*2, HOUSE_CUBE_WIDTH, Fade(BLACK, 0.5f));
    }
}

