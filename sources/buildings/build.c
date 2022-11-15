//
// Created by eleuc on 31/10/2022.
//

#include "../../includes/buildings/build.h"

bool is_possible_to_build(Map_t *map, Vector2 building_core_position, TileType building_varient, int money){
    switch (building_varient) {
        case Tile_Type_Road:
            /// Si on n'a pas assez d'argent ou que la case n'est pas vide ou que la souris est hors de la map
            if(money < ROAD_PRICE || building_core_position.x < 0 || building_core_position.x > map->width || building_core_position.y < 0 || building_core_position.y > map->height || map->tiles[(int)building_core_position.y*map->width+(int)building_core_position.x]->type != Tile_Type_Grass){
                return false;
            }
            return true;
        case Tile_Type_House:

            /// Si on n'a pas assez d'argent ou que la souris est hors de la map
            if (money < HOUSE_PRICE || building_core_position.x - 1 < 0 || building_core_position.x + 1 >= map->width || building_core_position.y - 1 < 0 || building_core_position.y + 1 >= map->height){
                return false;
            }
            bool is_there_road = false;
            /// On vérifie que les cases autour de la maison sont vides et qu'il y a une route autour
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
    if (building_core_position.x + 1 < map->width) {    /// Si on n'est pas sur le bord droit
        /// Si la case à droite est une route
        if (map->tiles[(int) building_core_position.y * map->width + (int) building_core_position.x + 1]->type ==Tile_Type_Road){
            /// On ajoute le côté droit
            map->tiles[(int) building_core_position.y * map->width + (int) building_core_position.x]->varient += ROAD_E;
            /// On ajoute le côté gauche à la case à droite
            map->tiles[(int) building_core_position.y * map->width + (int) building_core_position.x + 1]->varient += ROAD_W;
        }
    }
    if (building_core_position.y - 1 >= 0){ /// Si on n'est pas sur le bord haut
        /// Si la case au dessus est une route
        if (map->tiles[((int)building_core_position.y - 1) * map->width + (int)building_core_position.x]->type == Tile_Type_Road){
            /// On ajoute le côté haut
            map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient += ROAD_N;
            /// On ajoute le côté bas à la case au dessus
            map->tiles[((int)building_core_position.y - 1) * map->width + (int)building_core_position.x]->varient += ROAD_S;
        }
    }
    if (building_core_position.y + 1 < map->height){    /// Si on n'est pas sur le bord bas
        /// Si la case en dessous est une route
        if (map->tiles[((int)building_core_position.y + 1) * map->width + (int)building_core_position.x]->type == Tile_Type_Road){
            /// On ajoute le côté bas
            map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient += ROAD_S;
            /// On ajoute le côté haut à la case en dessous
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
        } else if (IsMouseButtonReleased(Mouse_Button_Left) && is_vec2D_same(*first_road_coord, *last_road_coord) &&
                   is_vec2D_same(*first_road_coord, *second_road_coord)) {
            if (is_possible_to_build(map, *first_road_coord, Tile_Type_Road, *money)) {
                build_one_road(map, *first_road_coord);
                money -= ROAD_PRICE;
            }
        }
    }
}

void destroy_one_road(Map_t *map, Vector2 building_core_position){
    /// On enlève la route
    map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->type = Tile_Type_Grass;
    map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x]->varient = 0;
    /// On enlève les côtés
    if (building_core_position.x - 1 >= 0) {    /// Si on n'est pas sur le bord gauche
        /// Si la case à gauche est une route
        if (map->tiles[(int) building_core_position.y * map->width + (int) building_core_position.x - 1]->type ==Tile_Type_Road){
            /// On enlève le côté droit à la case à gauche
            map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x - 1]->varient -= ROAD_E;
        }
    }
    if (building_core_position.x + 1 < map->width) {    /// Si on n'est pas sur le bord droit
        /// Si la case à droite est une route
        if (map->tiles[(int) building_core_position.y * map->width + (int) building_core_position.x + 1]->type ==Tile_Type_Road){
            /// On enlève le côté gauche à la case à droite
            map->tiles[(int)building_core_position.y * map->width + (int)building_core_position.x + 1]->varient -= ROAD_W;
        }
    }
    if (building_core_position.y - 1 >= 0){ /// Si on n'est pas sur le bord haut
        /// Si la case au dessus est une route
        if (map->tiles[((int)building_core_position.y - 1) * map->width + (int)building_core_position.x]->type == Tile_Type_Road){
            /// On enlève le côté bas à la case au dessus
            map->tiles[((int)building_core_position.y - 1) * map->width + (int)building_core_position.x]->varient -= ROAD_S;
        }
    }
    if (building_core_position.y + 1 < map->height){ /// Si on n'est pas sur le bord bas
        /// Si la case en dessous est une route
        if (map->tiles[((int)building_core_position.y + 1) * map->width + (int)building_core_position.x]->type == Tile_Type_Road){
            /// On enlève le côté haut à la case en dessous
            map->tiles[((int)building_core_position.y + 1) * map->width + (int)building_core_position.x]->varient -= ROAD_N;
        }
    }
}

void destroy_line_of_road(Map_t *map, Vector2 start, Vector2 end, int *money){
    Vector2 current = start;
    Vector2 direction = Vector2Subtract(end, start);
    direction = Vector2Normalize(direction);

    do {
        if(map->tiles[(int)current.y * map->width + (int)current.x]->type == Tile_Type_Road){
            destroy_one_road(map, current);
            *money -= ROAD_PRICE/5;
        }
        current = Vector2Add(current, direction);
    } while (Vector2Distance(current, end) >= 1);
    if(map->tiles[(int)end.y * map->width + (int)end.x]->type == Tile_Type_Road){
        destroy_one_road(map, end);
        *money -= ROAD_PRICE/5;
    }
}

void destroy_roads(Map_t *map, Vector2 mouse_pos_world, Vector2 *first_road_coord, Vector2 *second_road_coord, Vector2 *last_road_coord, int *money){
    /// Si on a cliqué sur la map
    if (IsMouseButtonPressed(Mouse_Button_Left) && is_mouse_on_map(map, mouse_pos_world)) {
        *first_road_coord = mouse_pos_world;
        *second_road_coord = mouse_pos_world;
        *last_road_coord = mouse_pos_world;
    }
        /// Si on garde le clic enfoncé
    else if (IsMouseButtonDown(Mouse_Button_Left) && is_mouse_on_map(map, *first_road_coord)) {
        if (is_vec2D_same(*first_road_coord, *second_road_coord)) {
            *second_road_coord = mouse_pos_world;
        } else if (vec2D_sub(*first_road_coord, *second_road_coord).x) last_road_coord->x = mouse_pos_world.x;
        else last_road_coord->y = mouse_pos_world.y;
    }
        /// Si on relâche le clic
    else if (IsMouseButtonReleased(Mouse_Button_Left) && is_mouse_on_map(map, *first_road_coord)) {
        if (is_mouse_on_map(map, mouse_pos_world) && !is_vec2D_same(*first_road_coord, *last_road_coord)) {
            destroy_line_of_road(map, *first_road_coord, *last_road_coord, money);
        }
        else if (IsMouseButtonReleased(Mouse_Button_Left) && is_vec2D_same(*first_road_coord, *last_road_coord) &&is_vec2D_same(*first_road_coord, *second_road_coord)) {
            if (map->tiles[(int)mouse_pos_world.y * map->width + (int)mouse_pos_world.x]->type == Tile_Type_Road && *money >= ROAD_PRICE/5) {
                destroy_one_road(map, *first_road_coord);
                money -= ROAD_PRICE/5;
            }
        }
    }
}

