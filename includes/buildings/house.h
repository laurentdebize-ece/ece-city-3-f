//
// Created by eleuc on 01/11/2022.
//

#ifndef PROJET_HOUSE_H
#define PROJET_HOUSE_H

#include <stdlib.h>
#include <raylib.h>
#include "../basics/interface utilisateur.h"
#include "../basics/queue_file.h"
#include "build.h"

#define HOUSE_TILE_WIDTH (3*TILES_WIDTH)
#define HOUSE_TILE_HEIGHT (3*TILES_WIDTH)
#define HOUSE_CUBE_WIDTH (2*TILES_WIDTH)
#define HOUSE_LEVEL_UPDATE (15*FPS)
#define TAX_PER_PERSON 10

typedef struct House_t {
    Vector2 position;
    int connexite;
    int level;
    int counter;
    int electricity, water;
    int distance;
    Queue_t *water_towers;
    Queue_t *power_plants;
    BuildingOrientation orientation;
}House_t;

House_t *create_house(Vector2 position, BuildingOrientation orientation);

void reset_all_houses_connexity(Queue_t *houses);

void find_house_connexity(Map_t *map, House_t *house);

void find_all_houses_connexity(Map_t *map, Queue_t *houses);

void add_house(Map_t *map, Queue_t **houses, Vector2 position, BuildingOrientation orientation);

void house_update(Queue_t *houses, Map_t *map, int *population, int *money, int speed);

void house_draw(Queue_t *houses, Model *house_mesh);

void house_destroy_one(Map_t *map, Queue_t **houses, House_t *house_to_destroy);

void house_destroy(Queue_t **houses);

void draw_transparent_house(Map_t *map, Vector2 mouse_pos_world, int money, BuildingOrientation orientation, Model *house_mesh);

#endif //PROJET_HOUSE_H
