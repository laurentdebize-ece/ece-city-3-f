//
// Created by eleuc on 16/11/2022.
//

#include "../../includes/buildings/water_tower.h"

Water_Tower_t *create_water_tower(Vector2 position, BuildingOrientation orientation){
    Water_Tower_t *water_tower = malloc(sizeof(Water_Tower_t));
    water_tower->position = position;
    water_tower->connexite = 0;
    water_tower->water = 0;
    water_tower->houses = NULL;
    water_tower->orientation = orientation;
    return water_tower;
}

void add_water_tower(Map_t *map, Queue_t **water_towers, Vector2 position, BuildingOrientation orientation){
    /// Si la liste est vide
    if(*water_towers == NULL){
        *water_towers = create_queue(create_water_tower(position, orientation));
        (*water_towers)->next = *water_towers;
        (*water_towers)->prev = *water_towers;
    }
    else{
        add_queue(*water_towers, create_water_tower(position, orientation));
    }
    Water_Tower_t *water_tower = (*water_towers)->prev->data;
    switch (orientation){
        case Building_Orientation_S:
            for (int x = 0; x < WATER_TOWER_TILE_WIDTH; ++x) {
                for (int y = 0; y < WATER_TOWER_TILE_HEIGHT; ++y) {
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->type = Tile_Type_Builing;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->varient = Building_Varient_Water_Tower;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->building = water_tower;
                }
            }
            break;
        case Building_Orientation_E:
            for (int x = 0; x < WATER_TOWER_TILE_HEIGHT; ++x) {
                for (int y = 0; y > -WATER_TOWER_TILE_WIDTH; --y) {
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->type = Tile_Type_Builing;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->varient = Building_Varient_Water_Tower;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->building = water_tower;
                }
            }
            break;
        case Building_Orientation_N:
            for (int x = 0; x > -WATER_TOWER_TILE_WIDTH; --x) {
                for (int y = 0; y > -WATER_TOWER_TILE_HEIGHT; --y) {
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->type = Tile_Type_Builing;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->varient = Building_Varient_Water_Tower;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->building = water_tower;
                }
            }
            break;
        case Building_Orientation_W:
            for (int x = 0; x > -WATER_TOWER_TILE_HEIGHT; --x) {
                for (int y = 0; y < WATER_TOWER_TILE_WIDTH; ++y) {
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->type = Tile_Type_Builing;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->varient = Building_Varient_Water_Tower;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->building = water_tower;
                }
            }
            break;
    }
    map->water_tower_count++;
}

void water_tower_update(Queue_t *water_towers, Map_t *map, int *money, int speed);

void water_tower_draw(Queue_t *water_towers, Model *water_tower_mesh){
    if(water_towers != NULL){
        Queue_t *tmp = water_towers;
        do{
            Water_Tower_t *water_tower = tmp->data;
            switch (water_tower->orientation){
                case Building_Orientation_S:
                    DrawCube((Vector3){(water_tower->position.x + WATER_TOWER_TILE_WIDTH*TILES_WIDTH)*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y + WATER_TOWER_TILE_HEIGHT*TILES_WIDTH)*TILES_WIDTH}, WATER_TOWER_CUBE_WIDTH*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT*TILES_WIDTH, WATER_TOWER_CUBE_LENGTH * TILES_WIDTH, BLUE);
                    DrawCubeWires((Vector3){(water_tower->position.x + WATER_TOWER_TILE_WIDTH*TILES_WIDTH)*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y + WATER_TOWER_TILE_HEIGHT*TILES_WIDTH)*TILES_WIDTH}, WATER_TOWER_CUBE_WIDTH*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT*TILES_WIDTH, WATER_TOWER_CUBE_LENGTH * TILES_WIDTH, BLACK);
                    break;
                case Building_Orientation_E:
                    DrawCube((Vector3){(water_tower->position.x + WATER_TOWER_TILE_HEIGHT*TILES_WIDTH)*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y - WATER_TOWER_TILE_WIDTH*TILES_WIDTH + 1)*TILES_WIDTH}, WATER_TOWER_CUBE_LENGTH * TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT * TILES_WIDTH, WATER_TOWER_CUBE_WIDTH * TILES_WIDTH, BLUE);
                    DrawCubeWires((Vector3){(water_tower->position.x + WATER_TOWER_TILE_HEIGHT*TILES_WIDTH)*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y - WATER_TOWER_TILE_WIDTH*TILES_WIDTH + 1)*TILES_WIDTH}, WATER_TOWER_CUBE_LENGTH * TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT * TILES_WIDTH, WATER_TOWER_CUBE_WIDTH * TILES_WIDTH, BLACK);

                    break;
                case Building_Orientation_N:
                    DrawCube((Vector3){(water_tower->position.x - WATER_TOWER_TILE_WIDTH*TILES_WIDTH + 1)*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y - WATER_TOWER_TILE_HEIGHT*TILES_WIDTH + 1)*TILES_WIDTH}, WATER_TOWER_CUBE_WIDTH*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT*TILES_WIDTH, WATER_TOWER_CUBE_LENGTH * TILES_WIDTH, BLUE);
                    DrawCubeWires((Vector3){(water_tower->position.x - WATER_TOWER_TILE_WIDTH*TILES_WIDTH + 1)*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y - WATER_TOWER_TILE_HEIGHT*TILES_WIDTH + 1)*TILES_WIDTH}, WATER_TOWER_CUBE_WIDTH*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT*TILES_WIDTH, WATER_TOWER_CUBE_LENGTH * TILES_WIDTH, BLACK);
                    break;
                case Building_Orientation_W:
                    DrawCube((Vector3){(water_tower->position.x - WATER_TOWER_TILE_HEIGHT*TILES_WIDTH + 1)*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y + WATER_TOWER_TILE_WIDTH*TILES_WIDTH)*TILES_WIDTH}, WATER_TOWER_CUBE_LENGTH * TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT * TILES_WIDTH, WATER_TOWER_CUBE_WIDTH * TILES_WIDTH, BLUE);
                    DrawCubeWires((Vector3){(water_tower->position.x - WATER_TOWER_TILE_HEIGHT*TILES_WIDTH + 1)*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y + WATER_TOWER_TILE_WIDTH*TILES_WIDTH)*TILES_WIDTH}, WATER_TOWER_CUBE_LENGTH * TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT * TILES_WIDTH, WATER_TOWER_CUBE_WIDTH * TILES_WIDTH, BLACK);
                    break;
            }
            tmp = tmp->next;
        }while(tmp != water_towers);
    }
}

