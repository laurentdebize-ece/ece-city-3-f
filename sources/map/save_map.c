//
// Created by eleuc on 15/11/2022.
//

#include "../../includes/map/save_map.h"

void save_map(Map_t *map, House_t *house, Time_t *time, int money, char *path) {

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
        House_t *current_house = house;
        do{
            fprintf(file, "%f %f %d %d\n", current_house->position.x, current_house->position.y, current_house->level, current_house->counter);
            current_house = current_house->next;
        }while (current_house != house);
    }

    fclose(file);
}

void load_saved_map(Map_t **map, House_t **house, Time_t *time, int *money, char *path) {
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
            if (*house == 0){
                *house = malloc(sizeof(House_t));
                (*house)->next = *house;
                (*house)->prev = *house;

            } else {
                House_t *new_house = malloc(sizeof(House_t));
                new_house->next = *house;
                new_house->prev = (*house)->prev;
                (*house)->prev->next = new_house;
                (*house)->prev = new_house;
            }
            fscanf(file, "%f %f %d %d\n", &(*house)->prev->position.x, &(*house)->prev->position.y, &(*house)->prev->level, &(*house)->prev->counter);
            for (int y = (*house)->prev->position.y - 1; y <= (*house)->prev->position.y + 1; ++y) {
                for (int x = (*house)->prev->position.x - 1; x <= (*house)->prev->position.x + 1; ++x) {
                    (*map)->tiles[y*(*map)->width+x]->building = (*house)->prev;
                }
            }
        }
    }
    fclose(file);
}