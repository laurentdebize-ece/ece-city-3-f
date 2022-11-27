//
// Created by eleuc on 22/11/2022.
//

#include "../../includes/buildings/water_elec_distribution.h"

Cell_t *create_cell(int x, int y, int distance) {
    Cell_t *cell = malloc(sizeof(Cell_t));
    cell->x = x;
    cell->y = y;
    cell->distance = distance;
    return cell;
}

Building_With_Distance_t *create_building_with_distance(void *building, int distance) {
    Building_With_Distance_t *building_with_distance = malloc(sizeof(Building_With_Distance_t));
    building_with_distance->building = building;
    building_with_distance->distance = distance;
    return building_with_distance;
}

void trier_centrale_par_connexite(Power_Plant_t **power_plants){

}

void add_house_to_power_plant_by_level(Power_Plant_t *power_plant, House_t *house) {
    if (!power_plant->houses) {
        add_to_back_queue(&power_plant->houses, house);
    }
    else{
        Queue_t *current_power_plant_house = power_plant->houses;
        while (current_power_plant_house != power_plant->houses->prev && ((House_t *)current_power_plant_house->data)->level >= house->level){
            current_power_plant_house = current_power_plant_house->next;
        }
        current_power_plant_house->prev->next = create_queue(house);
        current_power_plant_house->prev->next->next = current_power_plant_house;
        current_power_plant_house->prev = current_power_plant_house->prev->next;
    }
}

void add_houses_to_queue_by_connexity(Power_Plant_t *power_plant, Queue_t *houses){
    Queue_t *current_house_cell = houses;
    if (houses) {
        do {
            House_t *current_house = current_house_cell->data;
            if (current_house->connexite == power_plant->connexite) {
                add_house_to_power_plant_by_level(power_plant, current_house);
            }
            current_house_cell = current_house_cell->next;
        } while (current_house_cell != houses);
    }
}

void electric_distribution(Power_Plant_t *power_plant, Queue_t *houses){
    add_houses_to_queue_by_connexity(power_plant, houses);
    Queue_t *current_house_cell = power_plant->houses;
    do {
        House_t *current_house = current_house_cell->data;
        if (current_house->electricity == 0 && current_house->level > Terrain_nu){
            switch (current_house->level) {
                case Cabane:
                    if (power_plant->electrecity >= 10) {
                        current_house->electricity = 10;
                        power_plant->electrecity -= 10;
                    }
                    break;
                case Maison:
                    if (power_plant->electrecity >= 40){
                        current_house->electricity = 50;
                        power_plant->electrecity -= 40;
                    }
                    break;
                case Immeuble:
                    if (power_plant->electrecity >= 50){
                        current_house->electricity = 100;
                        power_plant->electrecity -= 50;
                    }
                    break;
                case Gratte_Ciel:
                    if (power_plant->electrecity >= 900){
                        current_house->electricity = 1000;
                        power_plant->electrecity -= 900;
                    }
                    break;
            }
        }
        current_house_cell = current_house_cell->next;
    }while (current_house_cell != power_plant->houses->prev && power_plant->electrecity > 0);
}

bool is_water_tower_connected_to_house(Water_Tower_t *water_tower, House_t *house){
    if (!house->water_towers) return false;
    Queue_t *current_water_tower = house->water_towers;
    while (current_water_tower != house->water_towers->prev){
        if (current_water_tower->data == water_tower){
            return true;
        }
        current_water_tower = current_water_tower->next;
    }
    return false;
}

void add_house_to_water_tower(Water_Tower_t *water_tower, House_t *house, int distance) {
    if (!water_tower->houses) {
        add_to_back_queue(&water_tower->houses, create_building_with_distance(house, distance));
    }
    else{
        Queue_t *current_water_tower_house = water_tower->houses;
        while (current_water_tower_house != water_tower->houses->prev && ((House_t *)current_water_tower_house->data)->level >= house->level){
            current_water_tower_house = current_water_tower_house->next;
        }
        current_water_tower_house->prev->next = create_queue(create_building_with_distance(house, distance));
        current_water_tower_house->prev->next->next = current_water_tower_house;
        current_water_tower_house->prev = current_water_tower_house->prev->next;
    }
}

