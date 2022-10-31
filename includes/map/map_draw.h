//
// Created by eleuc on 31/10/2022.
//

#ifndef PROJET_MAP_DRAW_H
#define PROJET_MAP_DRAW_H

#include <raylib.h>
#include "../basics/interface utilisateur.h"
#include "../foncftions_affichage.h"
#include "map.h"

#define TILES_WIDTH 2.0f

#define DECALAGE_MAP_X (MAP_WIDTH*TILES_WIDTH/2.0f)
#define DECALAGE_MAP_Y 0.0f
#define DECALAGE_MAP_Z (MAP_HEIGHT*TILES_WIDTH/2.0f)

void map_draw(Map_t *map, float tile_size);

#endif //PROJET_MAP_DRAW_H
