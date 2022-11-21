//
// Created by eleuc on 31/10/2022.
//

#include "../../includes/map/map_draw.h"

void map_draw(Map_t *map, Texture2D road_texture, float tile_size, int vew_mode) {
    switch (vew_mode) {
        case 0: {
            for (int y = 0; y < map->height; ++y) {
                for (int x = 0; x < map->width; ++x) {
                    switch (map->tiles[y * map->width + x]->type) {
                        case Tile_Type_Grass:
                            DrawPlane((Vector3) {(float) x * tile_size + DECALAGE_MAP_X, DECALAGE_MAP_Y,(float) y * tile_size + DECALAGE_MAP_Z}, (Vector2) {tile_size, tile_size},(Color) {0, 255, 0, 255});
                            break;
                        case Tile_Type_Road:
                            //DrawPlane((Vector3) {(float) x * tile_size + DECALAGE_MAP_X, DECALAGE_MAP_Y,(float) y * tile_size + DECALAGE_MAP_Z}, (Vector2) {tile_size, tile_size},GRAY);
                            DrawCubeTextureRec(road_texture, (Rectangle) {0, road_texture.width *(map->tiles[y * map->width + x]->varient),road_texture.width, road_texture.width},(Vector3) {(float) x * tile_size + DECALAGE_MAP_X, DECALAGE_MAP_Y,(float) y * tile_size + DECALAGE_MAP_Z}, tile_size, 0, tile_size, WHITE);
                            break;
                        case Tile_Type_House:
                            DrawPlane((Vector3) {(x + 0.5f) * TILES_WIDTH, 0, (y + 0.5f) * TILES_WIDTH}, (Vector2) {tile_size, tile_size}, GRAY);
                            break;
                        case Tile_Type_Builing:
                            switch (map->tiles[y * map->width + x]->varient) {
                                case Building_Varient_Water_Tower:
                                    DrawPlane((Vector3) {(x + 0.5f) * TILES_WIDTH, 0, (y + 0.5f) * TILES_WIDTH}, (Vector2) {tile_size, tile_size}, BLUE);
                                    break;
                                case Building_Varient_Power_Plant:
                                    DrawPlane((Vector3) {(x + 0.5f) * TILES_WIDTH, 0, (y + 0.5f) * TILES_WIDTH}, (Vector2) {tile_size, tile_size}, YELLOW);
                                    break;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
            break;
        case 1: {
            for (int y = 0; y < map->height; ++y) {
                for (int x = 0; x < map->width; ++x) {
                    if (map->tiles[y * map->width + x]->type == Tile_Type_Road)
                        DrawPlane((Vector3) {(float) x * tile_size + DECALAGE_MAP_X, DECALAGE_MAP_Y,
                                             (float) y * tile_size + DECALAGE_MAP_Z}, (Vector2) {tile_size, tile_size},
                                  BLUE);
                    else if (map->tiles[y * map->width + x]->type == Tile_Type_Builing && map->tiles[y * map->width + x]->varient == Building_Varient_Water_Tower)
                        DrawPlane((Vector3) {(float) x * tile_size + DECALAGE_MAP_X, DECALAGE_MAP_Y,
                                             (float) y * tile_size + DECALAGE_MAP_Z}, (Vector2) {tile_size, tile_size},
                                  DARKBLUE);
                    else
                        DrawPlane((Vector3) {(float) x * tile_size + DECALAGE_MAP_X, DECALAGE_MAP_Y,
                                             (float) y * tile_size + DECALAGE_MAP_Z}, (Vector2) {tile_size, tile_size},
                                  DARKGREEN);
                }
            }
        }
            break;
        case 2: {
            for (int y = 0; y < map->height; ++y) {
                for (int x = 0; x < map->width; ++x) {
                    if (map->tiles[y * map->width + x]->type == Tile_Type_Road)
                        DrawPlane((Vector3) {(float) x * tile_size + DECALAGE_MAP_X, DECALAGE_MAP_Y,
                                             (float) y * tile_size + DECALAGE_MAP_Z}, (Vector2) {tile_size, tile_size},
                                  YELLOW);
                    else if (map->tiles[y * map->width + x]->type == Tile_Type_Builing && map->tiles[y * map->width + x]->varient == Building_Varient_Power_Plant)
                        DrawPlane((Vector3) {(float) x * tile_size + DECALAGE_MAP_X, DECALAGE_MAP_Y,
                                             (float) y * tile_size + DECALAGE_MAP_Z}, (Vector2) {tile_size, tile_size},
                                  ORANGE);
                    else
                        DrawPlane((Vector3) {(float) x * tile_size + DECALAGE_MAP_X, DECALAGE_MAP_Y,
                                             (float) y * tile_size + DECALAGE_MAP_Z}, (Vector2) {tile_size, tile_size},
                                  DARKGREEN);
                }
            }
        }
            break;
        default:
            break;
    }
    DrawGrid2(map->width, TILES_WIDTH, (Vector3) {map->width*DECALAGE_MAP_X, 0.05f + DECALAGE_MAP_Y, map->height*DECALAGE_MAP_Z});
}

_Bool is_mouse_on_map(Map_t *map, Vector2 mouse_pos_world) {
    if (mouse_pos_world.x < 0 || mouse_pos_world.x > map->width || mouse_pos_world.y < 0 || mouse_pos_world.y > map->height)
        return false;
    return true;
}