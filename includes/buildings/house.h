//
// Created by eleuc on 01/11/2022.
//

#ifndef PROJET_HOUSE_H
#define PROJET_HOUSE_H

#include <stdlib.h>
#include <raylib.h>
#include "../basics/interface utilisateur.h"
#include "../map/map_draw.h"

#define HOUSE_TILE_WIDTH (3*TILES_WIDTH)
#define HOUSE_TILE_HEIGHT (3*TILES_WIDTH)
#define HOUSE_CUBE_WIDTH (2*TILES_WIDTH)
#define HOUSE_LEVEL_UPDATE (3*FPS)
#define TAX_PER_PERSON 10

typedef struct Centrale_Electrique_t Centrale_Electrique_t;
typedef struct Chateau_D_Eau_t Chateau_D_Eau_t;

typedef struct House_t {
    Vector2 position;
    Model buildings[4];
    BoundingBox bounds[4];

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

void house_update(House_t *house, Map_t *map, int *money);

void house_draw(House_t *house);

void house_destroy(House_t **house);

#endif //PROJET_HOUSE_H
