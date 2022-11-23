//
// Created by eleuc on 22/11/2022.
//

#include "../../includes/buildings/water_elec_distribution.h"

void add_house_by_level(Power_Plant_t *power_plant, House_t *house) {
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
    if (houses) {
        do {
            House_t *current_house = houses->data;
            if (current_house->connexite == power_plant->connexite) {
                add_house_by_level(power_plant, current_house);
            }
            houses = houses->next;
        } while (houses->next != houses);
    }
}

void electric_distribution(Power_Plant_t *power_plant, Queue_t *houses){
    Queue_t *current_house_cell = houses;
    while (current_house_cell != NULL && power_plant->electrecity > 0){
        House_t *current_house = current_house_cell->data;
        if (current_house->electricity == 0 && current_house->level > Terrain_nu && current_house->connexite == power_plant->connexite){
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
    }
}