void link_house_to_water_towers(Map_t *map, House_t *house){
    Queue_t *cells = NULL;
    for (int x = house->position.x - 1; x <= house->position.x + 1; ++x) {
        for (int y = house->position.y - 1; y <= house->position.y + 1; ++y) {
            if (x == (int) house->position.x - 1 && x - 1 >= 0) {
                if (map->tiles[y * map->width + (x - 1)]->type == Tile_Type_Road)
                    add_to_front_queue(&cells, create_cell(x - 1, y, 1));
            }
            if (x == (int) house->position.x + 1 && x + 1 < map->width) {
                if (map->tiles[y * map->width + (x + 1)]->type == Tile_Type_Road)
                    add_to_front_queue(&cells, create_cell(x + 1, y, 1));
            }
            if (y == (int) house->position.y - 1 && y - 1 >= 0) {
                if (map->tiles[(y - 1) * map->width + x]->type == Tile_Type_Road)
                    add_to_front_queue(&cells, create_cell(x, y - 1, 1));
            }
            if (y == (int) house->position.y + 1 && y + 1 < map->height) {
                if (map->tiles[(y + 1) * map->width + x]->type == Tile_Type_Road)
                    add_to_front_queue(&cells, create_cell(x, y + 1, 1));
            }
        }
    }
    Queue_t *current_cell = cells;
    do {
        Cell_t *current_cell_data = current_cell->data;
        map->tiles[current_cell_data->y * map->width + current_cell_data->x]->water = true;
        if (current_cell_data->x+1 < map->width){
            if (map->tiles[current_cell_data->y * map->width + (current_cell_data->x + 1)]->type == Tile_Type_Road && map->tiles[current_cell_data->y * map->width + (current_cell_data->x + 1)]->distance > current_cell_data->distance + 1){
                map->tiles[current_cell_data->y * map->width + (current_cell_data->x + 1)]->distance = current_cell_data->distance + 1;
                add_to_front_queue(&cells, create_cell(current_cell_data->x + 1, current_cell_data->y, current_cell_data->distance + 1));
            }
            else if (map->tiles[current_cell_data->y * map->width + (current_cell_data->x - 1)]->type == Tile_Type_Builing && map->tiles[current_cell_data->y * map->width + (current_cell_data->x - 1)]->varient == Building_Varient_Water_Tower && !is_water_tower_connected_to_house(map->tiles[current_cell_data->y * map->width + (current_cell_data->x - 1)]->building, house)){
                add_house_to_water_tower((Water_Tower_t*) map->tiles[current_cell_data->y * map->width + (current_cell_data->x - 1)]->building, house, current_cell_data->distance + 1);
                house->water_towers = create_queue(create_building_with_distance(map->tiles[current_cell_data->y * map->width + (current_cell_data->x - 1)]->building, current_cell_data->distance + 1));
            }
        }
        if (current_cell_data->x-1 >= 0){
            if (map->tiles[current_cell_data->y * map->width + (current_cell_data->x - 1)]->type == Tile_Type_Road && map->tiles[current_cell_data->y * map->width + (current_cell_data->x - 1)]->distance > current_cell_data->distance + 1){
                map->tiles[current_cell_data->y * map->width + (current_cell_data->x - 1)]->distance = current_cell_data->distance + 1;
                add_to_front_queue(&cells, create_cell(current_cell_data->x - 1, current_cell_data->y, current_cell_data->distance + 1));
            }
            else if (map->tiles[current_cell_data->y * map->width + (current_cell_data->x - 1)]->type == Tile_Type_Builing && map->tiles[current_cell_data->y * map->width + (current_cell_data->x - 1)]->varient == Building_Varient_Water_Tower && !is_water_tower_connected_to_house(map->tiles[current_cell_data->y * map->width + (current_cell_data->x - 1)]->building, house)){
                add_house_to_water_tower((Water_Tower_t*) map->tiles[current_cell_data->y * map->width + (current_cell_data->x - 1)]->building, house, current_cell_data->distance + 1);
                house->water_towers = create_queue(create_building_with_distance(map->tiles[current_cell_data->y * map->width + (current_cell_data->x - 1)]->building, current_cell_data->distance + 1));
            }
        }
        if (current_cell_data->y+1 < map->height){
            if (map->tiles[(current_cell_data->y + 1) * map->width + current_cell_data->x]->type == Tile_Type_Road && map->tiles[(current_cell_data->y + 1) * map->width + current_cell_data->x]->distance > current_cell_data->distance + 1){
                map->tiles[(current_cell_data->y + 1) * map->width + current_cell_data->x]->distance = current_cell_data->distance + 1;
                add_to_front_queue(&cells, create_cell(current_cell_data->x, current_cell_data->y + 1, current_cell_data->distance + 1));
            }
            else if (map->tiles[(current_cell_data->y + 1) * map->width + current_cell_data->x]->type == Tile_Type_Builing && map->tiles[(current_cell_data->y + 1) * map->width + current_cell_data->x]->varient == Building_Varient_Water_Tower && !is_water_tower_connected_to_house(map->tiles[(current_cell_data->y + 1) * map->width + current_cell_data->x]->building, house)){
                add_house_to_water_tower((Water_Tower_t*) map->tiles[(current_cell_data->y + 1) * map->width + current_cell_data->x]->building, house, current_cell_data->distance + 1);
                house->water_towers = create_queue(create_building_with_distance(map->tiles[(current_cell_data->y + 1) * map->width + current_cell_data->x]->building, current_cell_data->distance + 1));
            }
        }
        if (current_cell_data->y-1 >= 0){
            if (map->tiles[(current_cell_data->y - 1) * map->width + current_cell_data->x]->type == Tile_Type_Road && map->tiles[(current_cell_data->y - 1) * map->width + current_cell_data->x]->distance > current_cell_data->distance + 1){
                map->tiles[(current_cell_data->y - 1) * map->width + current_cell_data->x]->distance = current_cell_data->distance + 1;
                add_to_front_queue(&cells, create_cell(current_cell_data->x, current_cell_data->y - 1, current_cell_data->distance + 1));
            }
            else if (map->tiles[(current_cell_data->y - 1) * map->width + current_cell_data->x]->type == Tile_Type_Builing && map->tiles[(current_cell_data->y - 1) * map->width + current_cell_data->x]->varient == Building_Varient_Water_Tower && !is_water_tower_connected_to_house(map->tiles[(current_cell_data->y - 1) * map->width + current_cell_data->x]->building, house)){
                add_house_to_water_tower((Water_Tower_t*) map->tiles[(current_cell_data->y - 1) * map->width + current_cell_data->x]->building, house, current_cell_data->distance + 1);
                house->water_towers = create_queue(create_building_with_distance(map->tiles[(current_cell_data->y - 1) * map->width + current_cell_data->x]->building, current_cell_data->distance + 1));
            }
        }
        current_cell = current_cell->next;
    }while (current_cell != cells);

    do {
        Cell_t *current_cell_data = (Cell_t*) current_cell->data;
        map->tiles[current_cell_data->y * map->width + current_cell_data->x]->distance = 0;
        current_cell = current_cell->next;
    } while (current_cell != cells);
}

