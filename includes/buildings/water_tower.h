//
// Created by eleuc on 16/11/2022.
//

#ifndef PROJET_WATER_TOWER_H
#define PROJET_WATER_TOWER_H

#include <stdlib.h>
#include <raylib.h>
#include "../basics/interface utilisateur.h"
#include "../basics/queue_file.h"
#include "build.h"

#define WATER_TOWER_TILE_WIDTH 6
#define WATER_TOWER_TILE_HEIGHT 4
#define WATER_TOWER_CUBE_WIDTH 5
#define WATER_TOWER_CUBE_LENGTH 3
#define WATER_TOWER_CUBE_HEIGHT 3
#define WATER_TOWER_WATER_FOR_CABANE 10
#define WATER_TOWER_WATER_FOR_MAISON 50
#define WATER_TOWER_WATER_FOR_IMMEUBLE 100
#define WATER_TOWER_WATER_FOR_GRATTES_CIEL 1000
#define WATER_TOWER_CAPACITY 5000

typedef struct Water_Tower_t {
    Vector2 position;
    int connexite;
    int water;
    Queue_t *houses;
    BuildingOrientation orientation;
}Water_Tower_t;

Water_Tower_t *create_water_tower(Vector2 position, BuildingOrientation orientation);

void find_water_tower_connexity(Map_t *map, Water_Tower_t *water_tower);

void find_all_water_towers_connexity(Map_t *map, Queue_t *water_towers);

void reset_all_water_towers_connexity(Queue_t *water_tower);

void add_water_tower(Map_t *map, Queue_t **water_towers, Vector2 position, BuildingOrientation orientation);

void water_tower_update(Queue_t *water_towers, Map_t *map, int *money, int speed);

void water_tower_draw(Queue_t *power_plants, Model *water_tower_mesh);

void water_tower_destroy_one(Map_t *map, Queue_t **water_towers, Water_Tower_t *water_tower_to_destroy);

void water_tower_destroy(Queue_t **power_plants);

void draw_transparent_water_tower(Map_t *map, Vector2 mouse_pos_world, int money, BuildingOrientation orientation, Model *water_tower_mesh);

#endif //PROJET_WATER_TOWER_H
