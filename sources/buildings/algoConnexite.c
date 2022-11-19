//
// Created by theos on 09/11/2022.
//

#include "../../includes/buildings/algoConnexite.h"


void changeConnexite() {

}

void connexite(Map_t *map) {


    for (int i = 0; i < map->width * map->height; i++) {
        if (map->tiles[i]->type == Tile_Type_Road) {
            if (map->tiles[i]->connexite == 0) {
                map->nb_connexite++;
                map->tiles[i]->connexite = map->nb_connexite;
                int num_case = i;
                while ((map->tiles[num_case + 1]->type == Tile_Type_Road &&
                        map->tiles[num_case + 1]->connexite != map->tiles[num_case]->connexite) ||
                       (map->tiles[num_case - 1]->type == Tile_Type_Road &&
                        map->tiles[num_case - 1]->connexite != map->tiles[num_case]->connexite) ||
                       (map->tiles[num_case - map->width]->type == Tile_Type_Road &&
                        map->tiles[num_case - map->width]->connexite != map->tiles[num_case]->connexite) ||
                       (map->tiles[num_case + map->height]->type == Tile_Type_Road &&
                        map->tiles[num_case + map->height]->connexite != map->tiles[num_case]->connexite)) {

                    if (map->tiles[num_case + 1]->type == Tile_Type_Road &&
                        map->tiles[num_case + 1]->connexite != map->tiles[num_case]->connexite) {

                        map->tiles[num_case + 1]->connexite = map->tiles[num_case]->connexite;
                        num_case = num_case + 1;

                    } else if (map->tiles[num_case - 1]->type == Tile_Type_Road &&
                               map->tiles[num_case - 1]->connexite != map->tiles[num_case]->connexite) {

                        map->tiles[num_case - 1]->connexite = map->tiles[num_case]->connexite;
                        num_case = num_case - 1;

                    } else if (map->tiles[num_case - map->width]->type == Tile_Type_Road &&
                               map->tiles[num_case - map->width]->connexite != map->tiles[num_case]->connexite) {
                        map->tiles[num_case - map->width]->connexite = map->tiles[num_case]->connexite;
                        num_case = num_case - map->width;

                    } else if (map->tiles[num_case + map->height]->type == Tile_Type_Road &&
                               map->tiles[num_case + map->height]->connexite != map->tiles[num_case]->connexite) {
                        map->tiles[num_case - map->height]->connexite = map->tiles[num_case]->connexite;
                        num_case = num_case - map->height;
                    }
                }
            }
        }
    }

}