void link_all_houses_to_water_towers(Map_t* map, Queue_t* houses){
    Queue_t *current_house = houses;
    do {
        link_house_to_water_towers(map, (House_t*) current_house->data);
        current_house = current_house->next;
    } while (current_house != houses);
}

void share_water(Queue_t *houses){
    Queue_t *current_house = houses;
    while (current_house != houses->prev){
        House_t *house = (House_t*) current_house->data;
        switch (house->level) {
            case Cabane: {
                Queue_t *current_water_tower = house->water_towers;
                while (current_water_tower != house->water_towers->prev || house->water < 10){
                    Building_With_Distance_t *building_with_distance = (Building_With_Distance_t*) current_water_tower->data;
                    Water_Tower_t *water_tower = (Water_Tower_t*) building_with_distance->building;
                    if (water_tower->water >= 10){
                        water_tower->water -= (10 - house->water);
                        house->water += (10 - house->water);
                    }
                    current_water_tower = current_water_tower->next;
                }
                break;
            }
        }
        current_house = current_house->next;
    }
}

void reset_water_canalisations(Map_t *map){
    for (int i = 0; i < map->width * map->height; ++i) {
            map->tiles[i]->water = false;
    }
}

void reset_houses_water(Queue_t *houses){
    if (houses == NULL) return;
    Queue_t *current_house = houses;
    while (current_house != houses->prev){
        House_t *house = (House_t*) current_house->data;
        house->water = 0;
        Queue_t *current_water_tower = house->water_towers;
        while (current_water_tower != house->water_towers->prev){
            Building_With_Distance_t *building_with_distance = (Building_With_Distance_t*) current_water_tower->data;
            free(building_with_distance);
            current_water_tower = current_water_tower->next;
        }
        free_queue(&house->water_towers);
        current_house = current_house->next;
    }
}