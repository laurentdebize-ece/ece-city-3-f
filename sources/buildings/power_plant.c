//
// Created by eleuc on 19/11/2022.
//

#include "../../includes/buildings/power_plant.h"

Power_Plant_t *create_power_plant(Vector2 position, BuildingOrientation orientation) {
    Power_Plant_t *power_plant = malloc(sizeof(Power_Plant_t));
    power_plant->position = position;
    power_plant->connexite = 0;
    power_plant->power = 0;
    power_plant->houses = NULL;
    power_plant->orientation = orientation;
    return power_plant;
}

void add_power_plant(Map_t *map, Queue_t **power_plants, Vector2 position, BuildingOrientation orientation){

    add_queue(power_plants, create_power_plant(position, orientation));
    Power_Plant_t *water_tower = (*power_plants)->prev->data;
    switch (orientation){
        case Building_Orientation_S:
            for (int x = 0; x < POWER_PLANT_TILE_WIDTH; ++x) {
                for (int y = 0; y < POWER_PLANT_TILE_HEIGHT; ++y) {
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->type = Tile_Type_Builing;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->varient = Building_Varient_Power_Plant;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->building = water_tower;
                }
            }
            break;
        case Building_Orientation_E:
            for (int x = 0; x < POWER_PLANT_TILE_HEIGHT; ++x) {
                for (int y = 0; y > -POWER_PLANT_TILE_WIDTH; --y) {
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->type = Tile_Type_Builing;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->varient = Building_Varient_Power_Plant;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->building = water_tower;
                }
            }
            break;
        case Building_Orientation_N:
            for (int x = 0; x > -POWER_PLANT_TILE_WIDTH; --x) {
                for (int y = 0; y > -POWER_PLANT_TILE_HEIGHT; --y) {
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->type = Tile_Type_Builing;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->varient = Building_Varient_Power_Plant;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->building = water_tower;
                }
            }
            break;
        case Building_Orientation_W:
            for (int x = 0; x > -POWER_PLANT_TILE_HEIGHT; --x) {
                for (int y = 0; y < POWER_PLANT_TILE_WIDTH; ++y) {
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->type = Tile_Type_Builing;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->varient = Building_Varient_Power_Plant;
                    map->tiles[(int)(position.y+y)*map->width + (int)position.x+x]->building = water_tower;
                }
            }
            break;
    }
    map->power_plant_count++;
}

