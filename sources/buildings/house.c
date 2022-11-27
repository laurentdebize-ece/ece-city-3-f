//
// Created by eleuc on 01/11/2022.
//

#include "../../includes/buildings/house.h"

House_t *create_house(Vector2 position, BuildingOrientation orientation) {
    House_t *house = malloc(sizeof(House_t));
    house->connexite = 0;
    house->orientation = orientation;
    house->level = Terrain_nu;
    house->counter = 0;
    house->electricity = 0;
    house->water = 0;
    house->distance = 0;
    house->position = position;
    return house;
}

void reset_all_houses_connexity(Queue_t *houses){
    Queue_t *current_house_cell = houses;
    do{
        ((House_t*)current_house_cell->data)->connexite = 0;
        current_house_cell = current_house_cell->next;
    } while (current_house_cell != houses);
}

void find_house_connexity(Map_t *map, House_t *house){
    for (int x = house->position.x - 1; x <= house->position.x + 1 && !house->connexite; ++x) {
        for (int y = house->position.y - 1; y <= house->position.y + 1 && !house->connexite; ++y) {
            if (x == (int) house->position.x - 1 && x - 1 >= 0) {
                if (map->tiles[y * map->width + (x - 1)]->type == Tile_Type_Road){
                    house->connexite = map->tiles[y * map->width + x-1]->connexite;
                    x = map->width;
                    y = map->height;
                }
            }
            if (x == (int) house->position.x + 1 && x + 1 < map->width) {
                if (map->tiles[y * map->width + (x + 1)]->type == Tile_Type_Road){
                    house->connexite = map->tiles[y * map->width + x+1]->connexite;
                    x = map->width;
                    y = map->height;
                }
            }
            if (y == (int) house->position.y - 1 && y - 1 >= 0) {
                if (map->tiles[(y - 1) * map->width + x]->type == Tile_Type_Road){
                    house->connexite = map->tiles[(y - 1) * map->width + x]->connexite;
                    x = map->width;
                    y = map->height;
                }
            }
            if (y == (int) house->position.y + 1 && y + 1 < map->height) {
                if (map->tiles[(y + 1) * map->width + x]->type == Tile_Type_Road){
                    house->connexite = map->tiles[(y + 1) * map->width + x]->connexite;
                    x = map->width;
                    y = map->height;
                }
            }
        }
    }
}

void find_all_houses_connexity(Map_t *map, Queue_t *houses) {
    Queue_t *current_house_cell = houses;
    do {
        House_t *house = current_house_cell->data;
        for (int x = house->position.x - 1; x <= house->position.x + 1 && !house->connexite; ++x) {
            for (int y = house->position.y - 1; y <= house->position.y + 1 && !house->connexite; ++y) {
                if (x == (int) house->position.x - 1 && x - 1 >= 0) {
                    if (map->tiles[y * map->width + (x - 1)]->type == Tile_Type_Road){
                        house->connexite = map->tiles[y * map->width + x-1]->connexite;
                    }
                }
                if (x == (int) house->position.x + 1 && x + 1 < map->width) {
                    if (map->tiles[y * map->width + (x + 1)]->type == Tile_Type_Road){
                        house->connexite = map->tiles[y * map->width + x+1]->connexite;
                    }
                }
                if (y == (int) house->position.y - 1 && y - 1 >= 0) {
                    if (map->tiles[(y - 1) * map->width + x]->type == Tile_Type_Road){
                        house->connexite = map->tiles[(y - 1) * map->width + x]->connexite;
                    }
                }
                if (y == (int) house->position.y + 1 && y + 1 < map->height) {
                    if (map->tiles[(y + 1) * map->width + x]->type == Tile_Type_Road){
                        house->connexite = map->tiles[(y + 1) * map->width + x]->connexite;
                    }
                }
            }
        }
        current_house_cell = current_house_cell->next;
    } while (current_house_cell != houses);
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
        for (int x = position.x - 1; x <= position.x + 1 && !((House_t*)(*houses)->data)->connexite; ++x) {
            for (int y = position.y - 1; y < position.y + 1 && !((House_t *) (*houses)->data)->connexite; ++y) {
                if (x == (int) position.x - 1 && x - 1 >= 0) {
                    if (map->tiles[y * map->width + (x - 1)]->type == Tile_Type_Road)
                        ((House_t *) (*houses)->data)->connexite = map->tiles[(y + 1) * map->width + x]->connexite;
                }
                if (x == (int) position.x + 1 && x + 1 < map->width) {
                    if (map->tiles[y * map->width + (x + 1)]->type == Tile_Type_Road)
                        ((House_t *) (*houses)->data)->connexite = map->tiles[(y + 1) * map->width + x]->connexite;
                }
                if (y == (int) position.y - 1 && y - 1 >= 0) {
                    if (map->tiles[(y - 1) * map->width + x]->type == Tile_Type_Road)
                        ((House_t *) (*houses)->data)->connexite = map->tiles[(y + 1) * map->width + x]->connexite;
                }
                if (y == (int) position.y + 1 && y + 1 < map->height) {
                    if (map->tiles[(y + 1) * map->width + x]->type == Tile_Type_Road)
                        ((House_t *) (*houses)->data)->connexite = map->tiles[(y + 1) * map->width + x]->connexite;
                }
            }
        }
    }
    else {
        Queue_t *new_house = create_queue(create_house(position, orientation));
        for (int y = (int)position.y-1 ; y <= (int)position.y+1; ++y) {
            for (int x = (int)position.x-1; x <= (int)position.x+1; ++x) {
                map->tiles[y*map->width+x]->type = Tile_Type_House;
                map->tiles[y*map->width+x]->building = (House_t*) new_house->data;
            }
        }
        (*houses)->prev->next = new_house;
        new_house->prev = (*houses)->prev;
        (*houses)->prev = new_house;
        new_house->next = *houses;

    }
    map->house_count++;
}

void house_update(Queue_t *houses, Map_t *map, int *population, int *money, int speed) {
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
                switch (current_house->level) {
                    case Cabane:
                        *population+= 10;
                        break;
                    case Maison:
                        *population+= 40;
                        break;
                    case Immeuble:
                        *population+= 50;
                        break;
                    case Gratte_Ciel:
                        *population+= 900;
                        break;
                }
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

void house_update_capitaliste() {

}

void house_update_communiste() {

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