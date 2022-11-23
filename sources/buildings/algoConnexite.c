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

void connexity_init(Map_t *map) {
    for (int i = 0; i < map->width*map->height; i++) {
        if (map->tiles[i]->type == Tile_Type_Road) {
            if (!map->tiles[i]->connexite){
                map->nb_connexite++;
                int connexite = map->nb_connexite;
                map->tiles[i]->connexite = connexite;
                Queue_t *queue = create_queue(i);
                queue->next = queue;
                queue->prev = queue;
                while (queue){
                    int num_case = (int) queue->data;
                    retirer_premier_queue(&queue);
                    /// Si la case de droite n'est pas hors du plateau
                    if (num_case%map->width != map->width-1){
                        /// Si la case de droite est une route et qu'elle n'a pas encore de connexité
                        if (map->tiles[num_case+1]->type == Tile_Type_Road && !map->tiles[num_case+1]->connexite){
                            map->tiles[num_case+1]->connexite = connexite;
                            add_queue(&queue, (void *) (num_case + 1));
                        }
                        /// Si la case de droite est une maison et qu'elle n'a pas encore de connexité
                        else if (map->tiles[num_case+1]->type == Tile_Type_House && !((House_t*)map->tiles[num_case+1]->building)->connexite){
                            ((House_t*)map->tiles[num_case+1]->building)->connexite = connexite;
                        }
                        /// Si la case de droite est un bâtiment et qu'il n'a pas encore de connexité
                        else if (map->tiles[num_case+1]->type == Tile_Type_Builing) {
                            /// Si le bâtiment est un château d'eau
                            if (map->tiles[num_case+1]->varient == Building_Varient_Water_Tower && !((Water_Tower_t *)map->tiles[num_case+1]->building)->connexite){
                                ((Water_Tower_t *)map->tiles[num_case+1]->building)->connexite = connexite;
                            }
                            /// Si le bâtiment est une centrale électrique
                            else if (map->tiles[num_case+1]->varient == Building_Varient_Power_Plant && !((Power_Plant_t *)map->tiles[num_case+1]->building)->connexite){
                                ((Power_Plant_t *)map->tiles[num_case+1]->building)->connexite = connexite;
                            }
                        }
                    }
                    if (map->tiles[num_case-1]->type == Tile_Type_Road && !map->tiles[num_case-1]->connexite && num_case%map->width != 0){
                        map->tiles[num_case-1]->connexite = connexite;
                        add_queue(&queue, (void *) (num_case - 1));
                    }
                    if (map->tiles[num_case+map->width]->type == Tile_Type_Road && !map->tiles[num_case+map->width]->connexite && num_case+map->width < map->width*map->height){
                        map->tiles[num_case+map->width]->connexite = connexite;
                        add_queue(&queue, (void *) (num_case + map->width));
                    }
                    if (map->tiles[num_case-map->width]->type == Tile_Type_Road && !map->tiles[num_case-map->width]->connexite && num_case-map->width >= 0){
                        map->tiles[num_case-map->width]->connexite = connexite;
                        add_queue(&queue, (void *) (num_case - map->width));
                    }
                }
            }
        }
    }
}

void reset_connexity(Map_t *map) {
    for (int i = 0; i < map->width*map->height; i++) {
        if (map->tiles[i]->type == Tile_Type_Road) {
            map->tiles[i]->connexite = 0;
        }
    }
    map->nb_connexite = 0;
}