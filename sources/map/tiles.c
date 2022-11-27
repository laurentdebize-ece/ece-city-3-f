//
// Created by eleuc on 26/10/2022.
//

#include "../../includes/map/tiles.h"

Tile_t tile_init_default(void) {
    Tile_t tile;
    tile.type = 0;
    tile.varient = 0;
    tile.distance = 0;
    tile.building = 0;
    tile.connexite = 0;
    tile.water = 0;
    tile.electricity = 0;
    return tile;
}