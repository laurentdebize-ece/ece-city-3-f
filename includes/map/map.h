//
// Created by eleuc on 31/10/2022.
//

#ifndef PROJET_MAP_H
#define PROJET_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "tiles.h"

#define MAP_WIDTH 40
#define MAP_HEIGHT 40
#define MAP_SIZE MAP_WIDTH * MAP_HEIGHT
#define MAP_FILE_PATH "../map.txt"

typedef struct {
    int width;
    int height;
    Tile_t **tiles;
} Map_t;

Map_t *map_create(int width, int height);

Map_t *load_map(const char *path);

void print_map_console(Map_t* map);

void map_destroy(Map_t **map);

#endif //PROJET_MAP_H
