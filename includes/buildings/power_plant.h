//
// Created by eleuc on 19/11/2022.
//

#ifndef PROJET_POWER_PLANT_H
#define PROJET_POWER_PLANT_H

#include <stdlib.h>
#include <raylib.h>
#include "../basics/interface utilisateur.h"
#include "../basics/queue_file.h"
#include "build.h"

#define POWER_PLANT_TILE_WIDTH 6
#define POWER_PLANT_TILE_HEIGHT 4
#define POWER_PLANT_CUBE_WIDTH 5
#define POWER_PLANT_CUBE_LENGTH 3
#define POWER_PLANT_CUBE_HEIGHT 3
#define POWER_PLANT_CAPACITY 5000

typedef struct Power_Plant_t {
    Vector2 position;
    int connexite;
    int electrecity;
    Queue_t *houses;
    BuildingOrientation orientation;
}Power_Plant_t;

/// Création d'une centrale électrique

Power_Plant_t *create_power_plant(Vector2 position, BuildingOrientation orientation);

/// Ajout d'une centrale électrique à la map

void add_power_plant(Map_t *map, Queue_t **power_plants, Vector2 position, BuildingOrientation orientation);

/// Mise à jour de la centrale électrique

void power_plant_update(Queue_t *power_plants, Map_t *map, int *money, int speed);

/// Dessin de la centrale électrique

void power_plant_draw(Queue_t *power_plants, Model *power_plant_mesh);

/// Destruction d'une centrale électrique

void power_plant_destroy_one(Map_t *map, Queue_t **power_plants, Power_Plant_t *power_plant_to_destroy);

/// Destruction de toutes les centrales électriques

void power_plant_destroy(Queue_t **power_plants);

/// Dessin de la centrale électrique en transparence

void draw_transparent_power_plant(Map_t *map, Vector2 mouse_pos_world, int money, BuildingOrientation orientation, Model *power_plant_mesh);

#endif //PROJET_POWER_PLANT_H
