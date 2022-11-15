//
// Created by eleuc on 01/11/2022.
//

#include "../../includes/buildings/house.h"

House_t *create_house(Vector2 position) {
    House_t *house = malloc(sizeof(House_t));

    house->buildings[1] = LoadModel("../assets/Models3d/Houses/buildingP1.obj"); // tableaux des maisons 3D
    house-> bounds[1] = GetMeshBoundingBox(house->buildings[1].meshes[0]);   // Set model bounds

    house->buildings[2] = LoadModel("../assets/Models3d/Houses/buildingM1.obj");
    house-> bounds[2] = GetMeshBoundingBox(house->buildings[2].meshes[0]);

    house->buildings[3] = LoadModel("../assets/Models3d/Houses/buildingG1.obj");
    house-> bounds[3] = GetMeshBoundingBox(house->buildings[3].meshes[0]);

    house->buildings[4] = LoadModel("../assets/Models3d/Houses/buildingT1.obj");
    house-> bounds[4] = GetMeshBoundingBox(house->buildings[4].meshes[0]);

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
    if(!*house){
        *house = create_house(position);
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
        House_t *new_house = create_house(position);
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

void house_draw(House_t *house) {
    Color houseColors[4] = {RED, YELLOW, GREEN, BLUE};


    if(!house){
        return;
    }
    House_t *current_house = house;
    do {
        if(current_house->level >= Cabane){

            DrawModel(house-> buildings[current_house->level - 1], (Vector3){(current_house->position.x+0.5f)*TILES_WIDTH, 0, (current_house->position.y+0.5f)*TILES_WIDTH}, 5.0f, WHITE);        // Draw 3d model with texture

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

void draw_transparent_house(Map_t *map, Vector2 mouse_pos_world, int money){
    /// Si on peut construire une maison
    if (is_possible_to_build(map, mouse_pos_world, Tile_Type_House, money)){
        /// On dessine une maison transparente verte à la position de la souris (pour montrer où elle sera construite)
        DrawCube((Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, HOUSE_CUBE_WIDTH, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, HOUSE_CUBE_WIDTH, HOUSE_CUBE_WIDTH*2, HOUSE_CUBE_WIDTH,Fade(GREEN, 0.5f));
        DrawCubeWires((Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, HOUSE_CUBE_WIDTH, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, HOUSE_CUBE_WIDTH, HOUSE_CUBE_WIDTH*2, HOUSE_CUBE_WIDTH, Fade(BLACK, 0.5f));
    }
        /// Si on ne peut pas construire une maison
    else{
        /// On dessine une maison transparente rouge à la position de la souris (pour montrer où elle ne sera pas construite)
        DrawCube((Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, HOUSE_CUBE_WIDTH, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, HOUSE_CUBE_WIDTH, HOUSE_CUBE_WIDTH*2, HOUSE_CUBE_WIDTH,Fade(RED, 0.5f));
        DrawCubeWires((Vector3){(mouse_pos_world.x+0.5f)*TILES_WIDTH, HOUSE_CUBE_WIDTH, (mouse_pos_world.y+0.5f)*TILES_WIDTH}, HOUSE_CUBE_WIDTH, HOUSE_CUBE_WIDTH*2, HOUSE_CUBE_WIDTH, Fade(BLACK, 0.5f));
    }
}