void power_plant_draw(Queue_t *power_plants, Model *water_tower_mesh){
    if(power_plants != NULL){
        Queue_t *tmp = power_plants;
        do{
            Power_Plant_t *water_tower = tmp->data;
            switch (water_tower->orientation){
                case Building_Orientation_S:
                    DrawCube((Vector3){(water_tower->position.x + POWER_PLANT_TILE_WIDTH*TILES_WIDTH)*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y + POWER_PLANT_TILE_HEIGHT*TILES_WIDTH)*TILES_WIDTH}, POWER_PLANT_CUBE_WIDTH*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT*TILES_WIDTH, POWER_PLANT_CUBE_LENGTH * TILES_WIDTH, YELLOW);
                    DrawCubeWires((Vector3){(water_tower->position.x + POWER_PLANT_TILE_WIDTH*TILES_WIDTH)*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y + POWER_PLANT_TILE_HEIGHT*TILES_WIDTH)*TILES_WIDTH}, POWER_PLANT_CUBE_WIDTH*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT*TILES_WIDTH, POWER_PLANT_CUBE_LENGTH * TILES_WIDTH, BLACK);
                    break;
                case Building_Orientation_E:
                    DrawCube((Vector3){(water_tower->position.x + POWER_PLANT_TILE_HEIGHT*TILES_WIDTH)*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y - POWER_PLANT_TILE_WIDTH*TILES_WIDTH + 1)*TILES_WIDTH}, POWER_PLANT_CUBE_LENGTH * TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT * TILES_WIDTH, POWER_PLANT_CUBE_WIDTH * TILES_WIDTH, YELLOW);
                    DrawCubeWires((Vector3){(water_tower->position.x + POWER_PLANT_TILE_HEIGHT*TILES_WIDTH)*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y - POWER_PLANT_TILE_WIDTH*TILES_WIDTH + 1)*TILES_WIDTH}, POWER_PLANT_CUBE_LENGTH * TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT * TILES_WIDTH, POWER_PLANT_CUBE_WIDTH * TILES_WIDTH, BLACK);

                    break;
                case Building_Orientation_N:
                    DrawCube((Vector3){(water_tower->position.x - POWER_PLANT_TILE_WIDTH*TILES_WIDTH + 1)*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y - POWER_PLANT_TILE_HEIGHT*TILES_WIDTH + 1)*TILES_WIDTH}, POWER_PLANT_CUBE_WIDTH*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT*TILES_WIDTH, POWER_PLANT_CUBE_LENGTH * TILES_WIDTH, YELLOW);
                    DrawCubeWires((Vector3){(water_tower->position.x - POWER_PLANT_TILE_WIDTH*TILES_WIDTH + 1)*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y - POWER_PLANT_TILE_HEIGHT*TILES_WIDTH + 1)*TILES_WIDTH}, POWER_PLANT_CUBE_WIDTH*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT*TILES_WIDTH, POWER_PLANT_CUBE_LENGTH * TILES_WIDTH, BLACK);
                    break;
                case Building_Orientation_W:
                    DrawCube((Vector3){(water_tower->position.x - POWER_PLANT_TILE_HEIGHT*TILES_WIDTH + 1)*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y + POWER_PLANT_TILE_WIDTH*TILES_WIDTH)*TILES_WIDTH}, POWER_PLANT_CUBE_LENGTH * TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT * TILES_WIDTH, POWER_PLANT_CUBE_WIDTH * TILES_WIDTH, YELLOW);
                    DrawCubeWires((Vector3){(water_tower->position.x - POWER_PLANT_TILE_HEIGHT*TILES_WIDTH + 1)*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT/2.0f*TILES_WIDTH, (water_tower->position.y + POWER_PLANT_TILE_WIDTH*TILES_WIDTH)*TILES_WIDTH}, POWER_PLANT_CUBE_LENGTH * TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT * TILES_WIDTH, POWER_PLANT_CUBE_WIDTH * TILES_WIDTH, BLACK);
                    break;
            }
            tmp = tmp->next;
        }while(tmp != power_plants);
    }
}

