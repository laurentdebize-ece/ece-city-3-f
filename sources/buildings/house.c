//
// Created by eleuc on 01/11/2022.
//

#include "../../includes/buildings/house.h"
/*
House_t *create_house(Vector2 position, BuildingOrientation orientation) {
    House_t *house = malloc(sizeof(House_t));
    house->connexite = 0;
    house->orientation = orientation;
    house->level = Terrain_nu;
    house->counter = 0;
    house->electricity = 0;
    house->water = 0;
    house->position = position;
    return house;
}

void add_house(Map_t *map, House_t **house, Vector2 position, BuildingOrientation orientation) {
    if(!*house){
        *house = create_house(position, orientation);
        (*house)->next = *house;
        (*house)->prev = *house;
        for (int y = (int)position.y -1 ; y <= (int)position.y+1; ++y) {
            for (int x = (int)position.x-1; x <= (int)position.x+1; ++x) {
                map->tiles[y*map->width+x]->type = Tile_Type_House;
                map->tiles[y*map->width+x]->building = *house;
            }
        }
    }
    else {
        House_t *new_house = create_house(position, orientation);
        (*house)->prev->next = new_house;
        new_house->prev = (*house)->prev;
        (*house)->prev = new_house;
        new_house->next = *house;
        for (int y = (int)position.y -1 ; y <= (int)position.y+1; ++y) {
            for (int x = (int)position.x-1; x <= (int)position.x+1; ++x) {
                map->tiles[y*map->width+x]->type = Tile_Type_House;
                map->tiles[y*map->width+x]->building = (House_t*) new_house;
            }
        }
    }
    map->house_count++;
}

void house_update(House_t *house, Map_t *map, int *money, int speed) {
    if(!house){
        return;
    }
    House_t *current_house = house;
    do {
        current_house->counter += speed;
        if (current_house->counter >= HOUSE_LEVEL_UPDATE) {
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
            current_house->counter = current_house->counter % (int)HOUSE_LEVEL_UPDATE;

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

void house_draw(House_t *house, Model *house_mesh) {
    Color houseColors[4] = {RED, YELLOW, GREEN, BLUE};


    if(!house){
        return;
    }
    House_t *current_house = house;
    do {
        if(current_house->level >= Cabane){

            //DrawModel(house_mesh[current_house->level - 2], (Vector3){(current_house->position.x+0.5f)*TILES_WIDTH, 0, (current_house->position.y+0.5f)*TILES_WIDTH}, 1.0f, WHITE);        // Draw 3d model with texture
            //DrawModelWires(house_mesh[current_house->level - 2], (Vector3){(current_house->position.x+0.5f)*TILES_WIDTH, 0, (current_house->position.y+0.5f)*TILES_WIDTH}, 1.0f, LIGHTGRAY);  // Draw 3d model wires (with texture)
            DrawModelEx(house_mesh[current_house->level - 2], (Vector3){(current_house->position.x+0.5f)*TILES_WIDTH, 0, (current_house->position.y+0.5f)*TILES_WIDTH}, (Vector3){0, 1, 0}, house->orientation * 90, (Vector3){1, 1, 1}, WHITE);

            //DrawCube((Vector3){(current_house->position.x+0.5f)*TILES_WIDTH, (current_house->level-1)*HOUSE_CUBE_WIDTH/2.0f, (current_house->position.y+0.5f)*TILES_WIDTH}, HOUSE_CUBE_WIDTH, (current_house->level-1)*HOUSE_CUBE_WIDTH, HOUSE_CUBE_WIDTH, houseColors[current_house->level-2]);
            //DrawCubeWires((Vector3){(current_house->position.x+0.5f)*TILES_WIDTH, (current_house->level-1)*HOUSE_CUBE_WIDTH/2.0f, (current_house->position.y+0.5f)*TILES_WIDTH}, HOUSE_CUBE_WIDTH, (current_house->level-1)*HOUSE_CUBE_WIDTH, HOUSE_CUBE_WIDTH, BLACK);
        }
        current_house = current_house->next;
    }while (current_house != house);
}

void house_destroy_one(Map_t *map, House_t **houses, House_t *house_to_destroy) {

    if((*houses)->next == *houses){   /// S'il n'y a qu'une seule maison
        for (int y = (*houses)->position.y-1; y <= (*houses)->position.y+1; ++y) {
            for (int x = (*houses)->position.x-1; x <= (*houses)->position.x+1; ++x) {
                map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                map->tiles[y*map->width+x]->building = NULL;
                map->tiles[y*map->width+x]->varient = 0;
            }
        }
        free(*houses);
        *houses = NULL;
    }
    else if (*houses == house_to_destroy) { /// Si la maison à démolir est la première maison de la liste chaînée
        (*houses)->prev->next = (*houses)->next;
        (*houses)->next->prev = (*houses)->prev;
        (*houses) = (*houses)->next;
        for (int y = house_to_destroy->position.y-1; y <= house_to_destroy->position.y+1; ++y) {
            for (int x = house_to_destroy->position.x-1; x <= house_to_destroy->position.x+1; ++x) {
                map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                map->tiles[y*map->width+x]->building = NULL;
                map->tiles[y*map->width+x]->varient = 0;
            }
        }
        free(house_to_destroy);
        house_to_destroy = NULL;
    }
    else{   /// Sinon
        house_to_destroy->prev->next = house_to_destroy->next;
        house_to_destroy->next->prev = house_to_destroy->prev;

        for (int y = house_to_destroy->position.y-1; y <= house_to_destroy->position.y+1; ++y) {
            for (int x = house_to_destroy->position.x-1; x <= house_to_destroy->position.x+1; ++x) {
                map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                map->tiles[y*map->width+x]->building = NULL;
                map->tiles[y*map->width+x]->varient = 0;
            }
        }
        free(house_to_destroy);
        house_to_destroy = NULL;
    }
    map->house_count--;
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

void draw_transparent_house(Map_t *map, Vector2 mouse_pos_world, int money, BuildingOrientation orientation, Model *house_mesh) {
    /// Si on peut construire une maison
    if (is_possible_to_build(map, mouse_pos_world, Tile_Type_House, money)){
        /// On dessine une maison transparente verte à la position de la souris (pour montrer où elle sera construite)
        //DrawModel(house_mesh[0], (Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, 0, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, 1.0f,Fade(GREEN, 0.5f));
        DrawModelEx(house_mesh[0], (Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, 0, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, (Vector3){0, 1, 0}, orientation * 90, (Vector3){1, 1, 1}, GREEN);
    }
        /// Si on ne peut pas construire une maison
    else{
        /// On dessine une maison transparente rouge à la position de la souris (pour montrer où elle ne sera pas construite)
        //DrawModel(house_mesh[0], (Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, 0, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, 1.0f,Fade(RED, 0.5f));
        DrawModelEx(house_mesh[0], (Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, 0, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, (Vector3){0, 1, 0}, orientation * 90, (Vector3){1, 1, 1}, RED);
    }
}

*/
/*
House_t *create_house(Vector2 position, BuildingOrientation orientation) {
    House_t *house = malloc(sizeof(House_t));
    house->connexite = 0;
    house->orientation = orientation;
    house->level = Terrain_nu;
    house->counter = 0;
    house->electricity = 0;
    house->water = 0;
    house->position = position;
    return house;
}

void add_house(Map_t *map, Queue_t **houses, Vector2 position, BuildingOrientation orientation) {
    if(!*houses){
        *houses = create_queue(create_house(position, orientation));
        (*houses)->next = *houses;
        (*houses)->prev = *houses;
        for (int y = (int)position.y -1 ; y <= (int)position.y+1; ++y) {
            for (int x = (int)position.x-1; x <= (int)position.x+1; ++x) {
                map->tiles[y*map->width+x]->type = Tile_Type_House;
                map->tiles[y*map->width+x]->building = (*houses)->data;
            }
        }
    }
    else {
        Queue_t *new_house = create_queue(create_house(position, orientation));
        (*houses)->prev->next = new_house;
        new_house->prev = (*houses)->prev;
        (*houses)->prev = new_house;
        new_house->next = *houses;
        for (int y = (int)position.y -1 ; y <= (int)position.y+1; ++y) {
            for (int x = (int)position.x-1; x <= (int)position.x+1; ++x) {
                map->tiles[y*map->width+x]->type = Tile_Type_House;
                map->tiles[y*map->width+x]->building = (House_t*) new_house->data;
            }
        }
    }
    map->house_count++;
}

void house_update(Queue_t *houses, Map_t *map, int *money, int speed) {
    if(!houses){
        return;
    }
    Queue_t *current_house_in_queue = houses;
    do {
        House_t *current_house = current_house_in_queue->data;
        current_house->counter += speed;
        if (current_house->counter >= HOUSE_LEVEL_UPDATE) {
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
            current_house->counter = current_house->counter % (int)HOUSE_LEVEL_UPDATE;

            if (current_house->level < Gratte_Ciel) {
                current_house->level += 1;
                for (int y = (int)current_house->position.y - 1; y <= (int)current_house->position.y+1; ++y) {
                    for (int x = (int)current_house->position.x - 1; x <= (int)current_house->position.x+1; ++x) {
                        map->tiles[y*map->width+x]->varient = current_house->level;
                    }
                }
            }
        }
        current_house_in_queue = current_house_in_queue->next;
    }while (current_house_in_queue != houses);
}

void house_draw(Queue_t *houses, Model *house_mesh) {
    /// S'il n'y a pas de maison
    if(!houses){
        return;
    }
    /// S'il y a des maisons
    Queue_t *current_house_in_queue = houses;
    do {
        House_t *current_house = current_house_in_queue->data;
        if(current_house->level >= Cabane){

            DrawModelEx(house_mesh[current_house->level - 2], (Vector3){(current_house->position.x+0.5f)*TILES_WIDTH, 0, (current_house->position.y+0.5f)*TILES_WIDTH}, (Vector3){0, 1, 0}, current_house->orientation * 90, (Vector3){1, 1, 1}, WHITE);
        }
        current_house_in_queue = current_house_in_queue->next;
    }while (current_house_in_queue != houses);
}

void house_destroy_one(Map_t *map, Queue_t **houses, House_t *house_to_destroy) {

    if((*houses)->next == *houses){   /// S'il n'y a qu'une seule maison
        house_to_destroy = (*houses)->data;
        for (int y = house_to_destroy->position.y-1; y <= house_to_destroy->position.y+1; ++y) {
            for (int x = house_to_destroy->position.x-1; x <= house_to_destroy->position.x+1; ++x) {
                map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                map->tiles[y*map->width+x]->building = NULL;
                map->tiles[y*map->width+x]->connexite = 0;
                map->tiles[y*map->width+x]->varient = 0;
            }
        }
        free((*houses)->data);
        free(*houses);
        *houses = NULL;
    }
    else if ((*houses)->data == house_to_destroy) { /// Si la maison à démolir est la première maison de la liste chaînée
        Queue_t *cell_to_destroy = *houses;
        (*houses)->prev->next = (*houses)->next;
        (*houses)->next->prev = (*houses)->prev;
        (*houses) = (*houses)->next;
        for (int y = house_to_destroy->position.y-1; y <= house_to_destroy->position.y+1; ++y) {
            for (int x = house_to_destroy->position.x-1; x <= house_to_destroy->position.x+1; ++x) {
                map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                map->tiles[y*map->width+x]->building = NULL;
                map->tiles[y*map->width+x]->connexite = 0;
                map->tiles[y*map->width+x]->varient = 0;
            }
        }
        free(house_to_destroy);
        free(cell_to_destroy);
        house_to_destroy = NULL;
    }
    else{   /// Sinon

        Queue_t *cell_to_destroy = (*houses)->next;
        while(cell_to_destroy->data != house_to_destroy)
            cell_to_destroy = cell_to_destroy->next;
        cell_to_destroy->prev->next = cell_to_destroy->next;
        cell_to_destroy->next->prev = cell_to_destroy->prev;

        for (int y = house_to_destroy->position.y-1; y <= house_to_destroy->position.y+1; ++y) {
            for (int x = house_to_destroy->position.x-1; x <= house_to_destroy->position.x+1; ++x) {
                map->tiles[y*map->width+x]->type = Tile_Type_Grass;
                map->tiles[y*map->width+x]->building = NULL;
                map->tiles[y*map->width+x]->connexite = 0;
                map->tiles[y*map->width+x]->varient = 0;
            }
        }
        free(house_to_destroy);
        free(cell_to_destroy);
        house_to_destroy = NULL;
    }
    map->house_count--;
}

void house_destroy(Queue_t **houses){
    if(!*houses){
        return;
    }
    Queue_t *current_house = *houses;
    do {
        Queue_t *next_house = current_house->next;
        free(current_house->data);
        free(current_house);
        current_house = next_house;
    }while (current_house != *houses);
    *houses = NULL;
}

void draw_transparent_house(Map_t *map, Vector2 mouse_pos_world, int money, BuildingOrientation orientation, Model *house_mesh) {
    /// Si on peut construire une maison
    if (is_possible_to_build(map, mouse_pos_world, Tile_Type_House, money, 0)){
        /// On dessine une maison transparente verte à la position de la souris (pour montrer où elle sera construite)
        //DrawModel(house_mesh[0], (Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, 0, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, 1.0f,Fade(GREEN, 0.5f));
        DrawModelEx(house_mesh[0], (Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, 0, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, (Vector3){0, 1, 0}, orientation * 90, (Vector3){1, 1, 1}, GREEN);
    }
        /// Si on ne peut pas construire une maison
    else{
        /// On dessine une maison transparente rouge à la position de la souris (pour montrer où elle ne sera pas construite)
        //DrawModel(house_mesh[0], (Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, 0, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, 1.0f,Fade(RED, 0.5f));
        DrawModelEx(house_mesh[0], (Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, 0, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, (Vector3){0, 1, 0}, orientation * 90, (Vector3){1, 1, 1}, RED);
    }
}

*/