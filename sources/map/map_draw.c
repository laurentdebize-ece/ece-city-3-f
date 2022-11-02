//
// Created by eleuc on 31/10/2022.
//

#include "../../includes/map/map_draw.h"

void map_draw(Map_t *map, float tile_size) {
    Color colors[Tile_Type_Count] = {DARKGREEN, GRAY, SKYBLUE, YELLOW};
    for (int y = 0; y < map->height; ++y) {
        for (int x = 0; x < map->width; ++x) {
            int tile = map->tiles[y * map->width + x]->type;
            DrawPlane((Vector3) {(x + 0.5f)*TILES_WIDTH, 0, (y + 0.5f)*TILES_WIDTH}, (Vector2) {tile_size, tile_size}, colors[tile]);
        }
    }
    DrawGrid2(MAP_WIDTH, TILES_WIDTH, (Vector3) {DECALAGE_MAP_X, 0.05f + DECALAGE_MAP_Y, DECALAGE_MAP_Z});
}