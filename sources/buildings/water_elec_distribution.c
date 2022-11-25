//
// Created by eleuc on 22/11/2022.
//

#include "../../includes/buildings/water_elec_distribution.h"

void trier_centrale_par_connexite(Power_Plant_t **power_plants){

}

void add_house_to_power_plant_by_level(Power_Plant_t *power_plant, House_t *house) {
    if (!power_plant->houses) {
        add_queue(&power_plant->houses, house);
    }
    else{
        Queue_t *current_power_plant_house = power_plant->houses;
        while (current_power_plant_house != power_plant->houses && ((House_t *)current_power_plant_house->data)->level > house->level){
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
                    if (power_plant->electrecity >= 10){
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

void find_distance_to_water_tower(Map_t *map, House_t *house, Water_Tower_t *water_tower){

}

void add_house_to_water_tower_by_level(Water_Tower_t *water_tower, House_t *house) {
    if (!water_tower->houses) {
        add_queue(&water_tower->houses, house);
    }
    else{
        Queue_t *current_power_plant_house = water_tower->houses;
        while (current_power_plant_house != water_tower->houses && ((House_t *)current_power_plant_house->data)->level > house->level){
            current_power_plant_house = current_power_plant_house->next;
        }
        current_power_plant_house->prev->next = create_queue(house);
        current_power_plant_house->prev->next->next = current_power_plant_house;
        current_power_plant_house->prev = current_power_plant_house->prev->next;
    }
}