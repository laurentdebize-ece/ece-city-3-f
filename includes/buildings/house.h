//
// Created by eleuc on 01/11/2022.
//

#ifndef PROJET_HOUSE_H
#define PROJET_HOUSE_H

#include <stdlib.h>
#include <raymath.h>
#include "../basics/interface utilisateur.h"
#include "../map/map.h"

#define HOUSE_WIDTH 3
#define HOUSE_HEIGHT 3
#define HOUSE_LEVEL_UPDATE (15*FPS)

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

void house_update(House_t *house);

#endif //PROJET_HOUSE_H
