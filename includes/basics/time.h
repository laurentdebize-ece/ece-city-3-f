//
// Created by eleuc on 01/11/2022.
//

#ifndef PROJET_TIME_H
#define PROJET_TIME_H

#include <raylib.h>
#include "interface utilisateur.h"

#define TIME_FOR_MONTH (FPS*15)

typedef struct {
    int counter;
    int seconds;
    int minutes;
    int hours;
    int months;
    int years;
} Time_t;

void update_time(Time_t *time);

void print_real_time(Vector2 position, Time_t *time);

void print_in_game_time(Vector2 position, Time_t *time);

void print_time(Vector2 position, Time_t *time);

#endif //PROJET_TIME_H
