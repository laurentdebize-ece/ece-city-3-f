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

#define DECALAGE_MAP_X (TILES_WIDTH/2.0f)
#define DECALAGE_MAP_Y 0.0f
#define DECALAGE_MAP_Z (TILES_WIDTH/2.0f)

void map_draw(Map_t *map, Texture2D road_texture, float tile_size, int vew_mode);

_Bool is_mouse_on_map(Map_t *map, Vector2 mouse_pos_world);

#endif //PROJET_MAP_DRAW_H