void water_tower_destroy_one(Map_t *map, Queue_t **water_towers, Water_Tower_t *water_tower_to_destroy) {
    if((*water_towers)->next == *water_towers){   /// S'il n'y a qu'un seul château d'eau
        water_tower_to_destroy = (*water_towers)->data;
        switch (water_tower_to_destroy->orientation) {
            case Building_Orientation_S:
                for (int y = water_tower_to_destroy->position.y; y <= water_tower_to_destroy->position.y + WATER_TOWER_TILE_HEIGHT-1; ++y) {
                    for (int x = water_tower_to_destroy->position.x; x <= water_tower_to_destroy->position.x + WATER_TOWER_TILE_WIDTH-1; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_E:
                for (int y = water_tower_to_destroy->position.y - WATER_TOWER_TILE_WIDTH+1; y <= water_tower_to_destroy->position.y; ++y) {
                    for (int x = water_tower_to_destroy->position.x; x <= water_tower_to_destroy->position.x + WATER_TOWER_TILE_HEIGHT-1; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_N:
                for (int y = water_tower_to_destroy->position.y - WATER_TOWER_TILE_HEIGHT+1; y <= water_tower_to_destroy->position.y; ++y) {
                    for (int x = water_tower_to_destroy->position.x - WATER_TOWER_TILE_WIDTH+1; x <= water_tower_to_destroy->position.x; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_W:
                for (int y = water_tower_to_destroy->position.y; y <= water_tower_to_destroy->position.y + WATER_TOWER_TILE_WIDTH-1; ++y) {
                    for (int x = water_tower_to_destroy->position.x - WATER_TOWER_TILE_HEIGHT+1; x <= water_tower_to_destroy->position.x; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
        }
        free((*water_towers)->data);
        free(*water_towers);
        *water_towers = NULL;
    }
    else if ((*water_towers)->data == water_tower_to_destroy) { /// Si la maison à démolir est le premier château d'eau de la liste chaînée
        Queue_t *cell_to_destroy = *water_towers;
        (*water_towers)->prev->next = (*water_towers)->next;
        (*water_towers)->next->prev = (*water_towers)->prev;
        (*water_towers) = (*water_towers)->next;
        switch (water_tower_to_destroy->orientation) {
            case Building_Orientation_S:
                for (int y = water_tower_to_destroy->position.y; y <= water_tower_to_destroy->position.y + WATER_TOWER_TILE_HEIGHT-1; ++y) {
                    for (int x = water_tower_to_destroy->position.x; x <= water_tower_to_destroy->position.x + WATER_TOWER_TILE_WIDTH-1; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_E:
                for (int y = water_tower_to_destroy->position.y - WATER_TOWER_TILE_WIDTH+1; y <= water_tower_to_destroy->position.y; ++y) {
                    for (int x = water_tower_to_destroy->position.x; x <= water_tower_to_destroy->position.x + WATER_TOWER_TILE_HEIGHT-1; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_N:
                for (int y = water_tower_to_destroy->position.y - WATER_TOWER_TILE_HEIGHT+1; y <= water_tower_to_destroy->position.y; ++y) {
                    for (int x = water_tower_to_destroy->position.x - WATER_TOWER_TILE_WIDTH+1; x <= water_tower_to_destroy->position.x; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_W:
                for (int y = water_tower_to_destroy->position.y; y <= water_tower_to_destroy->position.y + WATER_TOWER_TILE_WIDTH-1; ++y) {
                    for (int x = water_tower_to_destroy->position.x - WATER_TOWER_TILE_HEIGHT+1; x <= water_tower_to_destroy->position.x; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
        }
        free(water_tower_to_destroy);
        free(cell_to_destroy);
        water_tower_to_destroy = NULL;
    }
    else{   /// Sinon

        Queue_t *cell_to_destroy = (*water_towers)->next;
        while(cell_to_destroy->data != water_tower_to_destroy)
            cell_to_destroy = cell_to_destroy->next;
        cell_to_destroy->prev->next = cell_to_destroy->next;
        cell_to_destroy->next->prev = cell_to_destroy->prev;

        switch (water_tower_to_destroy->orientation) {
            case Building_Orientation_S:
                for (int y = water_tower_to_destroy->position.y; y <= water_tower_to_destroy->position.y + WATER_TOWER_TILE_HEIGHT-1; ++y) {
                    for (int x = water_tower_to_destroy->position.x; x <= water_tower_to_destroy->position.x + WATER_TOWER_TILE_WIDTH-1; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_E:
                for (int y = water_tower_to_destroy->position.y - WATER_TOWER_TILE_WIDTH+1; y <= water_tower_to_destroy->position.y; ++y) {
                    for (int x = water_tower_to_destroy->position.x; x <= water_tower_to_destroy->position.x + WATER_TOWER_TILE_HEIGHT-1; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_N:
                for (int y = water_tower_to_destroy->position.y - WATER_TOWER_TILE_HEIGHT+1; y <= water_tower_to_destroy->position.y; ++y) {
                    for (int x = water_tower_to_destroy->position.x - WATER_TOWER_TILE_WIDTH+1; x <= water_tower_to_destroy->position.x; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_W:
                for (int y = water_tower_to_destroy->position.y; y <= water_tower_to_destroy->position.y + WATER_TOWER_TILE_WIDTH-1; ++y) {
                    for (int x = water_tower_to_destroy->position.x - WATER_TOWER_TILE_HEIGHT+1; x <= water_tower_to_destroy->position.x; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
        }
        free(water_tower_to_destroy);
        free(cell_to_destroy);
        water_tower_to_destroy = NULL;
    }
    map->water_tower_count--;
}

void water_tower_destroy(Queue_t **water_towers){
    if(*water_towers != NULL){
        Queue_t *tmp = *water_towers;
        do{
            Water_Tower_t *water_tower = tmp->data;
            free(water_tower);
            tmp = tmp->next;
        }while(tmp != *water_towers);
        free_queue(water_towers);
    }
}

void draw_transparent_water_tower(Map_t *map, Vector2 mouse_pos_world, int money, BuildingOrientation orientation, Model *water_tower_mesh){
    switch (orientation){
        case Building_Orientation_S:
            DrawCube((Vector3){(mouse_pos_world.x + WATER_TOWER_TILE_WIDTH*TILES_WIDTH)*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT/2.0f*TILES_WIDTH, (mouse_pos_world.y + WATER_TOWER_TILE_HEIGHT*TILES_WIDTH)*TILES_WIDTH}, WATER_TOWER_CUBE_WIDTH*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT*TILES_WIDTH, WATER_TOWER_CUBE_LENGTH*TILES_WIDTH, (is_possible_to_build(map, mouse_pos_world, Tile_Type_Builing, money, orientation)) ? GREEN : RED);
            break;
        case Building_Orientation_E:
            DrawCube((Vector3){(mouse_pos_world.x + WATER_TOWER_TILE_HEIGHT*TILES_WIDTH)*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT/2.0f*TILES_WIDTH, (mouse_pos_world.y - WATER_TOWER_TILE_WIDTH*TILES_WIDTH + 1)*TILES_WIDTH}, WATER_TOWER_CUBE_LENGTH*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT * TILES_WIDTH, WATER_TOWER_CUBE_WIDTH*TILES_WIDTH, (is_possible_to_build(map, mouse_pos_world, Tile_Type_Builing, money, orientation)) ? GREEN : RED);
            break;
        case Building_Orientation_N:
            DrawCube((Vector3){(mouse_pos_world.x - WATER_TOWER_TILE_WIDTH*TILES_WIDTH + 1)*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT/2.0f*TILES_WIDTH, (mouse_pos_world.y - WATER_TOWER_TILE_HEIGHT*TILES_WIDTH + 1)*TILES_WIDTH}, WATER_TOWER_CUBE_WIDTH*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT*TILES_WIDTH, WATER_TOWER_CUBE_LENGTH*TILES_WIDTH, (is_possible_to_build(map, mouse_pos_world, Tile_Type_Builing, money, orientation)) ? GREEN : RED);
            break;
        case Building_Orientation_W:
            DrawCube((Vector3){(mouse_pos_world.x - WATER_TOWER_TILE_HEIGHT*TILES_WIDTH + 1)*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT/2.0f*TILES_WIDTH, (mouse_pos_world.y + WATER_TOWER_TILE_WIDTH*TILES_WIDTH)*TILES_WIDTH}, WATER_TOWER_CUBE_LENGTH*TILES_WIDTH, WATER_TOWER_CUBE_HEIGHT * TILES_WIDTH, WATER_TOWER_CUBE_WIDTH*TILES_WIDTH, (is_possible_to_build(map, mouse_pos_world, Tile_Type_Builing, money, orientation)) ? GREEN : RED);
            break;
    }
}