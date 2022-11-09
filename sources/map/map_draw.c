//
// Created by eleuc on 31/10/2022.
//

#include "../../includes/map/map_draw.h"

void map_draw(Map_t *map, float tile_size) {
    Color house_colors[Nb_Variantes_Maisons] = {BROWN, LIME, RED, GREEN, BLUE, PURPLE};
    for (int y = 0; y < map->height; ++y) {
        for (int x = 0; x < map->width; ++x) {
            int tile = map->tiles[y * map->width + x]->type;
            if (map->tiles[y * map->width + x]->type == Tile_Type_Road)
                DrawPlane((Vector3) {(float) x * tile_size + DECALAGE_MAP_X, DECALAGE_MAP_Y, (float) y * tile_size + DECALAGE_MAP_Z}, (Vector2) {tile_size, tile_size}, GRAY);
            else if (map->tiles[y*map->width + x]->type == Tile_Type_House)
                DrawPlane((Vector3) {(x + 0.5f)*TILES_WIDTH, 0, (y + 0.5f)*TILES_WIDTH}, (Vector2) {tile_size, tile_size}, house_colors[map->tiles[y*map->width + x]->varient]);
            else if (map->tiles[y*map->width + x]->type == Tile_Type_Builing)
                DrawPlane((Vector3) {(x + 0.5f)*TILES_WIDTH, 0, (y + 0.5f)*TILES_WIDTH}, (Vector2) {tile_size, tile_size}, YELLOW);
            else
                DrawPlane((Vector3) {(float) x * tile_size + DECALAGE_MAP_X, DECALAGE_MAP_Y, (float) y * tile_size + DECALAGE_MAP_Z}, (Vector2) {tile_size, tile_size}, DARKGREEN);
        }
    }
    DrawGrid2(map->width, TILES_WIDTH, (Vector3) {map->width*DECALAGE_MAP_X, 0.05f + DECALAGE_MAP_Y, map->height*DECALAGE_MAP_Z});
}