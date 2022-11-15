//
// Created by eleuc on 31/10/2022.
//

#ifndef PROJET_MAP_H
#define PROJET_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "tiles.h"

#define DEFAULT_MAP_FILE_PATH "../assets/map/default_map.txt"

typedef struct {
    /// Largeur de la map
    int width;
    /// Hauteur de la map
    int height;
    /// Nombre de maisons
    int house_count;
    /// Tableau de pointeurs de Tile_t (tuiles)
    Tile_t **tiles;
} Map_t;

Map_t *map_create(int width, int height);

Map_t *load_map(const char *path);

void print_map_console(Map_t* map);

void map_destroy(Map_t **map);

#endif //PROJET_MAP_H