void power_plant_destroy_one(Map_t *map, Queue_t **power_plants, Power_Plant_t *power_plant_to_destroy) {
    if((*power_plants)->next == *power_plants){   /// S'il n'y a qu'une seule centrale électrique
        power_plant_to_destroy = (*power_plants)->data;
        switch (power_plant_to_destroy->orientation) {
            case Building_Orientation_S:
                for (int y = power_plant_to_destroy->position.y; y <= power_plant_to_destroy->position.y + POWER_PLANT_TILE_HEIGHT - 1; ++y) {
                    for (int x = power_plant_to_destroy->position.x; x <= power_plant_to_destroy->position.x + POWER_PLANT_TILE_WIDTH - 1; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_E:
                for (int y = power_plant_to_destroy->position.y - POWER_PLANT_TILE_WIDTH + 1; y <= power_plant_to_destroy->position.y; ++y) {
                    for (int x = power_plant_to_destroy->position.x; x <= power_plant_to_destroy->position.x + POWER_PLANT_TILE_HEIGHT - 1; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_N:
                for (int y = power_plant_to_destroy->position.y - POWER_PLANT_TILE_HEIGHT + 1; y <= power_plant_to_destroy->position.y; ++y) {
                    for (int x = power_plant_to_destroy->position.x - POWER_PLANT_TILE_WIDTH + 1; x <= power_plant_to_destroy->position.x; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_W:
                for (int y = power_plant_to_destroy->position.y; y <= power_plant_to_destroy->position.y + POWER_PLANT_TILE_WIDTH - 1; ++y) {
                    for (int x = power_plant_to_destroy->position.x - POWER_PLANT_TILE_HEIGHT + 1; x <= power_plant_to_destroy->position.x; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
        }
        free((*power_plants)->data);
        free(*power_plants);
        *power_plants = NULL;
    }
    else if ((*power_plants)->data == power_plant_to_destroy) { /// Si la maison à démolir est la première centrale électrique de la liste chaînée
        Queue_t *cell_to_destroy = *power_plants;
        (*power_plants)->prev->next = (*power_plants)->next;
        (*power_plants)->next->prev = (*power_plants)->prev;
        (*power_plants) = (*power_plants)->next;
        switch (power_plant_to_destroy->orientation) {
            case Building_Orientation_S:
                for (int y = power_plant_to_destroy->position.y; y <= power_plant_to_destroy->position.y + POWER_PLANT_TILE_HEIGHT - 1; ++y) {
                    for (int x = power_plant_to_destroy->position.x; x <= power_plant_to_destroy->position.x + POWER_PLANT_TILE_WIDTH - 1; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_E:
                for (int y = power_plant_to_destroy->position.y - POWER_PLANT_TILE_WIDTH + 1; y <= power_plant_to_destroy->position.y; ++y) {
                    for (int x = power_plant_to_destroy->position.x; x <= power_plant_to_destroy->position.x + POWER_PLANT_TILE_HEIGHT - 1; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_N:
                for (int y = power_plant_to_destroy->position.y - POWER_PLANT_TILE_HEIGHT + 1; y <= power_plant_to_destroy->position.y; ++y) {
                    for (int x = power_plant_to_destroy->position.x - POWER_PLANT_TILE_WIDTH + 1; x <= power_plant_to_destroy->position.x; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_W:
                for (int y = power_plant_to_destroy->position.y; y <= power_plant_to_destroy->position.y + POWER_PLANT_TILE_WIDTH - 1; ++y) {
                    for (int x = power_plant_to_destroy->position.x - POWER_PLANT_TILE_HEIGHT + 1; x <= power_plant_to_destroy->position.x; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
        }
        free(power_plant_to_destroy);
        free(cell_to_destroy);
        power_plant_to_destroy = NULL;
    }
    else{   /// Sinon

        Queue_t *cell_to_destroy = (*power_plants)->next;
        while(cell_to_destroy->data != power_plant_to_destroy)
            cell_to_destroy = cell_to_destroy->next;
        cell_to_destroy->prev->next = cell_to_destroy->next;
        cell_to_destroy->next->prev = cell_to_destroy->prev;

        switch (power_plant_to_destroy->orientation) {
            case Building_Orientation_S:
                for (int y = power_plant_to_destroy->position.y; y <= power_plant_to_destroy->position.y + POWER_PLANT_TILE_HEIGHT - 1; ++y) {
                    for (int x = power_plant_to_destroy->position.x; x <= power_plant_to_destroy->position.x + POWER_PLANT_TILE_WIDTH - 1; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_E:
                for (int y = power_plant_to_destroy->position.y - POWER_PLANT_TILE_WIDTH + 1; y <= power_plant_to_destroy->position.y; ++y) {
                    for (int x = power_plant_to_destroy->position.x; x <= power_plant_to_destroy->position.x + POWER_PLANT_TILE_HEIGHT - 1; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_N:
                for (int y = power_plant_to_destroy->position.y - POWER_PLANT_TILE_HEIGHT + 1; y <= power_plant_to_destroy->position.y; ++y) {
                    for (int x = power_plant_to_destroy->position.x - POWER_PLANT_TILE_WIDTH + 1; x <= power_plant_to_destroy->position.x; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
            case Building_Orientation_W:
                for (int y = power_plant_to_destroy->position.y; y <= power_plant_to_destroy->position.y + POWER_PLANT_TILE_WIDTH - 1; ++y) {
                    for (int x = power_plant_to_destroy->position.x - POWER_PLANT_TILE_HEIGHT + 1; x <= power_plant_to_destroy->position.x; ++x) {
                        map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                        map->tiles[y*map->width+x]->connexite = 0;
                        map->tiles[y*map->width+x]->building = NULL;
                        map->tiles[y*map->width+x]->varient = 0;
                    }
                }
                break;
        }
        free(power_plant_to_destroy);
        free(cell_to_destroy);
        power_plant_to_destroy = NULL;
    }
    map->power_plant_count--;
}

void power_plant_destroy(Queue_t **power_plants){
    if(*power_plants != NULL){
        Queue_t *tmp = *power_plants;
        do{
            Power_Plant_t *power_plant = tmp->data;
            free(power_plant);
            tmp = tmp->next;
        }while(tmp != *power_plants);
        free_queue(power_plants);
    }
}

void draw_transparent_power_plant(Map_t *map, Vector2 mouse_pos_world, int money, BuildingOrientation orientation, Model *water_tower_mesh){
    switch (orientation){
        case Building_Orientation_S:
            DrawCube((Vector3){(mouse_pos_world.x + POWER_PLANT_TILE_WIDTH*TILES_WIDTH)*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT/2.0f*TILES_WIDTH, (mouse_pos_world.y + POWER_PLANT_TILE_HEIGHT*TILES_WIDTH)*TILES_WIDTH}, POWER_PLANT_CUBE_WIDTH*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT*TILES_WIDTH, POWER_PLANT_CUBE_LENGTH*TILES_WIDTH, (is_possible_to_build(map, mouse_pos_world, Tile_Type_Builing, money, orientation)) ? GREEN : RED);
            break;
        case Building_Orientation_E:
            DrawCube((Vector3){(mouse_pos_world.x + POWER_PLANT_TILE_HEIGHT*TILES_WIDTH)*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT/2.0f*TILES_WIDTH, (mouse_pos_world.y - POWER_PLANT_TILE_WIDTH*TILES_WIDTH + 1)*TILES_WIDTH}, POWER_PLANT_CUBE_LENGTH*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT * TILES_WIDTH, POWER_PLANT_CUBE_WIDTH*TILES_WIDTH, (is_possible_to_build(map, mouse_pos_world, Tile_Type_Builing, money, orientation)) ? GREEN : RED);
            break;
        case Building_Orientation_N:
            DrawCube((Vector3){(mouse_pos_world.x - POWER_PLANT_TILE_WIDTH*TILES_WIDTH + 1)*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT/2.0f*TILES_WIDTH, (mouse_pos_world.y - POWER_PLANT_TILE_HEIGHT*TILES_WIDTH + 1)*TILES_WIDTH}, POWER_PLANT_CUBE_WIDTH*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT*TILES_WIDTH, POWER_PLANT_CUBE_LENGTH*TILES_WIDTH, (is_possible_to_build(map, mouse_pos_world, Tile_Type_Builing, money, orientation)) ? GREEN : RED);
            break;
        case Building_Orientation_W:
            DrawCube((Vector3){(mouse_pos_world.x - POWER_PLANT_TILE_HEIGHT*TILES_WIDTH + 1)*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT/2.0f*TILES_WIDTH, (mouse_pos_world.y + POWER_PLANT_TILE_WIDTH*TILES_WIDTH)*TILES_WIDTH}, POWER_PLANT_CUBE_LENGTH*TILES_WIDTH, POWER_PLANT_CUBE_HEIGHT * TILES_WIDTH, POWER_PLANT_CUBE_WIDTH*TILES_WIDTH, (is_possible_to_build(map, mouse_pos_world, Tile_Type_Builing, money, orientation)) ? GREEN : RED);
            break;
    }
}