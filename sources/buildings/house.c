//
// Created by eleuc on 01/11/2022.
//

#include "../../includes/buildings/house.h"

House_t *create_house(Vector2 position) {
    House_t *house = malloc(sizeof(House_t));
    house->level = 0;
    house->counter = 0;
    house->electricity = 0;
    house->water = 0;
    house->position = position;
    house->next = NULL;
    house->prev = NULL;
    return house;
}

void add_house(Map_t *map, House_t **house, Vector2 position) {
    for (int y = (int)position.y -1 ; y <= (int)position.y+1; ++y) {
        for (int x = (int)position.x-1; x <= (int)position.x+1; ++x) {
            map->tiles[y*map->width+x]->type = Tile_Type_House;
        }
    }
    if(!*house){
        *house = create_house(position);
        (*house)->next = *house;
        (*house)->prev = *house;
        return;
    }
    House_t *new_house = create_house(position);
    (*house)->prev->next = new_house;
    new_house->prev = (*house)->prev;
    (*house)->prev = new_house;
    new_house->next = *house;
}

void house_update(House_t *house) {
    if(!house){
        return;
    }
    House_t *current_house = house;
    do {
        current_house->counter += 1;
        if (current_house->counter == HOUSE_LEVEL_UPDATE && current_house->level < Nb_Variantes_Maisons) {
            current_house->counter = 0;
            current_house->level += 1;
        }
        current_house = current_house->next;
    }while (current_house != house);
}