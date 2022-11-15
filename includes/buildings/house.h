//
// Created by eleuc on 01/11/2022.
//

#ifndef PROJET_HOUSE_H
#define PROJET_HOUSE_H

#include <stdlib.h>
#include <raylib.h>
#include "../basics/interface utilisateur.h"
#include "build.h"

#define HOUSE_TILE_WIDTH (3*TILES_WIDTH)
#define HOUSE_TILE_HEIGHT (3*TILES_WIDTH)
#define HOUSE_CUBE_WIDTH (2*TILES_WIDTH)
#define HOUSE_LEVEL_UPDATE (15*FPS)
#define TAX_PER_PERSON 10

typedef struct Centrale_Electrique_t Centrale_Electrique_t;
typedef struct Chateau_D_Eau_t Chateau_D_Eau_t;

typedef struct House_t {
    Vector2 position;
    int level;
    int counter;
    int electricity, water;
    struct House_t *next;
    struct House_t *prev;
    struct Chateau_D_Eau_t *chateau_d_eau;
    struct Centrale_Electrique_t *centrale_electrique;
}House_t;

House_t *create_house(Vector2 position);

void add_house(Map_t *map, House_t **house, Vector2 position);

void house_update(House_t *house, Map_t *map, int *money, int speed);

void house_draw(House_t *house);

void house_destroy_one(Map_t *map, House_t **houses, House_t *house_to_destroy);

void house_destroy(House_t **house);

void draw_transparent_house(Map_t *map, Vector2 mouse_pos_world, int money);

#endif //PROJET_HOUSE_H
