//
// Created by eleuc on 01/11/2022.
//

#include "../../includes/buildings/house.h"

House_t *create_house(Vector2 position) {
    House_t *house = malloc(sizeof(House_t));
    house->level = Terrain_nu;
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

void house_update(House_t *house, Map_t *map, int *money) {
    if(!house){
        return;
    }
    House_t *current_house = house;
    do {
        current_house->counter += 1;
        if (current_house->counter == HOUSE_LEVEL_UPDATE) {
            switch (current_house->level) {
                case Cabane:
                    *money += 10*TAX_PER_PERSON;
                    break;
                case Maison:
                    *money += 50*TAX_PER_PERSON;
                    break;
                case Immeuble:
                    *money += 100*TAX_PER_PERSON;
                    break;
                case Gratte_Ciel:
                    *money += 1000*TAX_PER_PERSON;
                    break;
                default:
                    break;
            }
            current_house->counter = 0;

            if (current_house->level < Gratte_Ciel) {
                current_house->level += 1;
                for (int y = (int)current_house->position.y - 1; y <= (int)current_house->position.y+1; ++y) {
                    for (int x = (int)current_house->position.x - 1; x <= (int)current_house->position.x+1; ++x) {
                        map->tiles[y*map->width+x]->varient = current_house->level;
                    }
                }
            }
        }
        current_house = current_house->next;
    }while (current_house != house);
}

void house_draw(House_t *house) {
    Color houseColors[4] = {RED, YELLOW, GREEN, BLUE};
    if(!house){
        return;
    }
    House_t *current_house = house;
    do {
        if(current_house->level >= Cabane){
            DrawCube((Vector3){(current_house->position.x+0.5f)*TILES_WIDTH, (current_house->level-1)*HOUSE_CUBE_WIDTH/2.0f, (current_house->position.y+0.5f)*TILES_WIDTH}, HOUSE_CUBE_WIDTH, (current_house->level-1)*HOUSE_CUBE_WIDTH, HOUSE_CUBE_WIDTH, houseColors[current_house->level-2]);
            DrawCubeWires((Vector3){(current_house->position.x+0.5f)*TILES_WIDTH, (current_house->level-1)*HOUSE_CUBE_WIDTH/2.0f, (current_house->position.y+0.5f)*TILES_WIDTH}, HOUSE_CUBE_WIDTH, (current_house->level-1)*HOUSE_CUBE_WIDTH, HOUSE_CUBE_WIDTH, BLACK);
        }
        current_house = current_house->next;
    }while (current_house != house);
}

void house_destroy(House_t **house){
    if(!*house){
        return;
    }
    House_t *current_house = *house;
    do {
        House_t *next_house = current_house->next;
        free(current_house);
        current_house = next_house;
    }while (current_house != *house);
    *house = NULL;
}