//
// Created by eleuc on 15/11/2022.
//

#include "../../includes/map/save_map.h"

void save_map(Map_t *map, Queue_t *house, Queue_t *water_tower, Queue_t *power_plant, Time_t *time, int money, char *path) {

    /// Ouverture du fichier
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    /// Ecriture de la taille de la map et l'argent
    fprintf(file, "%d %d %d\n", map->width, map->height, money);
    /// Récupération des infos du temps
    fprintf(file, "%d %d %d %d %d %d %d\n", time->years, time->months, time->hours, time->minutes, time->seconds, time->counter, time->speed);

    for (int y = 0; y < map->height; ++y) {
        for (int x = 0; x < map->width; ++x) {
            fprintf(file, "%d ", map->tiles[y*map->width+x]->type);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n\n\n");
    for (int y = 0; y < map->height; ++y) {
        for (int x = 0; x < map->width; ++x) {
            fprintf(file, "%d ", map->tiles[y*map->width+x]->varient);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n\n\n");
    fprintf(file, "%d\n", map->house_count);
    if (map->house_count > 0) {
        Queue_t *current_cell = house;
        do{
            House_t *current_house = current_cell->data;
            fprintf(file, "%f %f %d %d %d\n", current_house->position.x, current_house->position.y, current_house->level, current_house->counter, current_house->orientation);
            current_cell = current_cell->next;
        }while (current_cell != house);
    }
    fprintf(file, "\n\n\n");
    fprintf(file, "%d\n", map->water_tower_count);
    if (map->water_tower_count > 0) {
        Queue_t *current_cell = water_tower;
        do{
            Water_Tower_t *current_water_tower = current_cell->data;
            fprintf(file, "%f %f %d\n", current_water_tower->position.x, current_water_tower->position.y, current_water_tower->orientation);
            current_cell = current_cell->next;
        }while (current_cell != water_tower);
    }
    fprintf(file, "\n\n\n");
    fprintf(file, "%d\n", map->power_plant_count);
    if (map->power_plant_count > 0) {
        Queue_t *current_cell = power_plant;
        do{
            Power_Plant_t *current_power_plant = current_cell->data;
            fprintf(file, "%f %f %d\n", current_power_plant->position.x, current_power_plant->position.y, current_power_plant->orientation);
            current_cell = current_cell->next;
        }while (current_cell != power_plant);
    }
    fclose(file);
}

void load_saved_map(Map_t **map, Queue_t **house, Queue_t **water_tower, Queue_t **power_plant, Time_t *time, int *money, char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    int width, height;
    fscanf(file, "%d %d %d\n", &width, &height, money);
    *map = map_create(width, height);
    fscanf(file, "%d %d %d %d %d %d %d\n", &time->years, &time->months, &time->hours, &time->minutes, &time->seconds, &time->counter, &time->speed);
    for (int y = 0; y < (*map)->height; ++y) {
        for (int x = 0; x < (*map)->width; ++x) {
            fscanf(file, "%d ", &(*map)->tiles[y*(*map)->width+x]->type);
        }
    }
    for (int y = 0; y < (*map)->height; ++y) {
        for (int x = 0; x < (*map)->width; ++x) {
            fscanf(file, "%d ", &(*map)->tiles[y*(*map)->width+x]->varient);
        }
    }
    fscanf(file, "%d\n", &(*map)->house_count);
    if ((*map)->house_count > 0) {
        for (int i = 0; i < (*map)->house_count; ++i) {
            if (!*house){
                *house = create_queue(malloc(sizeof(House_t)));
                (*house)->next = *house;
                (*house)->prev = *house;

            } else {
                Queue_t *new_house = create_queue(malloc(sizeof(House_t)));
                new_house->next = *house;
                new_house->prev = (*house)->prev;
                (*house)->prev->next = new_house;
                (*house)->prev = new_house;
            }
            House_t *last_house_created = (*house)->prev->data;
            fscanf(file, "%f %f %d %d %d\n", &last_house_created->position.x, &last_house_created->position.y, &last_house_created->level, &last_house_created->counter, &last_house_created->orientation);
            for (int y = last_house_created->position.y - 1; y <= last_house_created->position.y + 1; ++y) {
                for (int x = last_house_created->position.x - 1; x <= last_house_created->position.x + 1; ++x) {
                    (*map)->tiles[y*(*map)->width+x]->building = last_house_created;
                }
            }
        }
    }
    fscanf(file, "%d\n", &(*map)->water_tower_count);
    if ((*map)->water_tower_count > 0) {
        for (int i = 0; i < (*map)->water_tower_count; ++i) {
            if (!*water_tower){
                *water_tower = create_queue(malloc(sizeof(Water_Tower_t)));
                (*water_tower)->next = *water_tower;
                (*water_tower)->prev = *water_tower;

            } else {
                Queue_t *new_water_tower = create_queue(malloc(sizeof(Water_Tower_t)));
                new_water_tower->next = *water_tower;
                new_water_tower->prev = (*water_tower)->prev;
                (*water_tower)->prev->next = new_water_tower;
                (*water_tower)->prev = new_water_tower;
            }
            Water_Tower_t *last_water_tower_created = (*water_tower)->prev->data;
            fscanf(file, "%f %f %d\n", &last_water_tower_created->position.x, &last_water_tower_created->position.y, &last_water_tower_created->orientation);
            switch (last_water_tower_created->orientation) {
                case Building_Orientation_S:
                    for (int y = last_water_tower_created->position.y; y < last_water_tower_created->position.y + WATER_TOWER_TILE_HEIGHT; ++y) {
                        for (int x = last_water_tower_created->position.x; x < last_water_tower_created->position.x + WATER_TOWER_TILE_WIDTH; ++x) {
                            (*map)->tiles[y*(*map)->width+x]->building = last_water_tower_created;
                        }
                    }
                    break;
                case Building_Orientation_E:
                    for (int y = last_water_tower_created->position.y - WATER_TOWER_TILE_WIDTH + 1; y <= last_water_tower_created->position.y; ++y) {
                        for (int x = last_water_tower_created->position.x; x < last_water_tower_created->position.x + WATER_TOWER_TILE_HEIGHT; ++x) {
                            (*map)->tiles[y*(*map)->width+x]->building = last_water_tower_created;
                        }
                    }
                    break;
                case Building_Orientation_N:
                    for (int y = last_water_tower_created->position.y - WATER_TOWER_TILE_HEIGHT + 1; y <= last_water_tower_created->position.y; ++y) {
                        for (int x = last_water_tower_created->position.x - WATER_TOWER_TILE_WIDTH + 1; x <= last_water_tower_created->position.x; ++x) {
                            (*map)->tiles[y*(*map)->width+x]->building = last_water_tower_created;
                        }
                    }
                    break;
                case Building_Orientation_W:
                    for (int y = last_water_tower_created->position.y; y < last_water_tower_created->position.y + WATER_TOWER_TILE_WIDTH; ++y) {
                        for (int x = last_water_tower_created->position.x - WATER_TOWER_TILE_HEIGHT + 1; x <= last_water_tower_created->position.x; ++x) {
                            (*map)->tiles[y*(*map)->width+x]->building = last_water_tower_created;
                        }
                    }
                    break;
            }
        }
    }
    fscanf(file, "%d\n", &(*map)->power_plant_count);
    if ((*map)->power_plant_count > 0) {
        for (int i = 0; i < (*map)->power_plant_count; ++i) {
            if (!*power_plant){
                *power_plant = create_queue(malloc(sizeof(Power_Plant_t)));
                (*power_plant)->next = *power_plant;
                (*power_plant)->prev = *power_plant;

            } else {
                Queue_t *new_power_plant = create_queue(malloc(sizeof(Power_Plant_t)));
                new_power_plant->next = *power_plant;
                new_power_plant->prev = (*power_plant)->prev;
                (*power_plant)->prev->next = new_power_plant;
                (*power_plant)->prev = new_power_plant;
            }
            Power_Plant_t *last_power_plant_created = (*power_plant)->prev->data;
            fscanf(file, "%f %f %d\n", &last_power_plant_created->position.x, &last_power_plant_created->position.y, &last_power_plant_created->orientation);
            switch (last_power_plant_created->orientation) {
                case Building_Orientation_S:
                    for (int y = last_power_plant_created->position.y; y < last_power_plant_created->position.y + POWER_PLANT_TILE_HEIGHT; ++y) {
                        for (int x = last_power_plant_created->position.x; x < last_power_plant_created->position.x + POWER_PLANT_TILE_WIDTH; ++x) {
                            (*map)->tiles[y*(*map)->width+x]->building = last_power_plant_created;
                        }
                    }
                    break;
                case Building_Orientation_E:
                    for (int y = last_power_plant_created->position.y - POWER_PLANT_TILE_WIDTH + 1; y <= last_power_plant_created->position.y; ++y) {
                        for (int x = last_power_plant_created->position.x; x < last_power_plant_created->position.x + POWER_PLANT_TILE_HEIGHT; ++x) {
                            (*map)->tiles[y*(*map)->width+x]->building = last_power_plant_created;
                        }
                    }
                    break;
                case Building_Orientation_N:
                    for (int y = last_power_plant_created->position.y - POWER_PLANT_TILE_HEIGHT + 1; y <= last_power_plant_created->position.y; ++y) {
                        for (int x = last_power_plant_created->position.x - POWER_PLANT_TILE_WIDTH + 1; x <= last_power_plant_created->position.x; ++x) {
                            (*map)->tiles[y*(*map)->width+x]->building = last_power_plant_created;
                        }
                    }
                    break;
                case Building_Orientation_W:
                    for (int y = last_power_plant_created->position.y; y < last_power_plant_created->position.y + POWER_PLANT_TILE_WIDTH; ++y) {
                        for (int x = last_power_plant_created->position.x - POWER_PLANT_TILE_HEIGHT + 1; x <= last_power_plant_created->position.x; ++x) {
                            (*map)->tiles[y*(*map)->width+x]->building = last_power_plant_created;
                        }
                    }
                    break;
            }
        }
    }
    fclose(file);
}